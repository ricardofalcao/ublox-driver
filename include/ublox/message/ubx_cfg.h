//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBX_CFG_H
#define UBLOX_UBX_CFG_H

#include "ublox/message/ubx_message.h"

#include <stdint.h>
#include <stddef.h>

void ubx_config_setup_port(uint16_t baud);

void ubx_config_msg_rate(uint8_t message_class, uint8_t message_id, uint8_t rate);

void ubx_config_nav_rate(uint16_t rate_ms, uint16_t cycles);

void ubx_config_psm(uint8_t power_mode);

void ubx_config_sbas(uint8_t enabled, uint8_t usage, uint8_t max, uint32_t scanmode, uint8_t scanmode2);

#endif //UBLOX_UBX_CFG_H
