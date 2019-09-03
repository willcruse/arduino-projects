#include <ESP8266WiFi.h>

const char* ssid = "REDACTED";
const char* PASSWORD = "REDACTED";

const int trig = 2;
const int echo = 0;

bool eng = false;
long lastEng = 0;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(50);
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  server.begin();
  Serial.print("Server Started: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2)/29.1;
  if (distance < 200) {
    lastEng = millis();
  }
  eng = (lastEng + 10000) <= millis();
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("New Client");
  while(!client.available()){
    delay(1);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.print("<html><head><title>Shitting?</title></head><body><p>There is ");
  if (!eng) {
     client.print("<b>a dickhead</b>");
  } else {
   client.print("<b>no one</b>");
  }
  client.print(distance);
  client.println(" shitting</p></body></html>");
  delay(10);
  Serial.println("Client Disconnected");
  Serial.println("");
}
