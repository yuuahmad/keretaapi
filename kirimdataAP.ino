#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

#include <Wire.h>
const char *ssid = "cobaESP";
const char *password = "123456789";

AsyncWebServer server(80);

String readPot()
{
  return String(analogRead(A0));
}
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/pot", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readPot().c_str());
  });
  server.begin();
}

void loop()
{
}
