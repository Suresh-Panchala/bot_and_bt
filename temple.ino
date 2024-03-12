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
  pinMode(12,OUTPUT);
  digitalWrite(12, HIGH);
  softSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(25); 
  delay(200);
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)){
    thresh = tm.Hour;
    Serial.println(thresh);
    

  }
  if(thresh == 5 && count == 0){
      digitalWrite(12, LOW);
      delay(4000);
      count = count + 1; 
      myDFPlayer.play(1);
  }
  
  if (myDFPlayer.available()) {
      uint8_t state = myDFPlayer.readType();
      Serial.print("State == ");
      Serial.println(state);
      if(state == 5){
        delay(1000);
        digitalWrite(12, HIGH);
        count = count - 1;
      }
  }
  delay(1000);
}
