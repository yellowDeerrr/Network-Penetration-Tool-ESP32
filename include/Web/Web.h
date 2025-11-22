#pragma once

#include "RGB/LedRGB.h"

#include <WebServer.h>

class Web {
private:
    WebServer server;
    LedRGB& led;

public:
    Web(LedRGB& ledRef) : server(80), led(ledRef) {}
    void init();
    void handle();

private:
    void setUpEndpoints();
};