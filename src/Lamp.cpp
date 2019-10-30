#include "Lamp.h"

Lamp::Lamp(const char* ip, const char* mac) : ip(ip), mac(mac)
{
  
}

const char* Lamp::getIP() {
    return ip;
}

void Lamp::setIP(const char* ip)
{
    this->ip = ip;
}

const char* Lamp::getMac() {
    return mac;
}

void Lamp::setMac(const char* mac)
{
    this->mac = mac;
}