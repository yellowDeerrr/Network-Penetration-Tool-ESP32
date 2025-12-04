#pragma once

#include "RGB/LedRGB.h"
#include "Networks/Services/Wifi/WifiService.h"
// #include "Networks/Services/Wifi/WifiScanService.h"

#include <WebServer.h>

class Web {
private:
    WebServer server;
    LedRGB& led;
    WifiService& wifi;
    // WifiScanService& scanner;

public:
    Web(LedRGB& ledRef, WifiService& wifiService)  : server(80), led(ledRef), wifi(wifiService) {} //scanner(wifiScanService) {}
    void init();
    void handle();

private:
    void setUpEndpoints();
};