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
#include <SerialCommand.h>
#include <Arduino.h>

/*
   var
*/
#define TX 11
#define RX 10
SoftwareSerial CMDSerial(RX, TX);    // The SoftwareSerial Object

//SerialCommand sCmd(CMDSerial);   // The demo SerialCommand object, using the SoftwareSerial Constructor
SerialCommand sCmd;

rdm630 rfid(3, 4);  //TX-pin of RDM630 connected to Arduino pin D3
const unsigned int ledPin = 13;
File myFile;
String eventId = "";
String logId = "" ;
unsigned long  rfidCard, oldCard;

unsigned long delaytime = 0;
unsigned long delaytimeLed = 0;

void setup() {
  Serial.begin(115200);
  CMDSerial.begin(115200);
  rfid.begin();

  pinMode(ledPin, OUTPUT);

  // Một số hàm trong thư viện Serial Command
  sCmd.addCommand("SetEvent", setEventID);
  sCmd.addCommand("SetTime", setTimeLog);
  sCmd.addCommand("New", haveNewRegistry);

  //  //đợi cài đặt sự kiện và thời gian ghi log
  //  while (eventId == "" || logId == "") {
  //    if (Serial.available() > 0) {
  //      String str = Serial.readStringUntil('/');
  //      if (str == "Send Data")  {
  //        Serial.println("Get Data/");
  //        while (true) {
  //          sCmd.readSerial();
  //        }
  //      }
  //    } else delay(1000);
  //  }
  //ktra module SD card
  if (!SD.begin(2)) {
    Serial.println("Error 1");
    writeLog("Error: SD card module not connect.");
  }
  Serial.println("readly");
  //  writeLog("Time: " + logId);
  //  writeLog("event: " + eventId);
}

void loop() {
  //hàng chờ lệnh
//  sCmd.readSerial();
  //  if (eventId != "" && logId != "") {
  //kiểm tra tính hiệu từ bộ đọc
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
  //  }
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

void writeLog(String log) {
  File logFile;
  logFile = SD.open("log/" + logId + ".log", FILE_WRITE);
  logFile.println(log);
  logFile.close();
}
void writeLogRFID(String log) {
  File logFile;
  logFile = SD.open(eventId + ".log", FILE_WRITE);
  if (!logFile) {
    Serial.println("not open file");
  }
  logFile.println(log);
  logFile.close();
  //  Serial.println("log Rfid");
}

//set event name: gán tên cho sự kiện để tạo file log điểm danh cho từng sự kiện riêng biệt
void setEventID() {
  char *arg;
  arg = sCmd.next();
  eventId = arg;
  Serial.println("Set Event ID: done.");
}
void setTimeLog() {
  char *arg;
  arg = sCmd.next();
  logId = arg;
  Serial.println("Set Time: done.");
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

