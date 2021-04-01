//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBLOX_WRITE_H
#define UBLOX_UBLOX_WRITE_H

#include <stddef.h>
#include <stdint.h>
/*
 *
 */

/*
 * Send a UBX protocol packet
 */
void ubx_write_ubx_packet(uint8_t packet_class, uint8_t packet_id, uint8_t *payload, size_t payload_length);

#endif //UBLOX_UBLOX_WRITE_H
