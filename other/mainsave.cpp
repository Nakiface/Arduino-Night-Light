#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "WiFiSetup.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoLifx.h>
//#include "MyLifx.h"

//Einträge Anpassen TODO: WiFiManager
const char* ssid = "ITS_Projekt";
const char* password = "ITS12345";
char targetMac[] = "d0:73:d5:3b:64:b3";
char target[] = "192.168.137.57";

char packetBuffer[255];
WiFiSetup wifi;
WiFiUDP Udp;
ArduinoLifx lifx(Udp);


void setup() {
  Serial.begin(115200);
  wifi.setup(ssid, password);
  lifx.begin(WiFi.localIP(), target, targetMac);
  lifx.setFlags(0, 0, 1);
  lifx.setColor(30, 100, 65535, 3500, 10); //3 Zahl ist helligkeit
}

void loop() {
  //lifx.setPower(1, 750);  // on
  //Serial.println("AN");
  delay(2000);
  lifx.setPower(0, 750);
  Serial.println("AUS"); // off
  delay(2000);
}
