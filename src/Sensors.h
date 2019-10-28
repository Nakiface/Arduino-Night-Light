#ifndef SENSORS_H
#define SENSORS_H

    class Sensors {
        public:
            Sensors(int motionSensorPin, int ldrPin);
            bool isMotion();
            bool isDark();
            int getBrightness();

        private:
            int motionSensorPin; // The motion sensor
            int ldrPin; // The LDR
            
    };
#endif // !SENSORS_H