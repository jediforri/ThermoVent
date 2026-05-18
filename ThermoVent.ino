// ThermoVent — thermally-actuated vest controller
// Reads skin temperature from a DS18B20, drives a nitinol wire via MOSFET PWM
// to proportionally open ventilation louvers as the wearer warms up.
//
// Hardware: Seeed XIAO SAMD21
//   D2 -> DS18B20 data line (1-Wire bus, 4.7kΩ pull-up to 5V)
//   D9 -> IRLZ44N MOSFET gate via 220Ω resistor; MOSFET switches nitinol to GND
//
// Status: UNTESTED. Hardware not yet assembled. Compiles cleanly for XIAO SAMD21.

#include <OneWire.h>
#include <DallasTemperature.h>

// --- Pin assignments ---
const int PIN_TEMP_SENSOR = 2;   // D2 on XIAO
const int PIN_MOSFET_GATE = 9;   // D9 on XIAO (PWM-capable)

// --- Control law thresholds ---
const float TEMP_VENT_START = 32.0;  // °C — below this, vents fully closed
const float TEMP_VENT_FULL  = 36.0;  // °C — above this, vents fully open

// --- Safety limit ---
// Nitinol activates around 70°C wire temperature. Cap PWM to limit average
// current and prevent the wire from overheating if the sensor fails high.
const int PWM_MAX = 200;  // out of 255 (~78% duty cycle)

// --- Loop timing ---
const unsigned long LOOP_INTERVAL_MS = 1000;  // read + update once per second

// --- Sensor objects ---
OneWire oneWire(PIN_TEMP_SENSOR);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000) {
    // Wait briefly for serial connection, but don't hang forever if unplugged
  }
  Serial.println("ThermoVent starting...");

  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount());
  Serial.println(" DS18B20 device(s)");

  pinMode(PIN_MOSFET_GATE, OUTPUT);
  analogWrite(PIN_MOSFET_GATE, 0);  // start with vents closed
}

void loop() {
  // Request a fresh reading from the sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Sanity check: DS18B20 returns -127 if disconnected or unreadable
  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("ERROR: temperature sensor disconnected");
    analogWrite(PIN_MOSFET_GATE, 0);  // fail safe: vents closed
    delay(LOOP_INTERVAL_MS);
    return;
  }

  // Compute PWM duty cycle from temperature using the control law
  int pwmValue = computePWM(tempC);
  analogWrite(PIN_MOSFET_GATE, pwmValue);

  // Log to serial for debugging
  Serial.print("Temp: ");
  Serial.print(tempC, 2);
  Serial.print(" °C   PWM: ");
  Serial.print(pwmValue);
  Serial.print(" / 255   (");
  Serial.print((pwmValue * 100) / 255);
  Serial.println("%)");

  delay(LOOP_INTERVAL_MS);
}

// Map temperature to PWM duty cycle.
// Below TEMP_VENT_START: 0 (vents closed).
// Above TEMP_VENT_FULL:  PWM_MAX (vents fully open).
// In between: linear ramp.
int computePWM(float tempC) {
  if (tempC <= TEMP_VENT_START) return 0;
  if (tempC >= TEMP_VENT_FULL) return PWM_MAX;

  float fraction = (tempC - TEMP_VENT_START) / (TEMP_VENT_FULL - TEMP_VENT_START);
  return (int)(fraction * PWM_MAX);
}
