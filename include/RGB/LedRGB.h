#pragma once

#include <Adafruit_NeoPixel.h>

#define RGB_PIN     48      // Onboard RGB LED pin
#define NUM_PIXELS  1       // Only one LED

// enum ColorsHue{
//     RED     = 0,            
//     YELLOW  = 10922,        
//     GREEN   = 21845,       
//     BLUE    = 43690,      

//     CYAN    = 32768,       
//     AQUA    = 38229,        
//     PURPLE  = 49152,       
//     MAGENTA = 54613,        
//     PINK    = 60074,        

//     WHITE   = 65535,

//     ATTACK = RED,
//     IDLE = GREEN,
//     INIT = YELLOW,
//     CANCELED = MAGENTA
// };

enum ColorsRGB {
    RED      = 0xFF0000,
    GREEN    = 0x00FF00,
    // BLUE     = 0x0000FF,
    YELLOW   = 0xFFFF00,
    CYAN     = 0x00FFFF,
    MAGENTA  = 0xFF00FF,
    WHITE    = 0xFFFFFF,
    ORANGE   = 0xFFA500,

    INIT     = WHITE,
    IDLE     = GREEN,
    ATTACK   = RED,
    COMPLETED = MAGENTA,
    CANCELED = YELLOW,
    FAILED = ORANGE,
    SCAN = CYAN
};

class LedRGB {
private:
    uint32_t lastColor = 0;
    Adafruit_NeoPixel pixel;

    bool delayColor = false;
    unsigned long startedDelayTime = 0;
    unsigned int delayTime = 0;

public:
    LedRGB() : pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800) {};
    void init();
    void handle(unsigned long now);
    void setColor(ColorsRGB color);
    void handleStatus(ColorsRGB status);
    void turnOff();
    void turnOn();
    void setBrightness(uint8_t value);
    void blink(int times);
};