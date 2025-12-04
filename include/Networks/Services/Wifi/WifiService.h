#pragma once

#include <Arduino.h>
#include <vector>
#include <esp_wifi.h>

#include "Networks/Types/WifiTypes.h"

#include "RGB/LedRGB.h"
#include "Networks/Services/Wifi/WifiService.h"


class WifiService {
private:
    SoftAPConfig apConfig;
    LedRGB& led;

public:
    WifiService(LedRGB& refLed) : led(refLed) {}
    // WifiService(SoftAPConfig initConfig);

    // SoftAP
    void softAP();
    void stopSoftAP();

    void setSoftAPConfig(SoftAPConfig newConfig);
    SoftAPConfig getSoftAPConfig();


    // Scanning
    void scanAPs();
    AccessPoint getAPbySSID(String ssid);
    AccessPoint getAPbyID(int i);
    std::vector<AccessPoint> getScannedAPs();
};