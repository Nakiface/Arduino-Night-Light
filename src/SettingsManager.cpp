#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    File settingsFile = SD.open("/settings.json");
    if(!settingsFile) {
        setDefaultSettings();
        return;
    }

    auto error = deserializeJson(json, settingsFile);
    if (error) {
        setDefaultSettings();
        return;
    }

    settingsFile.close();

    
}

void SettingsManager::setDefaultSettings() {
    setNightStart(22, 0);
    setNightEnd(6, 0);
    setNightBrightness(2);
    saveSettings();
    serializeJson(json, Serial);
}

void SettingsManager::saveSettings() {
    File settingsFile = SD.open("/settings.json", FILE_WRITE);
    serializeJson(json, settingsFile);
    settingsFile.close();
}

void SettingsManager::setNightStart(int hour, int minute) {
    if(hour < 0 || hour > 23) return;
    if(minute < 0 || minute > 59) return;
    JsonObject nightStart = json.createNestedObject("nightStart");
    nightStart["hour"] = hour;
    nightStart["minute"] = minute;
}

int SettingsManager::getNightStartHour() {
    return json.getMember("nightStart")["hour"]; 
}

int SettingsManager::getNightStartMinute() {
    return json.getMember("nightStart")["minute"]; 
}

void SettingsManager::setNightEnd(int hour, int minute) {
    if(hour < 0 || hour > 23) return;
    if(minute < 0 || minute > 59) return;
    JsonObject nightEnd = json.createNestedObject("nightEnd");
    nightEnd["hour"] = hour;
    nightEnd["minute"] = minute;
}

int SettingsManager::getNightEndHour() {
    return json.getMember("nightEnd")["hour"]; 
}

int SettingsManager::getNightEndMinute() {
    return json.getMember("nightEnd")["minute"]; 
}

void SettingsManager::setNightBrightness(int nightBrightness) {
    json["nightBrightness"] = nightBrightness;
}

int SettingsManager::getNightBrightness() {
    int nightBrightness = json["nightBrightness"];    
    return nightBrightness;
}

void SettingsManager::addTarget(char* mac, char* ip) {
    JsonArray lifx = json.createNestedArray("lifx");
    JsonObject lifx_elem = lifx.createNestedObject();
    lifx_elem["mac"] = mac;
    lifx_elem["ip"] = ip;
}

char** SettingsManager::getTargets() {
    JsonArray lifx = json.getMember("lifx");
    char[lifx.size][2] targets;
    for(int i = 0; i < lifx.size; i++) {
        targets[i][0] = lifx[0]["mac"];
        targets[i][1] = lifx[0]["ip"];
    }

    return targets;
}