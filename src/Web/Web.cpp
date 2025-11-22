#include "Web/Web.h"

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
}
