#pragma once

#include <Networks/Types/AttackTypes.h>
#include <esp_wifi.h>

class AttackDeauth {
private:
    DeauthAttackState state;
    deauth_frame_t frame;
    
public:
    AttackDeauth(const MacAddress& sourceAP, const MacAddress& targetSTA);

    void start(int times = 1);
    // void stop();
    attack_status_t getStatus();

private:
    // void buildDeauthFrame();
    void sendDeauthFrame();
};