## ThermoVent

WHAT: A jacket with vents that automatically open when I get too hot. A temperature sensor tracks my body heat, and when it crosses a threshold, it triggers a special wire sewn into the jacket that physically contracts — pulling the vent flaps open. When I cool down, they close on their own. No app, no buttons, just the jacket reacting to my body.

ABOUT ME: [I design and sew my own clothes](https://photos.app.goo.gl/d4ktTZewXSLSoAFM6) — I've made shirts, pants, and jackets from my own original patterns. But this project is pushing my creativity to a new place -- making clothes that are smart.  I have taken AP Computer Science (got an A and 4 on the test my freshman year). I led my FIRST LEGO League team to two [state championships](https://juiceboxrobotics.org/#seasons-2023-24). I am now taking an engineering class at high school. This is an opportunity to combine engineering knowledge with my personal interest in fashion. Thank you!

HOW TO MAKE IT: An Arduino reads a temperature sensor sewn into the inner lining near the chest. When it detects I'm running hot, it sends a signal to a switching component called a MOSFET — essentially a tiny electronic gate that lets current flow to a special wire called nitinol. Nitinol is a shape memory alloy: it looks like regular wire, but when electricity heats it up, it physically shortens. That contraction pulls a tab on the vent flap and opens it. When the Arduino cuts the current, the wire cools, and a small elastic band pulls the flap closed again. [Here is a diagram/schematic of how it will work](https://github.com/jediforri/ThermoVent/blob/main/IMG_6587.jpg).

[Here is a wiring diagram of how it will work](https://github.com/jediforri/ThermoVent/blob/main/Screenshot%202026-03-29%20at%208.24.jpg)

MATERIAL: I'd never heard of nitinol before this project. It's used in medical devices and aerospace engineering — but almost never in clothing. That's what drew me to it.

TECH: I will learn how MOSFETs work, how to manage a LiPo battery safely, and how to work with nitinol — a material I've never used before. I'm also figuring out how to route wiring through a garment without it showing or restricting movement. I know how to sew and build patterns, so the construction side feels manageable. The electronics are the new challenge, and that's exactly why I want to do this.

COST BREAKDOWN:

- Arduino Nano $12
- DS18B20 temperature sensor $5
- Flexinol nitinol wire (150µm, 1m) $15
- MOSFET + resistors (switching components) $11
- LiPo battery + USB charger board $15
- Voltage regulator $6
- Perfboard, heat shrink, connectors $8
- Fabric, snaps, elastic for vent mechanism $40
- Total $122

![design of thermo-jacket](https://github.com/jediforri/ThermoVent/blob/main/IMG_5955.jpg)

![circuit-design](https://github.com/jediforri/ThermoVent/blob/main/IMG_6587.jpg)
