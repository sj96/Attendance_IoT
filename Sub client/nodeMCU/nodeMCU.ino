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

const char* ssid = "PKOVER_WIFI";
const char* password =  "01678911202";

const String host = "http://192.168.43.47:80";
//const String host = "http://192.168.1.11:80";

const char* privateKey = "b091f0444231106d8e7b796ae7508bb50fc9c17556118fe705266018a4173438";

int delayTime = -1;

String event = "";
String eventId = "";
String date = "";
String date2 = "";
String timeStart = "";
String timeEnd = "";

//SerialCommand sCmd;

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
    //    Serial.println("Connecting..");
    printLCD("Connecting..", 0);
  }
  //  Serial.println("Connected");
  printLCD("Connected", 0);
  //  Serial.println("Get Event - Time");
  printLCD("Get Event - Time", 1);
  //lấy mã sự kiện
  String info = "";
  while (!readly()) {
    //    Serial.println("Geting...");
    printLCD("Get Event - Time", 0);
    printLCD("Geting...", 1);

    while (event == "" || event == "No Event") {
      info = getInfo();

      Serial.println(info);      
      StaticJsonBuffer<500> jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(info); 
      event = json["event"].as<String>();
      if (event == "" || event == "No Event") printLCD("No Event", 1);
      else {
        eventId = json["id"].as<String>();        
        date = json["date"].as<String>();
        date2 = json["date2"].as<String>();
        timeStart = json["timeStart"].as<String>();
        timeEnd = json["timeEnd"].as<String>();
        while (true) {
          Serial.println("/" + date2 + "ID" + eventId);          
          if (Serial.available() > 0) {
            String ok = Serial.readStringUntil('\n');
            if (ok = "OK") break;
          }
          delay(1000);
        }
      }
    }
      Serial.println("Event ID: " + eventId);
      Serial.println("Event: " + event);
      Serial.println("Date: " + date);
      Serial.println("Time: " + timeStart + " - " + timeEnd);
    
  }
  Serial.print("Get done");
  printLCD("Get done", 1);
  delay(5000);
  printLCD(event, 0);
  printLCD(date, 1);
}


void loop() {
  //  đợi lệnh
  //    sCmd.readSerial();
  if (Serial.available() > 0) {
    int code = Serial.parseInt();
    if (code > 0 && code > 100) {
      attendance(String(code));
      Serial.println(code);
    }
  }

  if (millis() - delayTime > 5000 && delayTime > 0) {
    printLCD(event, 0);
    printLCD(date, 1);
    //    Serial.println("Event: " + event);
    //    Serial.println("Time: " + date);
    delayTime = -1;

  }
  //
  //void attendance() {
  //  String rfid = sCmd.next();
}
void attendance(String rfid) {
  String info = sendAttendance(rfid);

  delayTime = millis();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(info);
  String name = json["name"].as<String>();
  String status = json["status"].as<String>();
  String time = json["time"].as<String>();
  //  if (name.startsWith("New")) {
  //    Serial.print("New\r\n");
  //  }
  Serial.println(info);
  printLCD(name, 0);
  if (status != "Attendance") {
    printLCD(status + " - " + time, 1);
  }
  else if (status == "Time Out") {
    printLCD(status, 1);
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
    //    Serial.print("getInfo: ");
    //    Serial.println(result);
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

