#include <WiFi.h>
#include "WiFiNetwork.h"
#include <vector>

void initNetwork(int n){
    if(n == 1)
        WiFi.mode(WIFI_MODE_STA);
    else if(n == 2)
        WiFi.mode(WIFI_MODE_AP);
    else if(n == 3)
        WiFi.mode(WIFI_MODE_APSTA);
    else 
        WiFi.mode(WIFI_MODE_STA);

    WiFi.disconnect();
}

std::vector<WiFiNetwork> scanNetworks(){
    std::vector<WiFiNetwork> networks;

    int n = WiFi.scanNetworks();

    if(n == 0){
        return networks;
    }else{
        // Serial.printf("%d networks found\n", n);
        
        for(int i = 0; i < n; i++){
            String ssid = WiFi.SSID(i);
            int rssi = WiFi.RSSI(i);
            int channel = WiFi.channel(i);
            String auth;

            switch (WiFi.encryptionType(i)) {
                case WIFI_AUTH_OPEN:           auth = "open"; break;
                case WIFI_AUTH_WEP:            auth = "WEP"; break;
                case WIFI_AUTH_WPA_PSK:        auth = "WPA"; break;
                case WIFI_AUTH_WPA2_PSK:       auth = "WPA2"; break;
                case WIFI_AUTH_WPA_WPA2_PSK:   auth = "WPA+WPA2"; break;
                case WIFI_AUTH_WPA2_ENTERPRISE:auth = "WPA2-EAP"; break;
                case WIFI_AUTH_WPA3_PSK:       auth = "WPA3"; break;
                case WIFI_AUTH_WPA2_WPA3_PSK:  auth = "WPA2+WPA3"; break;
                case WIFI_AUTH_WAPI_PSK:       auth = "WAPI"; break;
                default:                       auth = "unknown"; break;
            }
            networks.emplace_back(ssid, rssi, auth, channel);
            // Serial.printf("%d | SSID: %s (RSSI: %d) \t| Auth: %s \t| Channel: %d\n", i, WiFi.SSID(i).c_str(), WiFi.RSSI(i), auth, WiFi.channel(i));
        }
    }

    return networks;
}

