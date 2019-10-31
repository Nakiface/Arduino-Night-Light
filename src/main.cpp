#include <ESP8266WiFi.h>     
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include "MyWebServer.h"
#include <ESPAsyncWiFiManager.h>
#include <SPI.h>
#include <WiFiUdp.h>
#include <ArduinoLifx.h>
#include "MyLifx.h"
#include "Sensors.h"
#include "RTC.h"
#include "SettingsManager.h"

//Variablen zum Steuern der Logik
bool power = false;
bool changeBrightness = true;



//Erzeugen der verwendeten Klassen
AsyncWebServer server(80);
DNSServer dns;
AsyncWiFiManager wifiManager(&server, &dns);
SettingsManager settings;
MyWebServer webServer(&server, &settings);
WiFiUDP Udp;
MyLifx lifx(Udp); 

//Eingänge der Sensoren Deklareren und das Erzeugen der Sensoren Klasse
#define MOTION_SENSOR D3
#define LDR A0
Sensors sensors(MOTION_SENSOR, LDR);


void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPIFFS.begin();
  delay(4000);

  //Setup von WiFi, Uhr und lifx SmartLamp
  wifiManager.autoConnect("Night Light", "LIFX1234"); 
  RTC::setup(); 
  settings.loadSettings();
  lifx.setup(WiFi.localIP(), settings.getLamps()[0].getIP(), settings.getLamps()[0].getMac());

  webServer.begin();


}



void loop() {
  
  //Die Helligkeit der Lampe wird eingestellt. Hier brauchen wir ein langes Delay weil sich das setzen der Helligkeit
  //und das an- und ausschalten der Lampe sonst gegenseitig behindern
  if (changeBrightness && RTC::now().hour() == settings.getNightStartHour() && RTC::now().minute() > settings.getNightStartMinute())
  {
    delay(90000);
    lifx.setBrightness(settings.getNightBrightness()); 
    delay(90000);
    changeBrightness = false;
  }

  if (!changeBrightness && RTC::now().hour() == settings.getNightEndHour() && RTC::now().minute() > settings.getNightEndMinute())
  {
    delay(90000);
    lifx.setBrightness(5);
    delay(90000);
    changeBrightness = true;
  }
 
  //Wenn bewegung und kein lich oder bewegung und lampe ist an wahr ist wird die lampe an bzw. aus geschaltet
  //damit die lampe nicht schnell hin und her schlatet bei bewegung haben wir ein 10 sek pausefenster
  if(sensors.isMotion() && (sensors.isDark() || power)) {
    power = ! power;
    delay(100);
    lifx.setPower (power);
    delay(10000);      
  }  

  delay(10);
}
