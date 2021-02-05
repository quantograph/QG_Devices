#include <QG_Devices.h>

Bluetooth _bluetooth = Bluetooth();

//=================================================================================================
// Startup procedure, called before entering the "loop()" function
void setup() {
    _bluetooth.init();
    _bluetooth.setName("QuantoGraph");
}

//=================================================================================================
// The main loop. Called after "setup()" is done.
void loop() {
    _bluetooth.test();
    delay(100);
}
