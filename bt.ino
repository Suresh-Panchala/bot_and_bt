#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
char recieve;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("Crawler Bot"); 
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    recieve = SerialBT.read();
    Serial.println(recieve);
  }
  delay(20);
}
