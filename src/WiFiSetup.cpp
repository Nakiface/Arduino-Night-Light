#include "WiFiSetup.h"

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

void WiFiSetup::setup(const char* ssid,const char* password)
{
    delay(10);

        Serial.print("Connect to Wifi");

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
            Serial.print(".");
    }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.print("IP adress: ");
        Serial.println(WiFi.localIP());
}