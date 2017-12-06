/*
   RFID module
    TX - pin 3
    RX - pin 4
   SD card attached to SPI bus as follows:
 ** MOSI - pin 17
 ** MISO - pin 18
 ** SCK - pin 19
 ** CS - pin 2 (for MKRZero SD: SDCARD_SS_PIN)
*/

/*
    include lib
*/
#include "rdm630.h"
#include <SPI.h>
#include <SD.h>

#include <SerialCommand.h>

/*
   var
*/
SerialCommand sCmd;
rdm630 rfid(3, 4);  //TX-pin of RDM630 connected to Arduino pin D3

File myFile;
String eventName = "";
String logName = "" ;
unsigned long  rfidCard, oldCard;

unsigned long delaytime = 0;


void setup() {
  Serial.begin(115200);
  rfid.begin();

  // Một số hàm trong thư viện Serial Command
  sCmd.addCommand("SetEvent", setEventName);
  sCmd.addCommand("SetTime", setTimeLog);

  //đợi cài đặt sự kiện và thời gian ghi log
  while (eventName == "" || logName == "") {
    sCmd.readSerial();
  }
  //ktra module SD card
  if (!SD.begin(2)) {
    Serial.println("Error 1");
    writeLog("Error: SD card module not connect.");
  }
  Serial.println("readly");
  writeLog("Time: " + logName);
  writeLog("event: " + eventName);

}

void loop() {
  //hàng chờ lệnh
  sCmd.readSerial();

  //kiểm tra tính hiệu từ bộ đọc
  rfidCard = readRFID();
  if ( rfidCard != 0) {
    if (delaytime != 0 && oldCard == rfidCard) {
      delaytime = millis();
    }
    else {
      delaytime = millis();
      oldCard = rfidCard;
      //      writeLog("Read RFID card");
      writeLogRFID(String(rfidCard));
      Serial.println("Attendance " + String(rfidCard));
    }
  }
  else {
    if (millis() - delaytime > 1000 && delaytime > 0) {
      Serial.println("ok! next Card.");
      delaytime = 0;
    }
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

void writeLog(String log) {
  File logFile;
  logFile = SD.open("log/" + logName + ".log", FILE_WRITE);
  logFile.println(log);
  logFile.close();
}
void writeLogRFID(String log) {
  File logFile;
  logFile = SD.open(eventName + ".log", FILE_WRITE);
  if (!logFile) {
    Serial.println("not open file");
  }
  logFile.println(log);
  logFile.close();
  Serial.println("log Rfid");
}

//set event name: gán tên cho sự kiện để tạo file log điểm danh cho từng sự kiện riêng biệt
void setEventName() {
  char *arg;
  arg = sCmd.next();
  eventName = arg;
}
void setTimeLog() {
  char *arg;
  arg = sCmd.next();
  logName = arg;
}

