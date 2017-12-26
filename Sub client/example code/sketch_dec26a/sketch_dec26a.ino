#include <SoftwareSerial.h>

#define TX 7
#define RX 8
SoftwareSerial CMDSerial(RX, TX, false, 256);

String date = "26122012";

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   CMDSerial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  CMDSerial.print("SetTime " + date + "\r\n");
  Serial.print("SetTime " + date + "\r\n");
  delay(1000);
}
