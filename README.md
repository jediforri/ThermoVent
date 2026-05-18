# ThermoVent

## WHAT: 
A jacket with vents that automatically open when I get too hot. A temperature sensor tracks my body heat, and when it crosses a threshold, it triggers a special wire sewn into the jacket that physically contracts — pulling the vent flaps open. When I cool down, they close on their own. No app, no buttons, just the jacket reacting to my body.

## ABOUT ME: 
[I design and sew my own clothes](https://photos.app.goo.gl/d4ktTZewXSLSoAFM6) — I've made shirts, pants, and jackets from my own original patterns. But this project is pushing my creativity to a new place -- making clothes that are smart.  I have taken AP Computer Science (got an A and 4 on the test my freshman year). I led my FIRST LEGO League team to two [state championships](https://juiceboxrobotics.org/#seasons-2023-24). I am now taking an engineering class at high school. This is an opportunity to combine engineering knowledge with my personal interest in fashion. Thank you!

## HOW TO MAKE IT: 
A Seeed XIAO SAMD21 (an Arduino-compatible microcontroller) reads a temperature sensor sewn into the inner lining near the chest. When it detects I'm running hot, it sends a signal to a switching component called a MOSFET — essentially a tiny electronic gate that lets current flow to a special wire called nitinol. Nitinol is a shape memory alloy: it looks like regular wire, but when electricity heats it up, it physically shortens. That contraction pulls a tab on the vent flap and opens it. When the Arduino cuts the current, the wire cools, and a small elastic band pulls the flap closed again. 

## MATERIAL: 
I'd never heard of nitinol before this project. But I got some from amazon and [learned how it can change its shape when heated](https://youtube.com/shorts/DDK-d7Gqe3A) and was inspired.

## TECH:
I will learn how MOSFETs work, how to manage a LiPo battery safely, and how to work with nitinol — a material I've never used before. I'm also figuring out how to route wiring through a garment without it showing or restricting movement. I know how to sew and build patterns, so the construction side feels manageable. The electronics are the new challenge, and that's exactly why I want to do this.

The circuit uses raw components — temperature sensor, MOSFET, resistors — wired on my own breadboard layout rather than relying on premade sensor modules. This lets me document each design decision explicitly in the schematic: choosing a logic-level MOSFET (IRLZ44N) so the XIAO's 3.3V GPIO can fully drive the gate, adding a 4.7kΩ pull-up resistor to the DS18B20 data line as required by the 1-Wire bus specification, and using a 220Ω gate resistor to limit inrush current. I also switched from the Arduino Nano specified in earlier project drafts to the Seeed XIAO SAMD21 — same Arduino IDE compatibility, about half the board size (better for a wearable), and roughly 60% lower cost. The savings let me budget for a multimeter and higher-quality nitinol.

## COST BREAKDOWN:
[Amazon cart screenshot (PDF)](https://github.com/jediforri/ThermoVent/blob/main/ThermoVent-shopping.pdf) · [Checkout screenshot with grand total](https://github.com/jediforri/ThermoVent/blob/main/ThermoVent-checkout.png)

Funding request reflects the final Amazon shopping cart prices as of May 18, 2026.
 
### Component list
 
| # | Component | Qty | Listing | Unit price | Notes |
|---|---|---|---|---|---|
| 1 | DS18B20 waterproof temperature probe | 1 pack of 5 | HiLetgo 5pcs DS18B20 Temperature Sensor Stainless Steel Package Waterproof 1M | $10.99 | Stainless steel sealed probe with 1m cable; bare-wire termination for breadboard use |
| 2 | Digital multimeter | 1 | AstroAI AM33D 2000 Counts DC/AC Voltmeter | $14.59 | Required for MT3608 output voltage adjustment before circuit connection |
| 3 | Solderless breadboard + jumper wire kit | 1 | BOJACK 4 breadboards (830 + 400 tie-points) + 126 jumper wires | $9.99 | Prototyping platform |
| 4 | MT3608 boost converter | 1 pack of 10 | Eiechip MT3608 DC-DC Step Up Power Module, 2A output, adjustable | $11.69 | 3.7V LiPo → 5V step-up for circuit power rail |
| 5 | TP4056 USB-C charge controller | 1 pack of 6 | UMLIFE 6PCS TP4056 Type-C 1A Charging Module with Protection | $5.99 | LiPo charge management with overcurrent/overdischarge protection |
| 6 | 3.7V LiPo battery, 1000mAh | 1 | AKZYTUE 102050 LiPo with JST PH2.0 connector | $7.99 | Wearable power source |
| 7 | Flexinol nitinol actuator wire | 1 pack | Flexinol 0.0060" Diameter, 90°C Transition Temperature, 5' Length | $7.50 | Shape-memory actuator wire for vent louvers. *Currently shown as temporarily out of stock on Amazon; equivalent product available directly from Dynalloy Inc. (the manufacturer) at dynalloy.com if Amazon doesn't restock in time.* |
| 8 | Carbon film resistor assortment | 1 pack of 1000 | BOJACK 25-Value Resistor Kit (1Ω–1MΩ, 5%, 1/4W) | $9.99 | Includes 220Ω gate resistor and 4.7kΩ 1-Wire pull-up; assortment chosen since individual values cost similarly |
| 9 | IRLZ44N logic-level N-channel MOSFET | 1 pack of 10 | ALLECIN IRLZ44N 47A 55V TO-220 | $9.99 | Logic-level gate threshold (<3.3V) for XIAO SAMD21 PWM drive |
| 10 | Seeed Studio XIAO SAMD21 | 1 | Seeeduino XIAO ARM Cortex-M0+ Microcontroller | $9.50 | Project microcontroller |
 
### Total
 
| Line | Amount |
|---|---|
| Subtotal (10 items) | **$98.22** |
| Shipping (Amazon Prime) | $0.00 |
| Estimated tax (MA, ~6%) | ~$6.12 |
| **Estimated grand total** | **~$104.34** |


## DESIGN:
![design of thermo-jacket](https://github.com/jediforri/ThermoVent/blob/main/IMG_5955.jpg)

*Figure 1: Jacket design showing planned louver placement.*

![wiring design](https://github.com/jediforri/ThermoVent/blob/main/Schematic_jacket_2026-05-17%20(1).png)

*Figure 2: Circuit schematic. The XIAO SAMD21 reads the DS18B20 via a 1-Wire bus (with 4.7kΩ pull-up), and drives the nitinol wire through an IRLZ44N MOSFET gated by PWM on D9. Power chain: 3.7V LiPo → TP4056 charge controller → MT3608 boost converter → 5V circuit rail.*

## UNTESTED ARDUINO CODE:
[ThermoVent.ino](https://github.com/jediforri/ThermoVent/blob/main/ThermoVent.ino)
