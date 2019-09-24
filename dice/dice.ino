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
  
  //Read tiltswitches
  val1 = digitalRead(switchTilt01);
  val2 = digitalRead(switchTilt02);
  val3 = digitalRead(switchTilt03);
  val4 = digitalRead(switchTilt04);
  val5 = digitalRead(switchTilt05);
  val6 = digitalRead(switchTilt06);

  if (val1 == LOW) {
    Serial.println("Side 1");
    client.publish("/dice", "1");
  }

  if (val2 == LOW) {
    Serial.println("Side 2");
    client.publish("/dice", "2");
  }
    
  if (val3 == LOW) {
    Serial.println("Side 3");
    client.publish("/dice", "3");
  }
    
  if (val4 == LOW) {
    Serial.println("Side 4");
    client.publish("/dice", "4");
  }

  if (val5 == LOW) {
    Serial.println("Side 5");
    client.publish("/dice", "5");
  }

  if (val6 == LOW) {
    Serial.println("Side 6");
    client.publish("/dice", "6");
  }
}
