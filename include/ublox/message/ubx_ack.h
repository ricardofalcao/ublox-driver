//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBX_ACK_H
#define UBLOX_UBX_ACK_H

#include "ublox/message/ubx_message.h"

#ifdef DECODE_UBX

#include <stdint.h>
#include <stddef.h>

void ubx_process_ubx_ack(uint8_t packet_id, uint8_t * payload, size_t payload_length);

#endif

#endif //UBLOX_UBX_ACK_H
