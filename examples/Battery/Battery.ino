#include <QG_Devices.h>

TouchScreen _screen = TouchScreen();
Battery _battery = Battery();

//=================================================================================================
// Startup procedure, called before entering the "loop()" function
void setup() {
    _screen.init();
    _screen._screen.setTextColor(ILI9341_WHITE);
    _screen._screen.setTextSize(2);

    _battery.init();
}

//=================================================================================================
// The main loop. Called after "setup()" is done.
void loop() {
    char buffer[128];
    bool power;
    bool low;
    bool full;

    _battery.getState(power, low, full);

    // Send the status to the serial port
    Serial.printf("power=%d, low=%d, full=%d\n", power, low, full);

    // Show the status on the screen
    _screen._screen.fillRect(0, 0, _screen._width, _screen._height, ILI9341_BLACK);
    _screen._screen.setCursor(0, 0);
    sprintf(buffer, "power=%d\nlow=%d\nfull=%d", power, low, full);
    _screen._screen.print(buffer);

    delay(1000);
}
