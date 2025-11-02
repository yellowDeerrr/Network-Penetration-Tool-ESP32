#include <Arduino.h>
#include <vector> 
#include "WiFiNetwork.h"
#include "LCD.h"

#define DT_PIN 37
#define CLK_PIN 38
#define SW_PIN 39

volatile int counter = 0;
int lastStateCLK;


void IRAM_ATTR rotary_encoder(){
    int currentStateCLK = digitalRead(CLK_PIN);
    if(currentStateCLK != lastStateCLK && currentStateCLK){
        if(digitalRead(DT_PIN) != currentStateCLK){
            counter++;
        }else{
            counter--;
        }
    }
    lastStateCLK = currentStateCLK;
}

void setup(){
    Serial.begin(115200);
    
    initNetwork(1);

    initDisplay();
    
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    pinMode(SW_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(CLK_PIN), rotary_encoder, CHANGE);

    
}

long unsigned now, lastPrintOut, lastDisplayPrint, lastButtonPress = 0;

void loop(){
    now = millis();
    if(now - lastPrintOut >= 100){
        Serial.printf("CLK: %d\n", digitalRead(CLK_PIN));
        Serial.printf("DT: %d\n", digitalRead(DT_PIN));
        lastPrintOut = now;
    }

    if(now - lastDisplayPrint >= 150){
        displayCounter(counter);

        Serial.printf("Count: %d\n", counter);
        lastDisplayPrint = now;
    }

    if (digitalRead(SW_PIN) == LOW && now - lastButtonPress >= 300) {
        Serial.println("Button Pressed");
        std::vector<WiFiNetwork> nets = scanNetworks();
        displayNetworks(nets);
        lastButtonPress = now;
    }
}