#include <Arduino.h>
#include <WiFi.h>

#include "Networks/Services/WifiService.h"
#include "Networks/Services/AttackService.h"

#include "Web/Web.h"

#include "RGB/LedRGB.h"

#define DEBOUNCE_BUTTON_TIME 300

LedRGB led;
WifiService wifi(led);
AttackService attackService(led);
Web server(led, wifi);


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

    led.setColor(IDLE);
}

unsigned long now, lastButtonPress = 0;

void loop(){
    now = millis();
    server.handle();
    led.handle();

    if(!digitalRead(0) && now - lastButtonPress >= DEBOUNCE_BUTTON_TIME){
        if (attackService.getCurrentStatus() == attack_status_t::Running) {
            attackService.stopAttack();
            led.handleStatus(CANCELED);
        }else{
            MacAddress apMac = MacAddress::fromString("TARGET_AP");
            MacAddress staMac = MacAddress::fromString("TARGET_STA");
            
            attackService.startDeauthAttack(apMac, staMac, 10);
            
            // led.setColor(GREEN);

            // Serial.println(attackService.getExecutionTime());

            // led.setColor(RED);
            // wifi.scanAPs();

            // std::vector<AccessPoint> nets = wifi.getScannedAPs();

            // for(AccessPoint i : nets){
            //     Serial.print("SSID: ");
            //     Serial.println(i.ssid);
            //     Serial.print("RSSI: ");
            //     Serial.println(i.rssi);
            //     Serial.print("BSSID: ");
            //     Serial.println(i.bssid);
            //     Serial.println();
            // }
        }
        lastButtonPress = now;
    }

    
    delay(100);
}