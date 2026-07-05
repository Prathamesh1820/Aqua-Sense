# Overview

Aqua Sense Version 2 (v2) is an enhanced version of the original Aqua Sense system. It introduces a dual-Arduino architecture to separate sensor monitoring from communication and control tasks, resulting in improved reliability and expandability.

The system continuously monitors water level and water quality, displays real-time information on an OLED display, activates a buzzer for alerts, controls an external water pump through a relay, and notifies the owner using SMS or phone calls via a SIM800L GSM module.


# New Features

- Dual Arduino architecture
- I²C communication between Master and Slave Arduino
- Relay-controlled external pump
- GSM SMS notifications
- GSM phone call alerts
- SPDT switch for notification mode selection
- Automatic relay control
- Improved modular design


# Features

- User-configurable tank height
- User-configurable tank capacity
- Water level monitoring
- Remaining water in Percentage (%)
- Remaining water in Liters (L)
- OLED live display
- Boot animation
- Live TDS monitoring
- Water quality classification
- Low water buzzer alert
- SMS notifications
- Phone call notifications
- Relay controlled pump

---

# Hardware Components

 Component                Quantity 

 Arduino Uno                  2       
 SIM800L GSM Module           1
 OLED Display                 1
 Ultrasonic Sensor            1
 TDS Sensor                   1
 Relay Module                 1
 SPDT Switch                  1
 Active Buzzer                1
 Buck Converter               1
 22 kΩ Resistor               1
 10 kΩ Resistor               1


# System Architecture

  ## Master Arduino

  Responsibilities:

- Reads Ultrasonic Sensor
- Reads TDS Sensor
- Calculates remaining water
- Displays live data on OLED
- Controls buzzer
- Sends sensor data to Slave Arduino through I²C

---

  ## Slave Arduino

  Responsibilities:

- Receives data from Master Arduino
- Controls SIM800L GSM module
- Sends SMS alerts
- Makes phone call alerts
- Controls relay module for pump operation


# Working Principle

1. The Ultrasonic Sensor measures the water level.
2. The Arduino calculates:
   - Water percentage
   - Remaining liters
3. The TDS Sensor measures water quality.
4. OLED displays live information.
5. When water level falls below 20%, the buzzer activates.
6. The Master Arduino sends the water level and TDS values to the Slave Arduino using I²C.
7. Depending on the SPDT switch position:
   - SMS Mode → Sends SMS
   - Call Mode → Makes a phone call
   - OFF → No GSM notification
8. The Slave Arduino activates the relay when the water level is low.


# Notification Modes

 Mode          Function 
 
 SMS            Sends SMS alerts 
 CALL           Makes phone call alerts 
 OFF            Disables GSM notifications 


# Alert Conditions

 Condition                  Action 

 Water Level < 20%          Buzzer + Relay + SMS/Call 
 TDS > 500 ppm              SMS/Call 
 

# Water Quality Classification

 TDS (ppm)        Quality 

 0 – 150          Excellent 
 151 – 300        Good 
 301 – 500        Average 
 Above 500        Poor 


# Hardware Design Considerations

## SIM800L Power Supply

The SIM800L GSM module requires **3.4 – 4.4 V** and can draw up to **2 A** during transmission.

A dedicated **DC-DC Buck Converter** provides stable voltage and sufficient current because the Arduino Uno cannot supply the required peak current.


## Voltage Divider

A **22 kΩ** and **10 kΩ** resistor voltage divider is used to safely reduce the Arduino Uno's 5 V TX signal for the SIM800L RX pin.


## I²C Communication

Communication between the two Arduino Uno boards is achieved using the **Wire (I²C) library**.

The Master Arduino transmits:

- Water Level (%)
- TDS Value

to the Slave Arduino, allowing communication and relay tasks to remain independent from sensor processing.



# Author

**Prathamesh**

Developed as a **First-Year Mechanical Engineering Project** to demonstrate embedded systems, sensor integration, GSM communication, automation, and real-time water monitoring using Arduino.
