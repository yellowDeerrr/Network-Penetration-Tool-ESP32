#include "Networks/Services/Wifi/WifiService.h"

#include <WiFi.h>

void WifiService::softAP(){
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(
        apConfig.ssid.c_str(),
        apConfig.password.c_str(),
        apConfig.channel,
        apConfig.hidden,
        apConfig.maxConnections
    );
}

void WifiService::stopSoftAP(){
    WiFi.softAPdisconnect(true);
}

void WifiService::setSoftAPConfig(SoftAPConfig newConfig){
    apConfig = newConfig;
}

void scan(){
    // stop scan
    
}

// SoftAPConfig WifiService::getSoftAPConfig(){
//     return apConfig;
// }

// void WifiService::scanAPs(){
//     scannedNetworks.clear();

//     led.handleStatus(SCAN);

//     int n = WiFi.scanNetworks();
//     for(int i = 0; i < n; i++){
//         AccessPoint ap;

//         ap.ssid = WiFi.SSID(i);
//         ap.bssid = WiFi.BSSIDstr(i);
//         ap.rssi = WiFi.RSSI(i);
//         ap.channel = WiFi.channel(i);
//         ap.authMode = WiFi.encryptionType(i);
//         ap.hidden = false;
//         scannedNetworks.push_back(ap);
//     }

//     led.handleStatus(COMPLETED);
// }

// AccessPoint WifiService::getAPbySSID(String ssid){
//     for(AccessPoint i : scannedNetworks){
//         if(i.ssid == ssid) return i;
//     }

//     return AccessPoint{};
// }

// AccessPoint WifiService::getAPbyID(int i){
//     return scannedNetworks[i];
// }

// std::vector<AccessPoint> WifiService::getScannedAPs(){
//     return scannedNetworks;
// }