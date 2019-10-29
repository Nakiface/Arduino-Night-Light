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

    serializeJson(json, Serial);
}

void SettingsManager::setDefaultSettings() {
    setNightStart(22, 0);
    setNightEnd(6, 0);
    setNightBrightness(2);
    saveSettings();
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

JsonObject SettingsManager::getNightStart() {
    StaticJsonDocument<200> buf;
    JsonObject nightStart = buf.createNestedObject();
    nightStart["hour"] = json.createNestedObject("nightStart")["hour"];
    nightStart["minute"] = json.createNestedObject("nightStart")["minute"];

    return nightStart; 
}

void SettingsManager::setNightEnd(int hour, int minute) {
    if(hour < 0 || hour > 23) return;
    if(minute < 0 || minute > 59) return;
    JsonObject nightEnd = json.createNestedObject("nightEnd");
    nightEnd["hour"] = hour;
    nightEnd["minute"] = minute;
}

JsonObject SettingsManager::getNightEnd() {
    StaticJsonDocument<200> buf;
    JsonObject nightEnd = buf.createNestedObject();
    nightEnd["hour"] = json.createNestedObject("nightEnd")["hour"];
    nightEnd["minute"] = json.createNestedObject("nightEnd")["minute"];

    return nightEnd;
}

void SettingsManager::setNightBrightness(int nightBrightness) {
    json["nightBrightness"] = nightBrightness;
}

// int SettingsManager::getNightBrightness() {
//     int nightBrightness = json["nightBrightness"];    
//     return nightBrightness;
// }

void SettingsManager::addTarget(char* mac, char* ip) {
    JsonArray lifx = json.createNestedArray("lifx");
    JsonObject lifx_elem = lifx.createNestedObject();
    lifx_elem["mac"] = mac;
    lifx_elem["ip"] = ip;
}