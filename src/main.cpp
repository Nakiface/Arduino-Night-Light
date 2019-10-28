#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "WiFiSetup.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoLifx.h>
#include "MyLifx.h"
#include "Sensors.h"
#include "RTC.h"

//Einträge Anpassen TODO: WiFiManager
const char* ssid = "ITS_Projekt";
const char* password = "ITS12345";
bool power = false;
char* targetMac = "d0:73:d5:3b:64:b3";
char* target = "192.168.137.97";

char packetBuffer[255];
WiFiUDP Udp;
MyLifx lifx(Udp); //ToDo hier auch Mac adresse und co angeben damit man einfach mehrere lampen als objekt erzeugen kann

#define MOTION_SENSOR D3
#define LDR A0
Sensors sensors(MOTION_SENSOR, LDR);

void setup() {
  Serial.begin(9600);
  delay(3000);

  WiFiSetup::setup(ssid, password);
  RTC::setup();

  lifx.setup(WiFi.localIP(), target, targetMac);
  lifx.setPower(true);
  Serial.println("Lampe an");

}

void loop() {
  if(sensors.isMotion()) {
    Serial.print("Bewegung erkannt");
    Serial.print("Dunkel? ");
    Serial.println(sensors.isDark() ? 'Ja' : 'Nein');

    if(sensors.isDark()) {
      power = ! power;
      delay(10);
      lifx.setPower (power);
      Serial.println("\n \n \n");
      Serial.print("Lampe ist ");
      Serial.println(power ? 'an' : 'aus');
      Serial.print("Helligkeit: ");
      Serial.println(sensors.getBrightness());
      Serial.print("Uhrzeit: ");
      RTC::printNow();
    }
    
  }
  delay(10);
}
