#include <ArduinoJson.h>
#include <SerialCommand.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>

//Khởi tạo với các chân
LiquidCrystal lcd(D5, D0, D4, D3, D2, D1);

const char* ssid = "68C/10a";
const char* password =  "Khuvuc6@2017";

const String host = "http://192.168.1.7:80";

const char* privateKey = "b091f0444231106d8e7b796ae7508bb50fc9c17556118fe705266018a4173438";

int delayTime = -1;

String event = "";
String eventId = "";
String date = "";

SerialCommand sCmd;

void setup() {
  //cài đặt LCD
  lcd.begin(16, 2);
  //xoa lcd
  clearLCD(0);
  clearLCD(1);

  //mở giao tiếp
  Serial.begin(115200);

  //  sCmd.addCommand("Attendance ", attendance);

  //khởi tạo kết nối
  WiFi.begin(ssid, password);

  //kiểm tra kết nối host
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
    printLCD("Connecting..", 0);
  }
  Serial.println("Connected");
  printLCD("Connected", 0);
  Serial.println("Get Event - Time");
  printLCD("Get Event - Time", 1);
  //lấy mã sự kiện
  String info = "";
  while (!readly()) {
    Serial.println("Geting...");
    printLCD("Get Event - Time", 0);
    printLCD("Geting...", 1);
    info = getInfo();

    Serial.println("Geting... 1");
    while (info == "Error") {
      Serial.println("Geting... 2");
      info = getInfo();
    }
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(info);
    if ( json["event"].as<String>() == "No Event") printLCD("No Event", 1);
    else {
      eventId = json["id"].as<String>();
      event = json["event"].as<String>();
      date = json["date"].as<String>();

      delay(1000);
      Serial.print("SetEvent " + eventId + "\r\n");
//      delay(1000);
//      Serial.print("SetTime " + date + "\r\n");

    }
  }
  Serial.print("Get done");
  printLCD("Get done", 1);
  delay(500);
}


void loop() {
  //  đợi lệnh
  //    sCmd.readSerial();
  if (Serial.available() > 0) {
    String code = Serial.readStringUntil('-');
    if (code == "Attendance") {
      String rfid =  Serial.readStringUntil('/');
      //      attendance(code);
      Serial.println(code + " - " + rfid);
    }
  }
  if (delayTime < 0) {
    printLCD(event, 0);
    printLCD(date, 1);
    //    Serial.println("Event: " + event);
    //    Serial.println("Time: " + date);
  }
  else {
    delayTime--;
  }

}
//
//void attendance() {
//  String rfid = sCmd.next();
void attendance(String rfid) {
  String info = sendAttendance(rfid);
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(info);
  String name = json["name"].as<String>();
  String status = json["status"].as<String>();
  String time = json["time"].as<String>();
  if (name.startsWith("New")) {
    Serial.print("New\r\n");
  }
  printLCD(name, 0);
  if (time != "Attendance") {
    printLCD(status + " - " + time, 1);
  }
  else printLCD("Got roll-call", 1);
}
String sendAttendance(String rfid) {
  String result = "Error";

  String post = String("key=") + privateKey + String("&rfid=") + rfid;
  while (result == "Error") {
    result = Post(host + String("/attendance.php"), post);
  }
  return result;
}

boolean readly() {
  return (event != "" && event != "No Event" && date != "") ? true : false;
}

String getInfo() {
  String result = "Error";
  String post = String("key=") + privateKey;
  while (result == "Error") {
    result = Post(host + String("/getInfo.php"), post);
    Serial.print("getInfo: ");
    Serial.println(result);
  }
  return result;
}

void printLCD(String str, int line) {
  int x = 0;
  clearLCD(line);
  if (str.length() <= 16) {
    x = (16 - str.length()) / 2;
  }
  lcd.setCursor(x, line);
  // In ra dong chu
  lcd.print(str);
}

void clearLCD(int line) {
  lcd.setCursor(0, line);
  lcd.print("                ");
}

String Post(String host, String post) {
  String result = "Error";
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(host);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(post);
    if (httpCode > 0) {
      result = http.getString();
    }
    http.end();
  }
  //  Serial.print("Post: ");
  //  Serial.println(result);
  return result;
}

String Get(String host) {
  String result = "Error";
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(host);
    int httpCode = http.GET();
    if (httpCode > 0) {
      result = http.getString();
    }
    http.end(); //Free the resources
  }
  return result;
}

