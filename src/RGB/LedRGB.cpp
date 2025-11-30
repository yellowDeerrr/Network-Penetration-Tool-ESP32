#include "RGB/LedRGB.h"

#define LED_BRIGHTNESS 2
#define INIT_BLINKS 3


void LedRGB::init(){
    pixel.begin();
    pixel.setBrightness(LED_BRIGHTNESS);
    setColor(INIT);
    blink(INIT_BLINKS);
}

void LedRGB::setColor(ColorsRGB color){
    // lastColor = pixel.gamma32(pixel.ColorHSV(colorHue)); // Hue goes from 0 to 65535 for full cycle
    // pixel.setPixelColor(0, lastColor);
    // pixel.show();
    lastColor = color;
    pixel.setPixelColor(0, lastColor);
    pixel.show();
}

void LedRGB::handle(unsigned long now){
   if(delayColor){
      if(now - startedDelayTime >= delayTime) {
         setColor(IDLE);
         delayColor = false;
      }
   }
}

void LedRGB::handleStatus(ColorsRGB status){
   switch (status) {
      case INIT:
         setColor(INIT);
         blink(INIT_BLINKS);
         break;

      case IDLE:
         setColor(IDLE);
         break;

      case ATTACK:
         setColor(ATTACK);
         break;

      case COMPLETED:
         setColor(COMPLETED);

         delayColor = true;
         startedDelayTime = millis();
         delayTime = 2000;
         break;

      case CANCELED:
         setColor(CANCELED);
         
         delayColor = true;
         startedDelayTime = millis();
         delayTime = 1000;
         break;

      case FAILED:
         setColor(ORANGE);
         blink(2);

         delayColor = true;
         startedDelayTime = millis();
         delayTime = 1000;
         break;

      case SCAN:
         setColor(CYAN);
         break;

      default:
         break;
   }
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
    //     turnOff();
    //     delay(150);

    //     if (lastColor != 0) {
    //         pixel.setPixelColor(0, lastColor);
    //     } else {
    //         // fallback color if LED was off
    //         pixel.setPixelColor(0, pixel.Color(255, 255, 255)); // white
    //     }

    //     setBrightness(LED_BRIGHTNESS);
    //     delay(150);
    // }

    // pixel.setPixelColor(0, lastColor);
    // setBrightness(firstBrightness);

    uint8_t firstBrightness = pixel.getBrightness();
    for (int i = 0; i < times; i++) {
        turnOff();
        delay(150);

        pixel.setPixelColor(0, lastColor == 0 ? WHITE : lastColor);
        setBrightness(LED_BRIGHTNESS);
        delay(150);
    }

    pixel.setPixelColor(0, lastColor);
    setBrightness(firstBrightness);
 }