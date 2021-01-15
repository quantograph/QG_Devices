#include <QG_Devices.h>

AudioSettings _settings{};
AudioBoard _audio = AudioBoard();
int _count = 0;

//=================================================================================================
// Startup procedure, called before entering the "loop()" function
void setup() {
    // Open the serial port
    Serial.begin(152000);
    while (!Serial && (millis() <= 1000));

    _audio.init(&_settings);
}

//=================================================================================================
// The main loop. Called after "setup()" is done.
void loop() {
    _audio.process();

    if(_count % 10 == 0)
      _audio.setInput(Inputs::mic);

    if(_count % 20 == 0)
      _audio.setInput(Inputs::line);
      
    _count++;
    delay(100);
}