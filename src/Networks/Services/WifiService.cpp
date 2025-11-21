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
        _apConfig.ssid.c_str(),
        _apConfig.password.c_str(),
        _apConfig.channel,
        _apConfig.hidden,
        _apConfig.maxConnections
    );
}

void WifiService::stopSoftAP(){
    WiFi.softAPdisconnect(true);
}

void WifiService::setSoftAPConfig(SoftAPConfig newConfig){
    _apConfig = newConfig;
}

SoftAPConfig WifiService::getSoftAPConfig(){
    return _apConfig;
}

void WifiService::scanAPs(){
    _scannedNetworks.clear();

    int n = WiFi.scanNetworks();
    for(int i = 0; i < n; i++){
        AccessPoint ap;

        ap.ssid = WiFi.SSID(i);
        ap.bssid = WiFi.BSSIDstr(i);
        ap.rssi = WiFi.RSSI(i);
        ap.channel = WiFi.channel(i);
        ap.authMode = WiFi.encryptionType(i);
        ap.hidden = false;
        _scannedNetworks.push_back(ap);
    }
}

AccessPoint WifiService::getAPbySSID(String ssid){
    for(AccessPoint i : _scannedNetworks){
        if(i.ssid == ssid) return i;
    }

    return AccessPoint{};
}

AccessPoint WifiService::getAPbyID(int i){
    return _scannedNetworks[i];
}

std::vector<AccessPoint> WifiService::getScannedAPs(){
    return _scannedNetworks;
}