#include "Definitions.h"
#include "Bluetooth.h"

/*
Datasheet: https://www.mouser.com/datasheet/2/306/hc06-1324356.pdf

Connections:
BT board -> Teensy
     TXD -> pin 0, RX1
     RXD -> pin 1, TX1

Protocol
--------
2 bytes - packet size
packet:
    2 bytes - tag number
    tag value


Tags:
1 - note info:
    2 - instrument, string: rhythmGuitar, leadGuitar, bassGuitar, drums
    3 - MIDI note number or drum name for "drums": 
            tamborine, bass, snare_low, snare_high, tom_low, tom_mid, tom_high, crash_low, crash_high, ride_shoulder
    4 - volume, 0 - 127
    5 - string number (for guitars)
*/

// Separators:
#define PACKET_START 1 // Start of packet
#define PACKET_END 2 // Start of packet
#define TAG_END 3 // End of tag number
#define VALUE_END 4 // End of tag value
#define GROUP_END 5 // End of group of tags

//=================================================================================================
Bluetooth::Bluetooth() {
}

//=================================================================================================
bool Bluetooth::init() {
    Serial.printf("BT starting...\n");
    Serial1.begin(9600, SERIAL_8N1); // RXD on Bluetooth goes to pin 1 on Teensy, TXD -> pin 0
    Serial.printf("BT started...\n");

    pinMode(KEY_PIN, OUTPUT);
    digitalWrite(KEY_PIN, LOW);

    return true;
}

//=================================================================================================
bool Bluetooth::send(const char* buffer, int size) {
    Serial1.write(buffer, size);
    return true;
}

//=================================================================================================
bool Bluetooth::receive() {
    //Serial.printf("Serial1.available()=%d\n", Serial1.available());
    while(Serial1.available() > 0 && _received < BUFFER_SIZE - 1) {
        _buffer[_received++] = (char)Serial1.read();
    }

    _buffer[_received] = 0;
    //Serial.printf("_received=%d\n", _received);

    if(_received > 0)
        return true;
    else
        return false;
}

//=================================================================================================
// Changes the module name visible in 'scan'
bool Bluetooth::setName(const char* name) {
    String request{};
    String response{};

    request = "AT+NAME";
    request += name;
    command(request.c_str(), response);
    if(response != "OKsetname") {
        Serial.printf("##### ERROR: can't set name: %s\n", response.c_str());
    }

    return true;
}

//=================================================================================================
// Sends an AT command
bool Bluetooth::command(const char* request, String& response) {
    size_t length{0};
    size_t sent{0};
    bool ret{false};

    // Switch to AT command mode
    digitalWrite(KEY_PIN, HIGH);
    delay(100);

    // Send the command
    length = strlen(request);
    sent = Serial1.write(request, length);
    if(sent != length) {
        response = "ERROR: can't send";
        ret = false;
    } else {
        // Wait for the response
        _received = 0;
        for(int i = 0; i < 30; ++i) {
            if(Serial1.available() > 0) {
                while(Serial1.available() > 0) {
                    receive();
                    response += _buffer;
                    delay(100);
                }
            
                Serial.printf("Command: %s -> %s\n", request, response.c_str());
                ret = true;
                break;
            } else {
                delay(100);
            }
        }

        if(!ret)
            response = "ERROR: no response";
    }

    // Switch to tramsmission mode
    digitalWrite(KEY_PIN, LOW);
    delay(100);

    return ret;
}

//=================================================================================================
bool Bluetooth::process() {

    return true;
}

//=================================================================================================
void Bluetooth::test() {
    if(receive()) {
        Serial.printf("BT: %s\n", _buffer);
        send(_buffer, _received);
        _received = 0;
    }
}
