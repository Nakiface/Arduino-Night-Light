#include "ESPAsyncWebServer.h"

#ifndef WEBSERVER_H
#define WEBSERVER_H

    class MyWebServer
    {
    private:
        AsyncWebServer* server;
    public:
        MyWebServer(AsyncWebServer* server);
        void begin();
    };

#endif // !WEBSERVER_H