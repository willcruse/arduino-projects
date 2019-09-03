#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const int redPin = 0; //D3
const int greenPin = 4; //D4

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  WiFi.begin("REDACTED", "REDACTED");
  while(WiFi.status() != WL_CONNECTED) {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    delay(50);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(50);
  }
}

void loop() {
  IPAddress ip = (1, 1, 1, 1);
  bool ret = Ping.ping(ip);
  if (ret) {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  } else {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
  }
  delay(100);
}
