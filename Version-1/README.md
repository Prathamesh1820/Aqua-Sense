#  Aqua Sense - Version 1

## Smart Water Tank Monitoring System
   Developed as a **First-Year Mechanical Engineering Project**.

## Overview
  Aqua Sense Version 1 is an Arduino-based smart water tank monitoring system designed to continuously monitor the water level and water quality inside a storage tank.

The system calculates the remaining water in both **percentage (%)** and **liters (L)** based on user-defined tank dimensions. It displays live information on an OLED display and automatically sends an SMS notification when the water level falls below a predefined threshold.

# Features
  -  User-configurable tank height
  -  User-configurable tank capacity
  -  Live water level monitoring
  -  Remaining water displayed in:
    - Percentage (%)
    - Liters (L)
  -  Live TDS (Total Dissolved Solids) monitoring
  -  OLED display for real-time information
  -  Low water buzzer alert
  -  SMS notification using SIM800L GSM module
  -  Boot animation during startup
  -  SMS cooldown of **120 seconds** to prevent repeated alerts

# Hardware Components

| Arduino Uno x1
| SIM800L GSM Module X1
| OLED Display x1
| Ultrasonic Sensor x1
| TDS Sensor x1
| Active Buzzer |x1
| Buck Converter x1
| 22 kΩ Resistor x1
| 10 kΩ Resistor x1

# Working Principle

1. The user enters the tank height and total tank capacity.
2. The ultrasonic sensor continuously measures the water level.
3. The Arduino calculates:
   - Remaining water percentage
   - Remaining water in liters
4. The TDS sensor measures the water quality.
5. All values are displayed live on the OLED display.
6. If the water level falls below **20%**, the buzzer activates and an SMS notification is sent to the owner.
7. To avoid repeated messages, SMS notifications have a cooldown period of **120 seconds**.

# Alert Settings

 Parameter                Value 

|Low Water Threshold       20% 
 SMS Cooldown              120 Seconds 

# Water Quality Classification

 TDS (ppm)       Water Quality 

 0 – 150          Excellent 
 151 – 300        Good 
 301 – 500        Average 
 Above 500        Poor 

# Hardware Design Considerations

## SIM800L Power Supply

The SIM800L GSM module requires an operating voltage between **3.4 V and 4.4 V** and can draw up to **2 A peak current** during SMS transmission.

Since the Arduino Uno cannot provide sufficient current, a **DC-DC Buck Converter** is used to provide a stable voltage and reliable power supply to the SIM800L module.

This prevents communication failures and unexpected module resets.


## Voltage Divider

The SIM800L RX pin operates at lower logic levels than the Arduino Uno.

To safely interface the Arduino with the SIM800L, a voltage divider using:

- 22 kΩ resistor
- 10 kΩ resistor

is connected between the Arduino TX pin and the SIM800L RX pin.

This reduces the Arduino's 5 V logic level to a safe voltage for the SIM800L.


# Project Images

Add project images in the `Images` folder.

Example:

- Hardware Setup
- OLED Display
- Circuit Assembly
- Prototype

# Circuit Diagram

The circuit diagram is available in the `Circuit-Diagram` folder.

# Source Code

Arduino source code is available in the `Arduino-Code` folder.




# Author

**Prathamesh Patil**

Developed as a **First-Year Mechanical Engineering Project** to demonstrate embedded systems, sensor integration, GSM communication, and real-time water monitoring using Arduino.

---

## License

This project is shared for educational and learning purposes.
