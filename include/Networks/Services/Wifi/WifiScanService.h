#pragma once

#include "Networks/Types/GeneralTypes.h"
#include "Networks/Types/WifiTypes.h"
#include "RGB/LedRGB.h"
#include <WiFi.h>

#include <vector>

class WifiScanService {
private:
    std::vector<AccessPoint> lastScannedNetworks; 
    status_t currentStatus = status_t::Idle;
    LedRGB& led;

    unsigned long startMillis = 0;
    unsigned long elapsedMillis = 0;

    TaskHandle_t scanTaskHandle = nullptr;
    volatile bool stopRequested = false;

    static void scanTask(void *param);

    void addScannedNetworksToVector(int n);

public:
    WifiScanService(LedRGB& refLed) : led(refLed) {};
    ~WifiScanService();

    void startScan();
    void stopScan();
    void cancelScan();

    status_t getStatus() const;
    bool isScanning() const;
    bool isCompleted() const;

    std::vector<AccessPoint> getScannedAPs() const;
    AccessPoint getAPbySSID(String ssid) const;
    AccessPoint getAPbyID(int i) const;
    int getNetworkCount() const;
};