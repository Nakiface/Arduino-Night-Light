#include "SettingsManager.h"

SettingsManager::SettingsManager() {

}

void SettingsManager::loadSettings() {
    SPI.begin();
    SPIFFS.begin();
    Serial.println("loading settings");
    File settingsFile = SPIFFS.open("/settings.json", "r");

    if(!settingsFile) {
        Serial.println("no settings file found");
        setDefaultSettings();
        settingsFile = SPIFFS.open("/settings.json", "r");
    }

    StaticJsonDocument<1024> json;
    deserializeJson(json, settingsFile);
    settingsFile.close();

    nightStartHour = json["nightStart"]["hour"];
    nightStartMinute = json["nightStart"]["minute"];
    nightEndHour = json["nightEnd"]["hour"];
    nightEndMinute = json["nightEnd"]["minute"];
    nightBrightness = json["nightBrightness"];
    JsonArray jsonLamps = json["LIFX"];
    if(jsonLamps.size() > 0) {
        for(unsigned int i = 0; i < jsonLamps.size(); i++) {
            lamps.push_back(Lamp(jsonLamps[i]["ip"], jsonLamps[i]["mac"]));
        }
    }
}

void SettingsManager::setDefaultSettings() {
    Serial.println("saving default settings");
    File defaultSettingsFile = SPIFFS.open("/default-settings.json", "r");
    File settingsFile = SPIFFS.open("/settings.json", "w");

    if(!defaultSettingsFile) {
        Serial.println("failed to open default-settings.json file");
        return;
    }

    settingsFile.print(defaultSettingsFile.readString());
    settingsFile.flush();
    settingsFile.close();
    defaultSettingsFile.close();
}

void SettingsManager::saveSettings() {
    Serial.println("saving settings");
    File settingsFile = SPIFFS.open("/settings.json", "w");
    StaticJsonDocument<1024> json;
    JsonObject nightStart = json.createNestedObject("nightStart");
    nightStart["hour"] = nightStartHour;
    nightStart["minute"] = nightStartMinute;
    JsonObject nightEnd = json.createNestedObject("nightEnd");
    nightEnd["hour"] = nightEndHour;
    nightEnd["minute"] = nightEndMinute;
    json["nightBrightness"] = nightBrightness;
    JsonArray jsonLamps = json.createNestedArray("LIFX");
    for(int i = 0; i < lamps.size(); i++) {
        JsonObject jsonLamp = jsonLamps.createNestedObject();
        jsonLamp["ip"] = lamps[i].getIP();
        jsonLamp["mac"] = lamps[i].getMac();
    }
    serializeJsonPretty(json, settingsFile);
    settingsFile.close();
}

void SettingsManager::setNightStart(int hour, int minute) {
    if(hour < 0 || hour > 23) return;
    if(minute < 0 || minute > 59) return;
    Serial.printf("setting night start time to %02d:%02d\n", hour, minute);
    nightStartHour = hour;
    nightStartMinute = minute;
    saveSettings();
}

int SettingsManager::getNightStartHour() {
    return nightStartHour;
}

int SettingsManager::getNightStartMinute() {
    return nightStartMinute;
}

void SettingsManager::setNightEnd(int hour, int minute) {
    if(hour < 0 || hour > 23) return;
    if(minute < 0 || minute > 59) return;
    Serial.printf("setting night end time to %02d:%02d\n", hour, minute);
    nightEndHour = hour;
    nightEndMinute = minute;
    saveSettings();
}

int SettingsManager::getNightEndHour() {
    return nightEndHour;
}

int SettingsManager::getNightEndMinute() {
    return nightEndMinute;
}

void SettingsManager::setNightBrightness(int nightBrightness) {
    Serial.println("setting night brightness");
    this->nightBrightness = nightBrightness;
    saveSettings();
}

int SettingsManager::getNightBrightness() {
    return nightBrightness;
}

void SettingsManager::addLamp(const char* mac, const char* ip) {
    Serial.printf("adding lamp with mac: %s and ip: %s\n", mac, ip);
    lamps.push_back(Lamp(ip, mac));
    saveSettings();
}

void SettingsManager::removeLamp(int index) {
    Serial.println("removing lamp");
    if(lamps.size() > index) {
        lamps.erase(lamps.begin() + index);
        saveSettings();
    }
}

void SettingsManager::updateLamp(int index, const char* mac, const char* ip) {
    lamps[index].setMac(mac);
    lamps[index].setIP(ip);
    saveSettings();
}


std::vector<Lamp> SettingsManager::getLamps() {
    return lamps;
}

