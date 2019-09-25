#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "kali";
const char pass[] = "WoollyBugger837";

//Initiate tiltswitches pins
const int statusLED = LED_BUILTIN;
const int switchTilt01 = 26;
const int switchTilt02 = 25;
const int switchTilt03 = 34;
const int switchTilt04 = 39;
const int switchTilt05 = 36;
const int switchTilt06 = 4;

//Initiate tiltswitches values
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

//Initiate led pins
const int ledStripR = 13;
const int ledStripG = 12;
const int ledStripB = 27;

//Colours
const int[] white = [255, 255, 255];
const int[] off = [0, 0, 0];
const int[] devotion = [255, 10, 50];
const int[] control = [10, 50, 255];
const int[] tieupagainst = [10, 255, 50];
const int[] communication = [255, 50, 10];
const int[] whatisviolence = [50, 10, 255];
const int[] groupchallenge = [50, 255, 10];

#define fadespeed 5

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/liberatehongkong");
  // client.unsubscribe("/hello");
}

void blinkTest() {
  digitalWrite(ledStripR, HIGH);
  delay(500);
  digitalWrite(ledStripR,LOW);
  delay(5);
  digitalWrite(ledStripG, HIGH);
  delay(500);
  digitalWrite(ledStripG,LOW);
  delay(5);
  digitalWrite(ledStripB, HIGH);
  delay(500);
  digitalWrite(ledStripB,LOW);
  delay(5);
}

void idleCheck() {
  return true;
  /*
  val1new = digitalRead(switchTilt01);
  if (val1new == val1) {
    return true;
  } else return false;
  */
}

void idle() {
  if (idleCheck() == true) {
    int r;
    for (r = 0; r < 256; r++) { 
      analogWrite(ledStripR, r);
      analogWrite(ledStripG, r);
      analogWrite(ledStripB, r);
      delay(fadespeed);
    } 
  }
}

void shake() {
  int r, g, b;
	 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(ledStripR, r);
    delay(fadespeed);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(ledStripG, b);
    delay(fadespeed);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(ledStripB, g);
    delay(fadespeed);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    delay(fadespeed);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    delay(fadespeed);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(fadespeed);
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("172.20.10.12", net);
  client.onMessage(messageReceived);

  connect();

  //Set led pins
  pinMode (statusLED, OUTPUT);

  //Set tiltswitches pins
  pinMode (switchTilt01, INPUT);
  pinMode (switchTilt02, INPUT);
  pinMode (switchTilt03, INPUT);
  pinMode (switchTilt04, INPUT);
  pinMode (switchTilt05, INPUT);
  pinMode (switchTilt06, INPUT);

}

void loop() {
  /*
  //MQTT
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/liberatehongkong", "liberatehonkong");
  }
  */
  
  //Read tiltswitches
  val1 = digitalRead(switchTilt01);
  val2 = digitalRead(switchTilt02);
  val3 = digitalRead(switchTilt03);
  val4 = digitalRead(switchTilt04);
  val5 = digitalRead(switchTilt05);
  val6 = digitalRead(switchTilt06);

  //Shake
  if (idleCheck() != true) {
    shake();
    roll();
  }

  /*
  //Roll
  if (val1 == LOW) {
    Serial.println("Side 1");
    //client.publish("/dice", "1");
  }

  if (val2 == LOW) {
    Serial.println("Side 2");
    //client.publish("/dice", "2");
  }
    
  if (val3 == LOW) {
    Serial.println("Side 3");
    //client.publish("/dice", "3");
  }
    
  if (val4 == LOW) {
    Serial.println("Side 4");
    //client.publish("/dice", "4");
  }

  if (val5 == LOW) {
    Serial.println("Side 5");
    //client.publish("/dice", "5");
  }

  if (val6 == LOW) {
    Serial.println("Side 6");
    //client.publish("/dice", "6");
  }
  */

}
