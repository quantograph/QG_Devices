#include <QG_Devices.h>

RealTime _time = RealTime();
TouchScreen _screen = TouchScreen();

//=================================================================================================
// Startup procedure, called before entering the "loop()" function
void setup() {
    _screen.init();
    _screen._screen.setTextColor(ILI9341_WHITE);
    _screen._screen.setTextSize(2);

    _time.init();
    _time.sync();
}

//=================================================================================================
// The main loop. Called after "setup()" is done.
void loop() {
    String time = _time.show();

    _screen._screen.fillRect(0, 0, _screen._width, _screen._height, ILI9341_BLACK);
    _screen._screen.setCursor(0, 0);
    _screen._screen.print(time);

    delay(1000);
}
