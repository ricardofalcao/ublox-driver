//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBLOX_READ_H
#define UBLOX_UBLOX_READ_H

#include <stddef.h>
#include <stdint.h>

#ifdef DECODE_NMEA
#define NMEA_BUFFER_SIZE 1024
#endif

#define NMEA_SYNC_CHAR '$'
#define NMEA_TERM_CHAR '\n'

/*
 *
 */

#ifdef DECODE_UBX
#define UBX_BUFFER_SIZE 4096
#endif

#define UBX_SYNC_CHAR_1 0xB5
#define UBX_SYNC_CHAR_2 0x62

/*
 *
 */

void ubx_read_inbound(uint8_t * buffer, size_t buffer_size);

#endif //UBLOX_UBLOX_READ_H
