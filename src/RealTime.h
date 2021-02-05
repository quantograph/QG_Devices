#pragma once

#include <Arduino.h>
#include <TimeLib.h>

class RealTime
{
public:
    bool init();
    String show();
    bool sync();
    static time_t getTeensy3Time();
};
