#include <ArduinoJson.h>

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>

//Khởi tạo với các chân
LiquidCrystal lcd(D5, D0, D4, D3, D2, D1);

const char* ssid = "68C/10a";
const char* password =  "Khuvuc6@2017";

const char* host = "192.168.1.7:80";

const char* privateKey = "";

int count;

void setup() {
  //cài đặt LCD
  lcd.begin(16, 2);
  //mở giao tiếp
  Serial.begin(115200);
  //khởi tạo kết nối
  WiFi.begin(ssid, password);
  //kiểm tra kết nối host
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
    printLCD("Connecting..", 0);
  }
  Serial.println("Connected");
  printLCD("Connected", 0, 0);
  count = 0;
}


void loop() {
  
}

boolean sendData(String ID) {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

    http.begin("http://" + host + "/post.php?ID=1&key=1"); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request

    if (httpCode > 0) { //Check for the returning code
      Serial.print(count + " - ");
      count++;
      String payload = http.getString();
      //        Serial.println(httpCode);
      Serial.println(payload);
      printLCD(payload, 1);
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
}

String getTime() {
  String result = "";
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    http.begin("http://" + host + "/getTime.php"); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request

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
String getEvent() {
  String result = "";
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    http.begin("http://" + host + "/getEvent.php"); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request

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
  clearLCD(line);
  lcd.setCursor(0, line);
  // In ra dong chu
  lcd.print(str);
}

void clearLCD(int line) {
  lcd.setCursor(0, line);
  lcd.print("                ");
}

