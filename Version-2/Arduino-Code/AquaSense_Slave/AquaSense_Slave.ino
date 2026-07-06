//SLAVE
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial sim(2, 3);

int percent = 0;
int tds = 0;

bool lowSent = false;
bool tdsSent = false;

#define SMS_PIN 5
#define CALL_PIN 7
#define RELAY_PIN 8   

void receiveData(int bytes) {
  percent = Wire.read();
  int highByte = Wire.read();
  int lowByte = Wire.read();
  tds = (highByte << 8) | lowByte;
}

void sendSMS(String msg) {
  sim.println("AT+CMGF=1");
  delay(500);
  sim.println("AT+CMGS=\"+910000000000\""); //Replace "00000000" With Your Phone Number.
  delay(500);
  sim.println(msg);
  delay(300);
  sim.write(26);
  delay(3000);
}

void makeCall() {
  sim.println("ATD+910000000000;"); //Replace "00000000" With Your Phone Number.
  delay(20000);   
  sim.println("ATH");
  delay(1000);
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveData);

  sim.begin(9600);

  pinMode(SMS_PIN, INPUT_PULLUP);
  pinMode(CALL_PIN, INPUT_PULLUP);

  // Relay setup
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  

  delay(15000);  
}

void loop() {

  bool smsMode  = (digitalRead(SMS_PIN) == LOW);
  bool callMode = (digitalRead(CALL_PIN) == LOW);

  if (!smsMode && !callMode) {
    delay(300);
  }

  if (percent < 20) {

    digitalWrite(RELAY_PIN, LOW);  

    if (!lowSent) {
      if (smsMode) {
        sendSMS("ALERT: Water Level LOW!");
      }

      if (callMode) {
        makeCall();
      }

      lowSent = true;
    }
  }
  else {  
    digitalWrite(RELAY_PIN, HIGH);
    lowSent = false;
  }
  if (tds > 500 && !tdsSent) {

    if (smsMode) {
      sendSMS("ALERT: Water Quality BAD!");
    }

    if (callMode) {
      makeCall();
    }

    tdsSent = true;
  }

  if (tds <= 500) {
    tdsSent = false;
  }

  delay(500);
}