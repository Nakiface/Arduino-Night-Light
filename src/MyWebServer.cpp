#include "MyWebServer.h"

MyWebServer::MyWebServer(AsyncWebServer *server, SettingsManager *settings) : server(server), settings(settings)
{
}

void MyWebServer::begin()
{
  //Web Server
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Route to load favicon.png file
  server->on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/favicon.png", "image/png");
  });

  // Route to load bundle.css file
  server->on("/bundle.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/bundle.css", "text/css");
  });

  // Route to load bundle.js file
  server->on("/bundle.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/bundle.js", "text/javascript");
  });

  // Route to load settings.json file
  server->on("/settings.json", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/settings.json", "application/json");
  });

  // Route to save settings.json file
  // server->on("/savesettings", HTTP_POST, [](AsyncWebServerRequest *request)
  // {
  //   if(request->hasParam("body", true)) {
  //     AsyncWebParameter* p = request->getParam("body", true);
  //     String json = p->value();

  //     File settingsFile = SPIFFS.open("/settings.json", "w");
  //       settingsFile.print(json);
  //     settingsFile.close();
  //   }

  //     request->send(200);
  // });
  server->onRequestBody([this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  
    if(!index){
      Serial.printf("BodyStart: %u B\n", total);
      this->postBodyBuffer = (char*) malloc(total * sizeof(char));
    }
    for(size_t i=0; i<len; i++){
      this->postBodyBuffer[index + i] = data[i];
    }
    
    if(index + len == total){
      StaticJsonDocument<1024> json;
      File settingsFile = SPIFFS.open("/settings.json", "w");
      deserializeJson(json, this->postBodyBuffer);
      serializeJsonPretty(json, Serial);
      serializeJsonPretty(json, settingsFile);
      settingsFile.close();
      delete this->postBodyBuffer;
      Serial.println();
      Serial.printf("BodyEnd: %u B\n", total);
      this->settings->loadSettings();
    }

    request->send(200);
  });

  AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/savesettings", [](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject jsonObj = json.as<JsonObject>();
    serializeJsonPretty(jsonObj, Serial);
    // ...
  });
  server->addHandler(handler);

  server->begin();
}