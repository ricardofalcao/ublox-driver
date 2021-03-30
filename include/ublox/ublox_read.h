//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UBLOX_READ_H
#define UBLOX_UBLOX_READ_H

#include <stddef.h>

#define NMEA_SYNC_CHAR (uint8_t)'$'
#define NMEA_TERM_CHAR (uint8_t)'\n'

//#define DECODE_NMEA
#ifdef DECODE_NMEA
#define NMEA_BUFFER_SIZE 1024

#define NMEA_STATE_READY 0
#define NMEA_STATE_SYNC 1
#define NMEA_STATE_RECVDATA 2
#endif

/*
 *
 */

#define UBX_SYNC_CHAR_1 (uint8_t)0xB5
#define UBX_SYNC_CHAR_2 (uint8_t)0x62

#define DECODE_UBX
#ifdef DECODE_UBX
#define UBX_BUFFER_SIZE 4096

#define UBX_STATE_READY 0
#define UBX_STATE_SYNC 1
#define UBX_STATE_WAIT_LEN 2
#define UBX_STATE_RECVDATA 3
#endif

/*
 *
 */

void ubx_read_inbound(char * buffer, size_t buffer_size);

#endif //UBLOX_UBLOX_READ_H
