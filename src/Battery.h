// LED.h - all definitions for the LED's
#ifndef Battery_h
#define Battery_h

class Battery {
public:
    void init();
    void getState(bool& power, bool& low, bool& full);

    #define BATT_LOW 3 // Teensy pin for the "Low Battery" indicator. . Input LOW - red LED is on (reversed).
    #define BATT_POWER 6 // Teensy pin for the "Charger is plugger in" indicator. Input LOW - amber LED is on (reversed).
    #define BATT_FULL 40 // Teensy pin for the "Battery is fully charged" indicator. Input LOW - green LED is on (reversed).
};

#endif
