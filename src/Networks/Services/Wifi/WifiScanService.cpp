#include "Networks/Services/Wifi/WifiScanService.h"
#include "esp_wifi.h"

WifiScanService::~WifiScanService(){
    stopScan();
}

void WifiScanService::addScannedNetworksToVector(int n){
    for (int i = 0; i < n; i++) {
        AccessPoint ap;
        ap.ssid = WiFi.SSID(i);
        ap.bssid = WiFi.BSSIDstr(i);
        ap.rssi = WiFi.RSSI(i);
        ap.channel = WiFi.channel(i);
        ap.authMode = WiFi.encryptionType(i);
        ap.hidden = false;
        lastScannedNetworks.push_back(ap);
        Serial.println(ap.toString());
    }
}

void WifiScanService::scanTask(void *param){
    WifiScanService* self = static_cast<WifiScanService*>(param);

    self->currentStatus = status_t::Running;
    self->led.handleStatus(SCAN);
    self->lastScannedNetworks.clear();
    
    Serial.println("Starting WiFi scan...");

    WiFi.scanNetworks(true);

    Serial.println("Scanning async");

    int n = WIFI_SCAN_RUNNING;
    while (n == WIFI_SCAN_RUNNING && !self->stopRequested) {
        Serial.println("check");
        n = WiFi.scanComplete();
        vTaskDelay(pdMS_TO_TICKS(100)); // Check every 100ms
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
    n = WiFi.scanComplete();

    if (self->stopRequested) {
        Serial.println("Scan stopped by user");
        self->currentStatus = status_t::Canceled;
        self->led.handleStatus(CANCELED);
        WiFi.scanDelete();
    } 
    else if (n == WIFI_SCAN_FAILED || n < 0) {
        int attempts = 5;

        for(int i = 0; i < attempts; i++){
            n = WiFi.scanComplete();
            if(n >= 0){
                Serial.printf("Scan completed: %d networks found, Attemp: %d\n", n, i);

                self->addScannedNetworksToVector(n);
                self->currentStatus = status_t::Completed;
                self->led.handleStatus(COMPLETED);
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        if(n < 0){
            Serial.println("Scan failed");
            self->currentStatus = status_t::Failed;
            self->led.handleStatus(FAILED);
        }
        
        WiFi.scanDelete();
    } 
    else {
        Serial.printf("Scan completed: %d networks found\n", n);
        
        self->addScannedNetworksToVector(n);
        
        self->currentStatus = status_t::Completed;
        self->led.handleStatus(COMPLETED);
        WiFi.scanDelete();
    }
    
    self->elapsedMillis = millis();
    self->scanTaskHandle = nullptr;
    vTaskDelete(NULL);
}

void WifiScanService::startScan(){
    stopScan();

    stopRequested = false;
    lastScannedNetworks.clear();
    startMillis = millis();

    Serial.print("Scans");

    xTaskCreatePinnedToCore(
        scanTask,
        "ScanTask",
        4096,
        this,
        1,
        &scanTaskHandle,
        APP_CPU_NUM
    );
}



void WifiScanService::stopScan(){
    if(scanTaskHandle != nullptr){
        stopRequested = true;

        while(scanTaskHandle != nullptr){
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    currentStatus = status_t::Idle;
}

void WifiScanService::cancelScan(){
    stopScan();
    led.handleStatus(CANCELED);
}


status_t WifiScanService::getStatus() const {
    return currentStatus;
}

bool WifiScanService::isScanning() const {
    return currentStatus == status_t::Running;
}

bool WifiScanService::isCompleted() const {
    return currentStatus == status_t::Completed;
}

std::vector<AccessPoint> WifiScanService::getScannedAPs() const {
    return lastScannedNetworks;
}

AccessPoint WifiScanService::getAPbySSID(String ssid) const {
    for (const AccessPoint& ap : lastScannedNetworks) {
        if (ap.ssid == ssid) return ap;
    }
    return AccessPoint{};
}

AccessPoint WifiScanService::getAPbyID(int i) const {
    if (i >= 0 && i < (int)lastScannedNetworks.size()) {
        return lastScannedNetworks[i];
    }
    return AccessPoint{};
}

int WifiScanService::getNetworkCount() const {
    return lastScannedNetworks.size();
}