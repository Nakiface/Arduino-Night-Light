#include "Sensors.h"
#include "Arduino.h"

Sensors::Sensors(int motionSensorPin, int ldrPin) : motionSensorPin(motionSensorPin), ldrPin(ldrPin)
{
    pinMode(motionSensorPin, INPUT);
    pinMode(ldrPin, INPUT);
}

bool Sensors::isMotion() 
{
    return digitalRead(motionSensorPin) == HIGH;
    
}

bool Sensors::isDark()
{
    return getBrightness() < 800;
}

int Sensors::getBrightness() 
{
    return analogRead(ldrPin);
}