#include <SPI.h>
#include <FS.h>
#include <Arduino.h>
#include "ArduinoJson.h"
#include "Lamp.h"

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

    class SettingsManager {
        public:
            SettingsManager();

            void loadSettings();
            void setDefaultSettings();
            void saveSettings();

            void setNightStart(int hour, int minute);
            int getNightStartHour(); 
            int getNightStartMinute();

            void setNightEnd(int hour, int minute);
            int getNightEndHour();
            int getNightEndMinute();

            void setNightBrightness(int nightBrightness);
            int getNightBrightness(); 

            void addLamp(const char* mac, const char* ip);
            void updateLamp(int index, const char* mac, const char* ip);
            void removeLamp(int index);
            std::vector<Lamp> getLamps();

        protected:
            int nightStartHour;
            int nightStartMinute;
            int nightEndHour;
            int nightEndMinute;
            int nightBrightness;
            std::vector<Lamp> lamps;

    };

#endif // !SETTINGSMANAGER_H