#include "Definitions.h"
#include "Battery.h"

// Battery - battery charger state

//=================================================================================================
void Battery::init()
{
    pinMode(BATT_LOW, INPUT);
    pinMode(BATT_POWER, INPUT);
    pinMode(BATT_FULL, INPUT);
}

//=================================================================================================
void Battery::getState(bool& power, bool& low, bool& full)
{
    power = !digitalRead(BATT_POWER); // LED goes to power
    low = digitalRead(BATT_POWER); // LED goes to ground
    full = !digitalRead(BATT_FULL); // LED goes to power
}
