/*
   RFID module
    TX - pin 6
    RX - pin 7
   SD card attached to SPI bus as follows:
 ** MOSI - pin 17
 ** MISO - pin 18
 ** SCK - pin 19
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
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
rdm630 rfid(6, 7);  //TX-pin of RDM630 connected to Arduino pin 6

File myFile;
String eventName = "";
String logName = "" ;
unsigned long  rfidCard;

void setup() {
  Serial.begin(115200);
  rfid.begin();

  // Một số hàm trong thư viện Serial Command
  sCmd.addCommand("SetEvent",   setEventName);
  sCmd.addCommand("SetTimeLog",   setTimeLog);
  
  //đợi cài đặt sự kiện và thời gian ghi log
  while (eventName == "" || logName == "") {
    sCmd.readSerial();
  }
  writeLog("Time: "+logName);
  writeLog("event: "+eventName);
  
  //ktra module SD card
  if (!SD.begin(4)) {
    Serial.println("Error 1");
    writeLog("Error: SD card module not connect.");
  }
}

void loop() {
  //hàng chờ lệnh
  sCmd.readSerial();

  //kiểm tra tính hiệu từ bộ đọc
  rfidCard = readRFID();
  if ( rfidCard != 0) {
    writeLog("Read RFID card");
    writeLogRFID(rfidCard+"");
    Serial.print("Attendance ");
    Serial.println(rfidCard);
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
  logFile = SD.open("log/" + logName+".txt", FILE_WRITE);
  logFile.println(log);
  logFile.close();
}
void writeLogRFID(String log) {
  File logFile;
  logFile = SD.open("attendance/" + eventName+".txt", FILE_WRITE);
  logFile.println(log);
  logFile.close();
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

