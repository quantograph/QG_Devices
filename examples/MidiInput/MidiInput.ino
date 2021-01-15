#include <QG_Devices.h>

MidiInput _midiInput = MidiInput();

// the setup function runs once when you press reset or power the board
void setup() {
    _midiInput.init(true);
}

// the loop function runs over and over again until power down or reset
void loop() {
    _midiInput.process();

    delay(100);
}
