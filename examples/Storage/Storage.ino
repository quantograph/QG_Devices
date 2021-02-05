#include <QG_Devices.h>

Storage _storage = Storage();

//=================================================================================================
// Startup procedure, called before entering the "loop()" function
void setup() {
    _storage.test();
}

//=================================================================================================
// The main loop. Called after "setup()" is done.
void loop() {
    delay(50);
}
