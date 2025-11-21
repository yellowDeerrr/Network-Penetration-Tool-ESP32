#include "RGB/LedRGB.h"

#define LED_BRIGHTNESS 2

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void LedRGB::init(){
    pixel.begin();
    pixel.setBrightness(LED_BRIGHTNESS);
    setColor(YELLOW);
    blink(5);
}

void LedRGB::setColor(ColorsHue colorHue){
    uint32_t color = pixel.gamma32(pixel.ColorHSV(colorHue)); // Hue goes from 0 to 65535 for full cycle
    pixel.setPixelColor(0, color);
    pixel.show();
}

 void LedRGB::turnOff(){
    pixel.clear();
    pixel.show();
 }

 void LedRGB::turnOn(){
    pixel.begin();
 }

 void LedRGB::setBrightness(uint8_t value){
    pixel.setBrightness(value);
    pixel.show();
 }

 void LedRGB::blink(int times){
    // uint8_t firstBrightness = pixel.getBrightness();
    // for(int i = 0; i < times; i++){
    //     setBrightness(0);
    //     delay(150);

    //     setBrightness(LED_BRIGHTNESS);
    //     delay(150);
    // }
    // setBrightness(firstBrightness);

    uint8_t firstBrightness = pixel.getBrightness();
    uint32_t currentColor = pixel.getPixelColor(0); 
    for(int i = 0; i < times; i++){
        turnOff();
        delay(150);

        pixel.setPixelColor(0, currentColor);

        setBrightness(LED_BRIGHTNESS);
        delay(150);
    }

    pixel.setPixelColor(0, currentColor);
    setBrightness(firstBrightness);
 }