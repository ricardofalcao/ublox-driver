//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBX_CFG_H
#define UBLOX_UBX_CFG_H

#include "ublox/message/ubx_message.h"

#include <stdint.h>
#include <stddef.h>

void config_setup_port(uint16_t baud);

void config_msg_rate(uint8_t message_class, uint8_t message_id, uint8_t rate);

void config_nav_rate(uint16_t rate_ms, uint16_t cycles);

void config_psm(uint8_t power_mode);

#endif //UBLOX_UBX_CFG_H
