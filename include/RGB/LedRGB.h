#pragma once

#include <Adafruit_NeoPixel.h>

#define RGB_PIN     48      // Onboard RGB LED pin
#define NUM_PIXELS  1       // Only one LED

enum ColorsHue{
    GREEN = 21845,
    RED = 0,
    YELLOW = 10922,
    BLUE = 43690
};

class LedRGB {
private:
    uint32_t lastColor = 0;
    Adafruit_NeoPixel pixel;

public:
    LedRGB() : pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800) {};
    void init();
    void setColor(ColorsHue color);
    void turnOff();
    void turnOn();
    void setBrightness(uint8_t value);
    void blink(int times);
};