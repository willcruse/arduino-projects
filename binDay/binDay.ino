#include <ESP8266WiFi.h>
#include <ESP8266httpclient.h>
#include <ArduinoJson.h>

const int redPin = 0;
const int greenPin = 0;
const int yellowPin = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
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
}

void loop() {
  resetLEDS();
  char* url = "https://europe-west1-bindicator.cloudfunctions.net/getData";
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  char payload[] = http.getString();
  Serial.println(payload);
  http.end();
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    pinMode(redPin, HIGH);
    Serial.println(error.c_str());
    return;
  }
  String binDay = doc["bin"];
  String recDay = doc["rec"];
  if (binDay.equals("true")) {
    pinMode(yellowPin, HIGH);
  }
  if (recDay.equals("true")) {
    pinMode(greenPin, HIGH);
  }
//  delay(21600000);
  delay(10);
}

void resetLEDS() {
  pinMode(redPin, LOW);
  pinMode(greenPin, LOW);
  pinMode(yellowPin, LOW);
}
