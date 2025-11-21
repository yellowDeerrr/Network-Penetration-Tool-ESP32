#pragma once

#include <Arduino.h>
#include <Networks/Types/WifiTypes.h>

enum class attack_t {
    None,
    Deauth,
    Handshake,
    PMKID
};

enum class attack_status_t {
    Idle,
    Running,
    Completed,
    Failed
};

struct DeauthAttackState {
    attack_status_t status = attack_status_t::Idle;
    MacAddress targetSTA;
    MacAddress sourceAP;
};

struct deauth_frame_t{
  uint8_t frame_control[2] = { 0xC0, 0x00 };
  uint8_t duration[2];
  uint8_t station[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t sender[6];
  uint8_t access_point[6];
  uint8_t fragment_sequence[2] = { 0xF0, 0xFF };
  uint16_t reason = {0x0002};
};