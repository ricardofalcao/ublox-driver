//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBX_CFG_H
#define UBLOX_UBX_CFG_H

#include "ublox/message/ubx_message.h"

#include <stdint.h>
#include <stddef.h>

typedef struct {

    uint8_t id;
    uint8_t minimumChannels;
    uint8_t maximumChannels;
    uint32_t flags;

} GNSSConfig_t;

void ubx_config_setup_port(uint16_t baud);

void ubx_config_ant(uint16_t flags, uint16_t pins);

void ubx_config_cfg(uint32_t clear_mask, uint32_t save_mask, uint32_t load_mask);

void ubx_config_inf(uint8_t protocol_id, uint8_t inf_mask);

void ubx_config_gnss(uint8_t tracking_channels, uint8_t used_channels, GNSSConfig_t * configs, size_t configsLen);

void ubx_config_msg_rate(uint8_t message_class, uint8_t message_id, uint8_t rate);

void ubx_config_nav_rate(uint16_t rate_ms, uint16_t cycles);

void ubx_config_psm(uint8_t power_mode);

void ubx_config_dynmodel(uint8_t model);

void ubx_config_rst(uint16_t section, uint8_t reset_mode);

/*
 *
 */

void ubx_process_ubx_cfg(uint8_t packet_id, uint8_t * payload, size_t payload_length);

#endif //UBLOX_UBX_CFG_H
