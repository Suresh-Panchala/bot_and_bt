#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/5, /*tx =*/4);
DFRobotDFPlayerMini myDFPlayer;
int count = 0;
int thresh = 0;
void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13, HIGH);
  softSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("MP3 Player Mini Demo"));
  if (!myDFPlayer.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30); 
  delay(200);
}
void loop() {
  tmElements_t tm;
  if (RTC.read(tm)){
    thresh = tm.Hour;
    Serial.println(thresh);
  }
  if(thresh == 6 && count == 0){
      digitalWrite(13, LOW);
      delay(3000);
      count = count + 1; 
      myDFPlayer.play(1);
  }
  if (myDFPlayer.available()) {
      uint8_t state = myDFPlayer.readType();
      Serial.print("State == ");
      Serial.println(state);
      if(state == 5 && count == 1){
        delay(120000);
        myDFPlayer.play(2);   
        count = count + 1;
        state = 0;
      }
      else if(state == 5 && count == 2 ){ 
        Serial.println("Count == 0");
        digitalWrite(13, HIGH);
      }
      else if(thresh == 7){
       count = 0;
      }
  }
  delay(1000);
}
