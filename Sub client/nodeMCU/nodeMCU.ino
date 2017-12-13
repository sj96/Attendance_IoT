#include <ArduinoJson.h>
#include <SerialCommand.h>

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>

//Khởi tạo với các chân
LiquidCrystal lcd(D5, D0, D4, D3, D2, D1);

const char* ssid = "68C/10a";
const char* password =  "Khuvuc6@2017";

const String host = "192.168.1.7:80";

const char* privateKey = "0388a47143e4ddca4c0c6c1be40e07ef63ea2091";

int delayTime = -1;

String event = "";
String date = "";

SerialCommand sCmd;

void setup() {
  //cài đặt LCD
  lcd.begin(16, 2);

  //mở giao tiếp
  Serial.begin(115200);

  sCmd.addCommand("Attendance ", attendance);

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
  printLCD("Get Event - Time", 1);
  //lấy mã sự kiện
  while (event == "" || event == "Error" || event == "no Event") {
    event = getEvent();
    if (event == "no Event") printLCD(event, 1);
  }
  Serial.println("SetEvent " + String(event));

  //lấy ngày tháng
  while (date == "" || date == "Error") {
    date = getDate();
  }

  Serial.print("SetTime " + String(date));
}


void loop() {
  if (delayTime < 0) {
    String str = event + "-" + date;
    printLCD(str, 0);
  }
  else {
    delayTime--;
  }
  //đợi lệnh
  sCmd.readSerial();
}

boolean attendance(String rfid) {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPRequest();
    HTTPClient http;
    JsonBuffer<200> jsonBuffer;
    String post = String("key=") + privateKey + String("rfid=") + rfid;

    http.begin("http://" + host + "/attendance"); //Specify the URL and certificate
    int httpCode = http.POST(post);                                                //Make the request

    if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();


    }

    else {
      Serial.println("Error");
    }

    http.end(); //Free the resources
  }
}

String getDate() {
  String url = "http://" + host + "/getTime.php?type=date";
  return Get(url);
}

String getEvent() {
  String result = "";
  String post = String("key=") + privateKey;
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    http.begin("http://" + host + "/getEvent.php"); //Specify the URL and certificate
    int httpCode = http.POST(post);                                                  //Make the request

    if (httpCode > 0) { //Check for the returning code
      result = http.getString();
    }
    else {
      result = "Error";
    }
    http.end(); //Free the resources
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

String Post(String host, String post){
  String result = "Error";
  if ((WiFi.status() == WL_CONNECTED)) { 
    HTTPClient http;
    http.begin(host); 
    int httpCode = http.POST(post);                                                  //Make the request
    if (httpCode > 0) { 
      result = http.getString();
    }
    http.end();
  }
  return result;
}

String Get(String host){
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

