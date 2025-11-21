#include <Arduino.h>

#include "Networks/Services/WifiService.h"
#include <WiFi.h>

WifiService wifi;

void setup(){
    Serial.begin(115200);
    Serial.println("Started");
    delay(500);

    wifi.setSoftAPConfig(DEFAULT_AP_CONFIG);

    wifi.softAP();

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    wifi.scanAPs();

    std::vector<AccessPoint> scan = wifi.getScannedAPs();
    for(AccessPoint i : scan){
        Serial.println(i.toString());
    }
}

void loop(){
    Serial.println("Started");
    delay(2000);
}