#include <WiFiUdp.h>
#include <ArduinoLifx.h>

#ifndef LAMP_H
#define LAMP_H
    class Lamp 
    {
        public:
            Lamp(char* targetIP, char* targetMac);


        private:
            char* targetIP;
            char* targetMac;


    };
#endif // !LAMP_H