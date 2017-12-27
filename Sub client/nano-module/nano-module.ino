/*
   RFID module
    TX - pin 3
    RX - pin 4
   SD card attached to SPI bus as follows:
   MOSI - pin 17
   MISO - pin 18
   SCK - pin 19
   CS - pin 2 (for MKRZero SD: SDCARD_SS_PIN)
   Led notifycation - pin A7
*/

/*
    include lib
*/
#include "rdm630.h"
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

/*
   var
*/
rdm630 rfid(3, 4);  //TX-pin of RDM630 connected to Arduino pin D3
const unsigned int ledPin = 12;

File myFile;
String logFile = "";
unsigned long  rfidCard, oldCard;

unsigned long delaytime = 0;
unsigned long delaytimeLed = 0;

void setup() {
  Serial.begin(115200);
  rfid.begin();

  pinMode(ledPin, OUTPUT);
  
  
  if (!SD.begin(2)) {
    Serial.println("Error 1");
    writeLog("Error: SD card module not connect.");
  }
  while (logFile == "") {
    if (Serial.available() > 0) {
      logFile = Serial.readStringUntil('/');
      logFile = Serial.readStringUntil('\n');
      if (logFile != "") {
        delay(1000);
        Serial.println("OK");
//        Serial.println(logFile);
      }
    }
  }
  digitalWrite(ledPin, HIGH);
}

void loop() {
  //hàng chờ lệnh
  if (Serial.available() > 0) {
      String logStr = Serial.readStringUntil('\n');
      writeLog(logStr);
    }
  
  //xu li ma RFID tu the
  rfidCard = readRFID();
  if ( rfidCard != 0) {
    if (delaytime != 0 && oldCard == rfidCard) {
      delaytime = millis();
      delaytimeLed = delaytime;
      digitalWrite(ledPin, HIGH) ;
    }
    else {
      delaytime = millis();
      oldCard = rfidCard;
      //      writeLog("Read RFID card");
      //      writeLogRFID(String(rfidCard));
      Serial.println(rfidCard);
      //      CMDSerial.println("Attendance " + String(rfidCard));
    }
  }
  else {
    if (millis() - delaytime > 1000 && delaytime > 0) {
      //        Serial.println("ok! next Card.");
      delaytime = 0;
    }
  }
  if (millis() - delaytimeLed > 1000 && delaytimeLed > 0) {
    delaytimeLed = 0;
    digitalWrite(ledPin, LOW);
  }
}

unsigned long int readRFID() {
  byte data[6];
  byte length;
  unsigned long int result = 0;
  if (rfid.available()) {
    rfid.getData(data, length);
    //chuyển về thập phân
    result =
      ((unsigned long int)data[1] << 24) +
      ((unsigned long int)data[2] << 16) +
      ((unsigned long int)data[3] << 8) +
      data[4];
  }
  return result;
}

void writeLog(String logStr) {
  File logF;
  logF = SD.open("log/" + logFile + ".log", FILE_WRITE);
  logF.println(logStr);
  logF.close();
//  Serial.println(logStr);
}

void haveNewRegistry() {
  Serial.println("New Registry.");
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
}

