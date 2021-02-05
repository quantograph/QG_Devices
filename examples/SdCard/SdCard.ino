#include <QG_Devices.h>

SdCard _sdCard = SdCard();

//=================================================================================================
// Startup procedure, called before entering the "loop()" function
void setup() {
    _sdCard.init();
    _sdCard.test();
}

//=================================================================================================
// The main loop. Called after "setup()" is done.
void loop() {
    delay(50);
}
