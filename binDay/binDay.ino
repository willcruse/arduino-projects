#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const int redPin = 20;
const int greenPin = 19;
const int yellowPin = 18;
const int whitePin = 17;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(whitePin, OUTPUT);
  WiFi.begin("", "");
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
  resetLEDS();
  digitalWrite(whitePin, HIGH);
}

void loop() {
  resetLEDS();
  char* url = "https://europe-west1-bindicator.cloudfunctions.net/getData";
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  http.end();
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    digitalWrite(redPin, HIGH);
    Serial.println(error.c_str());
    return;
  }
  String binDay = doc["bin"];
  String recDay = doc["rec"];
  if (binDay.equals("true")) {
    digitalWrite(yellowPin, HIGH);
  }
  if (recDay.equals("true")) {
    digitalWrite(greenPin, HIGH);
  }
//  delay(21600000);
  delay(10);
}

void resetLEDS() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
}
