  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <Wire.h>
  #include <SoftwareSerial.h>

  //Oled Pins
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

  //Ultrasonic Sensor Pins
  #define TRIG 9
  #define ECHO 8
  float tankHeight = 15.0;  //Set your Tank Heigth in Cm.Replace with 15.0

  #define TDS_PIN A0

  #define BUZZER 11  

  SoftwareSerial sim(2, 3); //Sim800l  RX    TX Pins
  unsigned long lastSMS = 0;
  unsigned long smsCooldown = 120000;

  // Switch
  unsigned long lastSwitch = 0;
  bool showDisplay1 = true;

  // Sensor read
  unsigned long lastRead = 0;
  unsigned long readInterval = 500; 
  float percent = 0;
  float liters = 0;
  int tds = 0;

  //Water
  float getWaterLevelPercent(float distance) {
    float level = tankHeight - distance;
    if (level < 0) level = 0;
    if (level > tankHeight) level = tankHeight;
    return (level / tankHeight) * 100.0;
  }

  float getWaterLiters(float percent) {
    float tankVolume = 2.25;  //Replace "2.25" with Your Tank capacity In Liters
    return (percent / 100.0) * tankVolume;
  }

  //Sms
  void sendSMS(String msg) {
    if (millis() - lastSMS < smsCooldown) return;

    sim.println("AT+CMGF=1");
    delay(500);
    sim.println("AT+CMGS=\"+910000000000\""); //Replace "00000000" With Your Phone Number.
    delay(500);
    sim.println(msg);
    delay(300);
    sim.write(26);
    delay(2000);

    lastSMS = millis();
  }

  float getDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);
    return duration * 0.034 / 2.0;
  }

  // Tds 
  int getTDS() {
    int raw = analogRead(TDS_PIN);
    float voltage = raw * (5.0 / 1024.0);
    return voltage * 100;
  }

  //Startup Animation
  void showStartup() {
    display.clearDisplay();
    display.setTextColor(WHITE);

    display.setTextSize(3);
    display.setCursor(5, 5);
    display.print("AQUA");

    display.setTextSize(2);
    display.setCursor(25, 40);
    display.print("SENSE");

    display.display();
    delay(2000);
  }

  //D1
  void displayWater(float percent, float liters) {
    display.clearDisplay();
    display.setTextColor(WHITE);

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Water Level");

    display.setTextSize(3);
    display.setCursor(0, 15);
    display.print((int)percent);
    display.print("%");

    display.setTextSize(1);
    display.setCursor(0, 50);
    display.print("Left: ");
    display.print(liters, 1);
    display.print(" L");

    //bar
    int barHeight = map(percent, 0, 100, 0, 60);
    display.fillRect(118, 64 - barHeight, 8, barHeight, WHITE);

    //popup
    if (percent < 20) {
      display.setCursor(0, 40);
      display.print("LOW LEVEL!");
    }

    display.display();
  }

  //D2
  String getQualityText(int tds) {
    if (tds <= 150) return "Excellent";
    if (tds <= 300) return "Good";
    if (tds <= 500) return "Average";
    return "Poor";
  }

  void displayTDS(int tds) {
    display.clearDisplay();
    display.setTextColor(WHITE);

    display.setTextSize(2);
    display.setCursor(0, 5);
    display.print("TDS:");
    display.print(tds);

    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print(getQualityText(tds));

    if (tds > 500) {
      display.setCursor(0, 55);
      display.print("POOR QUALITY!");
    }

    display.display();
  }

  void setup() {
    Serial.begin(9600);
    sim.begin(9600);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      while (1);
    }

    showStartup();
  }

  void loop() {

    //SENSOR READ
    if (millis() - lastRead >= readInterval)
    {
      lastRead = millis();

      float distance = getDistance();
      percent = getWaterLevelPercent(distance);
      liters = getWaterLiters(percent);
      tds = getTDS();

      //Buzzer alerts
      if (percent < 20 || tds > 500 ) {
        digitalWrite(BUZZER, HIGH);
      } else {
        digitalWrite(BUZZER, LOW);
      }

      //SMS alerts
      if (percent < 20) sendSMS("ALERT: Water Level LOW!");
      if (tds > 500) sendSMS("ALERT: Water Quality BAD! TDS HIGH");
     

    }

    //DISPLAY SWITCH
    if (showDisplay1 && millis() - lastSwitch >= 5000) {
      showDisplay1 = false;
      lastSwitch = millis();
    }
    else if (!showDisplay1 && millis() - lastSwitch >= 2000) {
      showDisplay1 = true;
      lastSwitch = millis();
    }

    //SCREENS
    if (showDisplay1) {
      displayWater(percent, liters);
    } else {
      displayTDS(tds);
    }
  }
