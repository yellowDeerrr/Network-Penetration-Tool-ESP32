#pragma once

#include "RGB/LedRGB.h"
#include "Networks/Services/WifiService.h"

#include <WebServer.h>

class Web {
private:
    WebServer server;
    LedRGB& led;
    WifiService& wifi;

public:
    Web(LedRGB& ledRef, WifiService& wifiService) : server(80), led(ledRef), wifi(wifiService) {}
    void init();
    void handle();

private:
    void setUpEndpoints();
};