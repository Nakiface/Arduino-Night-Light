#include "MyWebServer.h"

MyWebServer::MyWebServer(AsyncWebServer* server) : server(server)
{

}

void MyWebServer::begin()
{
    //Web Server
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });
    
    // Route to load style.css file
    server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });
    
    server->begin();
}