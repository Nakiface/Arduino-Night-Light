#include "MyLifx.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoLifx.h>

MyLifx::MyLifx(WiFiUDP& udp) : udp(udp)
{
    lifx = new ArduinoLifx(udp);
}

void MyLifx::setup(IPAddress myIp, const char* targetIp, const char* targetMac)
{
    lifx->begin(myIp, targetIp, targetMac);
    lifx->setFlags(0,0,1);
}
        
void MyLifx::setBrightness(int Volume)
{
    int brightness = 0;
    switch (Volume) 
    {
        case 1:
            brightness = 1000;
        break;
        case 2:
            brightness = 10000;
            break;
        case 3:
            brightness = 20000;
            break;
        case 4:
            brightness = 45000;
            break;
        case 5:
            brightness = 65000;
            break;
        default:
            Serial.println("keine gültiger eintrag für die Helligkeit!");
            break;
        }
        lifx->setColor(30, 100, brightness, 3500, 10);
    }

void MyLifx::setPower (bool onOff)
    {
        lifx->setPower(onOff, 200);
    }
