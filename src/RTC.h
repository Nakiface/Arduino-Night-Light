#include "RTClib.h"
#include "Arduino.h"

#ifndef RTC_H
#define RTC_H

    class RTC {
        public:
            static void setup();
            static DateTime now();
            static void printNow();

        private:
            static RTC_DS3231 rtc;
    };

#endif // !RTC_H