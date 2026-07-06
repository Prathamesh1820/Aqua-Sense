**Smart Water Tank Monitoring and Pump Control System using Arduino & GSM**
**Developed as a First-Year Mechanical Engineering Project**

Aqua Sense is an Arduino-based smart water monitoring system designed to continuously monitor water level and water quality in storage tanks. The system displays real-time information on an OLED display and notifies the user through a GSM module when the water level becomes critically low.

The project evolved through two versions:

- **Version 1** – Water level and water quality monitoring with SMS alerts.
- **Version 2** – Enhanced with dual Arduino architecture, relay-based pump control, and selectable GSM notification modes.

#  Configuration

 Before uploading the code to your Arduino, update the following values according to your setup.
 

 Phone Number : Replace the default phone number with your own mobile number.
 
 Tank Height : Set the height of your water tank (in cm).
 
 Tank Capacity : Set the total capacity of your tank (in liters).

 
 

   **Note:** The project will not function correctly until these values are configured according to your installation.
 
# Features

 ## Version 1

-  User-configurable tank height
-  User-configurable tank capacity
-  Water level monitoring
-  Remaining water in Percentage and Liters
-  Live TDS monitoring
-  OLED display
-  Buzzer alerts
-  SMS notification using SIM800L
-  Boot animation


 ## Version 2

Includes every Version 1 feature plus:

-  Dual Arduino architecture
-  I²C communication between Arduinos
-  Relay controlled external pump
-  GSM Call alerts
-  GSM SMS alerts
-  SPDT switch for notification mode selection
-  Improved reliability by separating monitoring and communication tasks


#  Version Comparison

 Feature                                    Version 1             Version 2 
 

 Water Level Monitoring                         ✅                ✅
 
 Water Remaining (%)                            ✅                ✅
 
 Water Remaining (Liters)                       ✅                ✅

 OLED Display                                   ✅                ✅
 
 TDS Monitoring                                 ✅                ✅
 
 Boot Animation                                 ✅                ✅
 
 GSM SMS Alerts                                 ✅                ✅
 
 GSM Call Alerts                                ❌                ✅ 
 
 Relay Controlled Pump                          ❌                ✅
 
 Dual Arduino System                            ❌                ✅
 
 SPDT Notification Switch                       ❌                ✅
 


#  Hardware Used

### Version 1

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- TDS Sensor
- SIM800L GSM Module
- OLED Display
- Active Buzzer
- Buck Converter
- 22 kΩ & 10 kΩ Voltage Divider
- Capacitors

### Version 2

- 2 × Arduino Uno
- HC-SR04 Ultrasonic Sensor
- TDS Sensor
- SIM800L GSM Module
- OLED Display
- Relay Module
- SPDT Switch
- Active Buzzer
- Buck Converter
- 22 kΩ & 10 kΩ Voltage Divider
- Capacitors


# System Overview

## Version 1

The Arduino reads the ultrasonic sensor to determine the current water level and calculates the remaining water in both percentage and liters.

The TDS sensor continuously measures water quality.

All information is displayed on the OLED display.

When the water level falls below **20%**, the system:

- Activates the buzzer
- Sends an SMS notification through the SIM800L GSM module


## Version 2

Version 2 introduces a dual-controller architecture.

### Master Arduino

- Reads sensors
- Calculates water level
- Measures TDS
- Controls OLED display
- Controls buzzer
- Sends sensor data to Slave Arduino through I²C

### Slave Arduino

- Controls SIM800L
- Sends SMS
- Makes phone calls
- Controls relay module
- Operates according to the SPDT switch mode


#  Water Quality Classification

 TDS (ppm)             Water Quality 
 

 0 – 150               Excellent
 
 151 – 300             Good 
 
 301 – 500             Average 
 
 Above 500             Poor 
 


# Author

**Prathamesh Patil**

Developed as a **First-Year Mechanical Engineering Project** to explore embedded systems, Arduino programming, sensor integration, GSM communication, and automation.


## Support

If you found this project interesting, consider giving the repository a ⭐ on GitHub.


## License

This project is shared for educational and learning purposes.
