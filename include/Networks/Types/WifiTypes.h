#pragma once

#include <Arduino.h>

struct MacAddress {
    uint8_t bytes[6];

    MacAddress(){
        memset(bytes, 0, sizeof(bytes));
    }

    MacAddress(const uint8_t init[6]){
        memcpy(bytes, init, sizeof(bytes));
    }

    MacAddress(const String& str) {
        sscanf(str.c_str(),
               "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
               &bytes[0], &bytes[1], &bytes[2],
               &bytes[3], &bytes[4], &bytes[5]);
    }

    static MacAddress broadcast() {
        MacAddress mac;
        for (int i = 0; i < 6; i++) mac.bytes[i] = 0xFF;
        return mac;
    }
    
    static MacAddress fromString(const String& str){
        MacAddress mac;
         sscanf(str.c_str(),
               "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
               &mac.bytes[0], &mac.bytes[1], &mac.bytes[2],
               &mac.bytes[3], &mac.bytes[4], &mac.bytes[5]);
        return mac;
    }

    String toString() const {
        char buf[18];
        sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",
                bytes[0], bytes[1], bytes[2],
                bytes[3], bytes[4], bytes[5]);
        return String(buf);
    }

    bool operator==(const MacAddress& other) const {
        return memcmp(bytes, other.bytes, 6) == 0;
    }
};

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