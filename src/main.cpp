#include <ESP8266WiFi.h>     
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <SPI.h>
#include <WiFiUdp.h>
#include <ArduinoLifx.h>
#include "MyLifx.h"
#include "Sensors.h"
#include "RTC.h"
#include "SettingsManager.h"

bool power = false;
int i = 1;
char* targetMac = "d0:73:d5:3b:64:b3";
char* target = "192.168.137.237";

char packetBuffer[255];
WiFiManager wifiManager;
WiFiUDP Udp;
MyLifx lifx(Udp); //ToDo hier auch Mac adresse und co angeben damit man einfach mehrere lampen als objekt erzeugen kann

#define MOTION_SENSOR D3
#define LDR A0
Sensors sensors(MOTION_SENSOR, LDR);

SettingsManager settings;

void setup() {
  Serial.begin(9600);
  delay(3000);
  wifiManager.autoConnect("Night Light");
  //WiFiSetup::setup(ssid, password);
  RTC::setup();

  lifx.setup(WiFi.localIP(), target, targetMac);
  lifx.setPower(true);
  lifx.setBrightness(5);
  Serial.println("Lampe an");
  int test = settings.getNightStart()["hour"];
  Serial.println(test);
}

void loop() {
  //lifx später 18 uhr früher 6 uhr 
  //lifx.setBrightness(1)
  
  // if (i == 1 & RTC::now().hour() == 15 & RTC::now().minute() < 2)
  // {
  //   Serial.println("schlatet auf helligkeit 1");
  //   delay(90000);
  //   lifx.setBrightness(1); 
  //   delay(90000);
  //   i=2;
  // }

  // if (i == 2 & RTC::now().hour() == 15 & RTC::now().minute() > 3)
  // {
  //   Serial.println("schlatet auf helligkeit 5");
  //   delay(90000);
  //   lifx.setBrightness(5);
  //   delay(90000);
  //   i=1;
  // }

  if(sensors.isMotion()) {
    Serial.println("Bewegung erkannt");
    Serial.print("Dunkel? ");
    Serial.println(sensors.isDark() ? "Ja" : "Nein");

    
    
    if(!sensors.isDark()) {
      power = ! power;
      delay(100);
      lifx.setPower (power);
      Serial.println("\n \n \n");
      Serial.print("Lampe ist ");
      Serial.println(power ? "an" : "aus");
      Serial.print("Helligkeit: ");
      Serial.println(sensors.getBrightness());
      Serial.print("Uhrzeit: ");
      RTC::printNow();
      
    }
  
    delay(10000);
  }
  delay(10);

}
