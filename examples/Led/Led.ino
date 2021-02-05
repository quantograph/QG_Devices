#include <QG_Devices.h>

Led _led = Led();

void setup() {
    _led.Init(14, 24, 15, 1.0);
}

void loop() {
    _led.Test();

    delay(3);
}
