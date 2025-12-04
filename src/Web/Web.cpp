#include "Web/Web.h"
#include "Networks/Services/AttackService.h"
#include "Networks/Services/Wifi/WifiScanService.h"


extern AttackService attackService;
// extern WifiScanService scanner;

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

    // Start scanning
    // server.on("/scan", [this]() {
        
    //     // String html = R"(
    //     //     <html>
    //     //     <head>
    //     //         <meta charset='UTF-8'>
    //     //         <title>Scanning...</title>
    //     //         <script>
    //     //             let attempts = 0;
    //     //             function checkStatus() {
    //     //                 fetch('/scan-status')
    //     //                     .then(r => r.json())
    //     //                     .then(data => {
    //     //                         if (data.status === 'completed') {
    //     //                             window.location.href = '/results';
    //     //                         } else if (data.status === 'failed') {
    //     //                             document.body.innerHTML = '<h1>Scan Failed</h1><a href="/scan">Try Again</a>';
    //     //                         } else {
    //     //                             attempts++;
    //     //                             if (attempts < 30) {
    //     //                                 setTimeout(checkStatus, 1000);
    //     //                             } else {
    //     //                                 document.body.innerHTML = '<h1>Scan Timeout</h1><a href="/scan">Try Again</a>';
    //     //                             }
    //     //                         }
    //     //                     })
    //     //                     .catch(err => {
    //     //                         console.error('Error:', err);
    //     //                         setTimeout(checkStatus, 1000);
    //     //                     });
    //     //             }
    //     //             setTimeout(checkStatus, 1000);
    //     //         </script>
    //     //     </head>
    //     //     <body>
    //     //         <h1>Scanning WiFi Networks...</h1>
    //     //         <p>Please wait, this may take a few seconds...</p>
    //     //     </body>
    //     //     </html>
    //     // )";
        
    //     scanner.startScan();
    // });

    // // Check scan status (AJAX endpoint)
    // server.on("/scan-status", [this]() {
    //     String status;
        
    //     if (scanner.isCompleted()) {
    //         status = "completed";
    //     } else if (scanner.isScanning()) {
    //         status = "running";
    //     } else if (scanner.getStatus() == status_t::Failed) {
    //         status = "failed";
    //     } else {
    //         status = "idle";
    //     }
        
    //     String json = "{\"status\":\"" + status + "\"}";
    //     server.send(200, "application/json", json);
    // });

    // // Show results
    // server.on("/results", [this]() {
    //     auto nets = scanner.getScannedAPs();
        
    //     String html = "<html><head><meta charset='UTF-8'></head><body>";
    //     html += "<h1>Scanned Networks (" + String(nets.size()) + ")</h1>";
        
    //     if (nets.size() == 0) {
    //         html += "<p>No networks found.</p>";
    //     } else {
    //         html += "<ul>";
    //         for (size_t i = 0; i < nets.size(); i++) {
    //             html += "<li>" + nets[i].ssid + " (RSSI: " + String(nets[i].rssi) + ", CH: " + String(nets[i].channel) + ")";
    //             html += " <a href='/start/" + String(i) + "'>Start Attack</a></li>";
    //         }
    //         html += "</ul>";
    //     }
        
    //     html += "<br><a href='/scan'>Scan Again</a>";
    //     html += "</body></html>";
        
    //     server.send(200, "text/html", html);
    // });

    // Handle /start/{id}
    // server.onNotFound([this]() {
    //     String uri = server.uri();
    //     if (uri.startsWith("/start/")) {
    //         int id = uri.substring(7).toInt();
    //         auto nets = scanner.getScannedAPs();

    //         if (id >= 0 && id < (int)nets.size()) {
    //             AccessPoint ap = nets[id];

    //             MacAddress apMac = MacAddress::fromString(ap.bssid);
    //             MacAddress staMac = MacAddress::broadcast(); // Broadcast to all stations

    //             attackService.startDeauthAttack(apMac, staMac, DEFAULT_SECONDS_DEAUTH);

    //             String msg = "<html><body>";
    //             msg += "<h1>Attack Started!</h1>";
    //             msg += "<p>Target: " + ap.ssid + "</p>";
    //             msg += "<p>BSSID: " + ap.bssid + "</p>";
    //             msg += "<p>Duration: " + String(DEFAULT_SECONDS_DEAUTH) + " seconds</p>";
    //             msg += "<br><a href='/results'>Back to Results</a>";
    //             msg += "</body></html>";
                
    //             server.send(200, "text/html", msg);
    //         } else {
    //             server.send(404, "text/plain", "Invalid network ID");
    //         }
    //     } else {
    //         server.send(404, "text/plain", "Not found");
    //     }
    // });
}