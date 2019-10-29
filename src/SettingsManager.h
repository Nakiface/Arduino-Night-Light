#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#include "ArduinoJson.h"

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

    class SettingsManager {
        public:
            SettingsManager();
            void setDefaultSettings();
            void saveSettings();


            void setNightStart(int hour, int minute);
            JsonObject getNightStart();

            void setNightEnd(int hour, int minute);
            JsonObject getNightEnd();

            void setNightBrightness(int nightBrightness);
            //int getNightBrightness(); 

            void addTarget(char* mac, char* ip);

        protected:
            StaticJsonDocument<512> json;

    };

#endif // !SETTINGSMANAGER_H