#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "cloudstorerailway-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HRZdnKL5V2DC5AXmWpAPavy3lrQgbIjX9tUp6yZl"
#define WIFI_SSID "Unique_Galaxy"
#define WIFI_PASSWORD "embedded@unique"

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n;

void loop() {
  // set value
  // Firebase.setFloat("number", 42.0);
  // get   value
  n = Firebase.getInt("number");
  Serial.print("  Value  : ");
  Serial.println(n);
  if(n == 1){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }
  
  delay(1000);
}
