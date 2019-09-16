#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "The Grand Blossom 27A";
const char* password =  "TGB_guest27a";

const int statusLED = LED_BUILTIN;

const int switchTilt01 = 26;
const int switchTilt02 = 25;
const int switchTilt03 = 34;
const int switchTilt04 = 39;
const int switchTilt05 = 36;
const int switchTilt06 = 4;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

void setup() {

  // Initialize serial
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  
  pinMode (statusLED, OUTPUT);
  
  pinMode (switchTilt01, INPUT);
  pinMode (switchTilt02, INPUT);
  pinMode (switchTilt03, INPUT);
  pinMode (switchTilt04, INPUT);
  pinMode (switchTilt05, INPUT);
  pinMode (switchTilt06, INPUT);

  Serial.begin(9600);

}

void loop() {
  val1 = digitalRead(switchTilt01);
  val2 = digitalRead(switchTilt02);
  val3 = digitalRead(switchTilt03);
  val4 = digitalRead(switchTilt04);
  val5 = digitalRead(switchTilt05);
  val6 = digitalRead(switchTilt06);
  
  if (val1 == LOW) {
    Serial.println("Side 1");
  }

  if (val2 == LOW) {
    Serial.println("Side 2");
  }
  
  if (val3 == LOW) {
    Serial.println("Side 3");
  }
  
  if (val4 == LOW) {
    Serial.println("Side 4");
  }

  if (val5 == LOW) {
    Serial.println("Side 5");
  }

  if (val6 == LOW) {
    Serial.println("Side 6");
  }
}
