#include <QG_Devices.h>

TouchScreen _screen = TouchScreen();

// the setup function runs once when you press reset or power the board
void setup() {
    _screen.init();
    _screen._screen->setTextColor(ILI9341_WHITE);
    _screen._screen->setTextSize(2);

    Serial.printf("Screen resolution: width=%d, height=%d\n\n", _screen._width, _screen._height);

    Serial.printf("aaa\n");
}

// the loop function runs over and over again until power down or reset
void loop() {
    bool touched{_screen.read()}; // Whether the screen is being touched
    char buffer[128];

    _screen._screen->fillRect(0, 0, _screen._width, _screen._height, ILI9341_BLACK);
    _screen._screen->setCursor(0, 0);

    if(touched) {
        // Print the touch point to the serial port
        Serial.printf("Touched: x=%3d, y=%3d\n", 
                      _screen._x, _screen._y);

        // Show the touch point on the screen
        sprintf(buffer, "Touched:\n x=%3d\n y=%3d",
                _screen._x, _screen._y);
        _screen._screen->print(buffer);
    } else {
        _screen._screen->print("Not touched");
    }

    delay(100);
}
