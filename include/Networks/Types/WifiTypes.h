#pragma once

#include <Arduino.h>

struct SoftAPConfig {
    String ssid;
    String password;
    int channel;
    int maxConnections;
    bool hidden;
    wifi_auth_mode_t authMode;
};

struct AccessPoint {
    String ssid;
    String bssid;
    int channel;
    int rssi;
    wifi_auth_mode_t authMode;
    bool hidden;

    String toString() const {
        return ssid + " (" + bssid + ") ch:" + String(channel) +
               " rssi:" + String(rssi) + " enc:" + String(authMode);
    }
};

const SoftAPConfig DEFAULT_AP_CONFIG = {
    "TL_LINK-5437",     // ssid
    "esp32wroo32",      // password
    6,                  // channel
    2,                  // max connections
    false,              // hidden
    WIFI_AUTH_WPA2_PSK, // auth mode
};