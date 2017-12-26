#include <SoftwareSerial.h>

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    int code = Serial.parseInt();    
      //      attendance(code);
      Serial.println(code);
    }
}
