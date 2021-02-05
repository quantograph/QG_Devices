// LED - all functions for the LED's
#include "Definitions.h"
#include "LED.h"

//=================================================================================================
bool Led::Init(int redPin, int greenPin, int bluePin, float level) {
    _level = level;

    // RGB LED pins
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);

    GetAllHues();
    SetPwmFrequency(10000);

    return true;
}

//=================================================================================================
void Led::SetPwmFrequency(int frequency) {
    analogWriteFrequency(_redPin, frequency);
    analogWriteFrequency(_greenPin, frequency);
    analogWriteFrequency(_bluePin, frequency);
}

//=================================================================================================
// Gets colors of all hues
bool Led::GetAllHues() {
    int index = 0;

    GetHues(index, COLOR(255,   0,   0),  0,  1,  0);
    GetHues(index, COLOR(255, 255,   0), -1,  0,  0);
    GetHues(index, COLOR(0,   255,   0),  0,  0,  1);
    GetHues(index, COLOR(0,   255, 255),  0, -1,  0);
    GetHues(index, COLOR(0,     0, 255),  1,  0,  0);
    GetHues(index, COLOR(255,   0, 255),  0,  0, -1);

    return true;
}

//=================================================================================================
// Gets hues for two colors
bool Led::GetHues(int& index, const COLOR& color, int redMove, int greenMove, int blueMove) {
    COLOR listColor;
    int	i = 0;
    int	red = color._red;
    int	green = color._green;
    int	blue = color._blue;

    for(i = 0; i < 256; i++, index++) {
        _hues[index]._red = red;
        _hues[index]._green = green;
        _hues[index]._blue = blue;

        // Increment all values
        red += redMove;
        green += greenMove;
        blue += blueMove;
    }

    return true;
}

//=================================================================================================
void Led::SetLevel(float level) {
    _level = level;
}

//=================================================================================================
// Gets the next LED color
void Led::NextColor(int& color, int& increment) {
    int min = 0;
    int max = 255;

    // Get the next color
    if(increment > 0 && color >= max) {
        color = max;
        increment = -increment;
    } else if(increment < 0 && color <= min) {
        color = min;
        increment = -increment;
    } else if(random() % 100 == 0)
        increment = -increment;

    color += increment;
}

//=================================================================================================
void Led::SetHue(int hue) {
    SetColor(_hues[hue]._red * _level, _hues[hue]._green * _level, _hues[hue]._blue * _level);
}

//=================================================================================================
void Led::SetRandomHue() {
    int hue = random() % HUES;
    SetColor(_hues[hue]._red * _level, _hues[hue]._green * _level, _hues[hue]._blue * _level);
}

//=================================================================================================
// Sets color of RGB LED's
// All values are from 0 to 255
bool Led::SetColor(byte red, byte green, byte blue) {
    analogWrite(_redPin, red);
    analogWrite(_greenPin, green);
    analogWrite(_bluePin, blue);

    /*analogWrite(_redPin, _ledTable[red]);
    analogWrite(_greenPin, _ledTable[green]);
    analogWrite(_bluePin, _ledTable[blue]);*/

    return true;
}

//=================================================================================================
// Test of LED linear brightness
void Led::Test() {
	Serial.println("LedTest");
	
    static int red = 127;
    static int green = 127;
    static int blue = 127;
    static int redInc = 1;
    static int greenInc = 1;
    static int blueInc = 1;
    static int hue = 0;

    if(hue >= HUES - 1)
        hue = 0;

    //SetColor(_hues[hue]._red * level, _hues[hue]._green * level, _hues[hue]._blue * level);

    SetColor(red, green, blue);
    NextColor(red, redInc);
    NextColor(green, greenInc);
    NextColor(blue, blueInc);

    //hue += 1;
}

//=================================================================================================
void Led::Play(uint32_t touched) {
    if(touched)
        SetRandomHue();
    else
        SetColor(0, 0, 0);
}
