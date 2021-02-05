#pragma once

class Bluetooth {
public:
    Bluetooth();
    bool init();
    bool send(const char* buffer, int size);
    bool receive();
    bool command(const char* request, String& response);
    bool setName(const char* name);
    bool process();
    void test();

    #define BUFFER_SIZE 1024
    #define KEY_PIN 2
    char _buffer[BUFFER_SIZE];
    int _packetSize = 0;
    int _received = 0; // Received
    char _string[64];
};
