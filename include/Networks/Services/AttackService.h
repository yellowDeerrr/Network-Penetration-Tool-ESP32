#include "Networks/Types/AttackTypes.h"

#include "Networks/Attacks/AttackDeauth.h"
#include "RGB/LedRGB.h"

class AttackService {
private:
    attack_t currentType = attack_t::None;
    attack_status_t currentStatus = attack_status_t::Idle;
    unsigned long startMillis = 0;
    unsigned long elapsedMillis = 0;

    LedRGB& led;

    AttackDeauth* deauthAttack = nullptr;
    TaskHandle_t attackTaskHandle = nullptr;
    volatile bool stopRequested = false;

    unsigned int attackDuration = DEFAULT_SECONDS_DEAUTH;

    static void attackTask(void *param);

public:
    AttackService(LedRGB& refLed) : led(refLed) {}
    ~AttackService();

    void startDeauthAttack(const MacAddress& sourceAP, const MacAddress& targetSTA, unsigned int seconds = DEFAULT_SECONDS_DEAUTH);
    // void startHandshakeAttack(const MacAddress& sourceAP, const MacAddress& targetSTA);
    // void startPMKIDAttack(const MacAddress& sourceAP, const MacAddress& targetSTA);

    void stopAttack();
    void cancelAttack();

    attack_t getCurrentType() const;
    attack_status_t getCurrentStatus() const;
    unsigned long getExecutionTime();
};