#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const int redPin = 4; //D2
const int greenPin = 5; //D1
const int yellowPin = 2; //D4
const int whitePin = 15; //D3

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(whitePin, OUTPUT);
  Serial.println("Connecting to WiFi");
  WiFi.begin("REDACTED", "REDACTED");
  while(WiFi.status() != WL_CONNECTED) {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    delay(50);
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    delay(50);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(50);
  }
  Serial.println("Connected To WiFi");
  resetLEDS();
  digitalWrite(whitePin, HIGH);
}

void loop() {
  char* url = "http://europe-west1-bindicator.cloudfunctions.net/getData";
  HTTPClient http;
  bool a = http.begin(url);
  Serial.println(a);
//  while(!http.connected()) {
//    digitalWrite(whitePin, LOW);
//    delay(10);
//    Serial.println("connecting");
//    digitalWrite(whitePin, HIGH);
//  }
  digitalWrite(whitePin, LOW);
  Serial.println("Getting from URL");
  int httpCode = http.GET();
  String payload = http.getString();
  http.end();
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    digitalWrite(redPin, HIGH);
    Serial.print("Error: ");
    Serial.println(error.c_str());
    return;
  }
  String binDay = doc["bin"];
  String recDay = doc["rec"];
  if (binDay.equals("true")) {
    digitalWrite(yellowPin, HIGH);
  } else {
    digitalWrite(yellowPin, LOW);
  }
  if (recDay.equals("true")) {
    digitalWrite(greenPin, HIGH);
  } else {
    digitalWrite(greenPin, LOW);
  }
//  delay(21600000);
  delay(1000000);
}

void resetLEDS() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
}
