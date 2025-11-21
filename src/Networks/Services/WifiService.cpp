#include "Networks/Services/WifiService.h"
#include <WiFi.h>

// WifiService::WifiService(){
//     setSoftAPConfig(DEFAULT_AP_CONFIG);
// }

// WifiService::WifiService(SoftAPConfig initConfig){
//     setSoftAPConfig(initConfig);
//     launchSoftAP();
// }

void WifiService::softAP(){
    WiFi.mode(WIFI_AP);
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

SoftAPConfig WifiService::getSoftAPConfig(){
    return apConfig;
}

void WifiService::scanAPs(){
    scannedNetworks.clear();

    int n = WiFi.scanNetworks();
    for(int i = 0; i < n; i++){
        AccessPoint ap;

        ap.ssid = WiFi.SSID(i);
        ap.bssid = WiFi.BSSIDstr(i);
        ap.rssi = WiFi.RSSI(i);
        ap.channel = WiFi.channel(i);
        ap.authMode = WiFi.encryptionType(i);
        ap.hidden = false;
        scannedNetworks.push_back(ap);
    }
}

AccessPoint WifiService::getAPbySSID(String ssid){
    for(AccessPoint i : scannedNetworks){
        if(i.ssid == ssid) return i;
    }

    return AccessPoint{};
}

AccessPoint WifiService::getAPbyID(int i){
    return scannedNetworks[i];
}

std::vector<AccessPoint> WifiService::getScannedAPs(){
    return scannedNetworks;
}