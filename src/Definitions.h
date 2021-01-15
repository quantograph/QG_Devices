#pragma once

#include <limits>
#include <vector>
#include <list>
#include <float.h>

#include <Arduino.h>
#include <Math.h>
#include <Audio.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <TimeLib.h>

// Audio inputs
enum Inputs {
    none,
    mic,
    line
};

// Audio setting
struct AudioSettings {
    Inputs _input{Inputs::mic}; // Mic or line in
    float _micGain{0.3}; // Microphone gain (0.0 - 1.0)
    float _lineInLevel{0.5}; // (0.0 - 1.0)
};

#define MIC_GAIN_MAX 63 // 0 - 63
#define LINE_IN_MAX 15 // 0 - 15
#define VOLUME_MAX 1023