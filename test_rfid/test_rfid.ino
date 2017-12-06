#include "rdm630.h"

rdm630 rfid(3, 4);  //TX-pin of RDM630 connected to Arduino pin 3
int i = 0;
unsigned long int old_data = 0;
void setup()
{
  Serial.begin(9600);  // start serial to PC
  rfid.begin();

  Serial.println("ok!");
}

void loop()
{
  byte data[6];
  byte length;
  if (rfid.available()) {
    rfid.getData(data, length);
    //concatenate the bytes in the data array to one long which can be
    //rendered as a decimal number
    unsigned long result =
      ((unsigned long int)data[1] << 24) +
      ((unsigned long int)data[2] << 16) +
      ((unsigned long int)data[3] << 8) +
      data[4];
    Serial.println("Data valid ");
    Serial.println(i);
    i++;
    for (int i = 0; i < length; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("decimal CardID: ");
    Serial.println(result);
  }
}
