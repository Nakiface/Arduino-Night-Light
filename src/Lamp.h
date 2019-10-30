#include <WiFiUdp.h>
#include <ArduinoLifx.h>

#ifndef LAMP_H
#define LAMP_H
    class Lamp 
    {
        public:
            Lamp(const char* ip, const char* mac);
            const char* getIP();
            void setIP(const char* ip);
            const char* getMac();
            void setMac(const char* mac);


        private:
            const char* ip;
            const char* mac;


    };
#endif // !LAMP_H