#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>

//Khởi tạo với các chân
LiquidCrystal lcd(D5, D0, D4, D3, D2, D1);

const char* ssid = "68C/10a";
const char* password =  "Khuvuc6@2017";

int count;

void setup() {
  pinMode(A0, INPUT);
  //Thông báo đây là LCD 1602
  lcd.begin(16, 2);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    printLCD("Connecting..", 0, 0);
  }
  Serial.println("Connected to the WiFi network");
  printLCD("Connected", 0, 0);
  count = 0;
}


void loop() {
  while (Serial.available()) {
    String id = Serial.readStringUntil(':');
    Serial.print(id+":");
    id = Serial.readStringUntil(';');
    Serial.println(id);
    Serial.println("Send data.");
    sendData(id);
    Serial.println("Send done.");
  }
}

boolean sendData(String ID) {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

    http.begin("http://192.168.1.7:80/post.php?ID=1&key=1"); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request

    if (httpCode > 0) { //Check for the returning code
      Serial.print(count + " - ");
      count++;
      String payload = http.getString();
      //        Serial.println(httpCode);
      Serial.println(payload);
      printLCD(payload, 0, 1);
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
}

void printLCD(String str, int x, int line) {
  clearLCD(line);
  lcd.setCursor(x, line);
  // In ra dong chu
  lcd.print(str);
}

void clearLCD(int line) {
  lcd.setCursor(0, line);
  lcd.print("                ");
}

