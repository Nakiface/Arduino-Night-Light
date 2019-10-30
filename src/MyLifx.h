#include <WiFiUdp.h>
#include <ArduinoLifx.h>

#ifndef MYLIFX_H
#define MYLIFX_H
    class MyLifx 
    {
        public:
            MyLifx(WiFiUDP& udp);
            void setup(IPAddress myIp, const char* targetIp, const char* targetMac);
            void setBrightness(int Volume);
            void setPower(bool onOff);

        private:
            WiFiUDP udp;
            ArduinoLifx* lifx;

    };
#endif // !MYLIFX_H