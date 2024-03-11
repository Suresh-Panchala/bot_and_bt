#include "BluetoothSerial.h"
byte m1 = 13;
byte m2 = 12;
byte m3 = 14;
byte m4 = 27;
BluetoothSerial SerialBT;
char recieve;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("Crawler Bot"); 
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    recieve = SerialBT.read();
    Serial.println(recieve);
    if(recieve == 'a'){
      forward();
    }
    else if(recieve == 'b'){
      reverse();
    }
    else if(recieve == 'c'){
      left();
    }
    else if(recieve == 'd'){
      right();
    }
    else if(recieve == 'o'){
      standby();
    }
  }
  delay(20);
}
void forward(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
}
void reverse(){
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
}
void right(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
}
void left(){
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
}
void standby(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
}
