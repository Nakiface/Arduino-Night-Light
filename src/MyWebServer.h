#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "SettingsManager.h"

#ifndef WEBSERVER_H
#define WEBSERVER_H

    class MyWebServer
    {
    private:
        AsyncWebServer* server;
        SettingsManager* settings;
        char* postBodyBuffer;
        
    public:
        MyWebServer(AsyncWebServer* server, SettingsManager* settings);
        void begin();
    };

#endif // !WEBSERVER_H