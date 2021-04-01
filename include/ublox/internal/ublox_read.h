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

/*
 *
 */

#ifdef DECODE_UBX
#define UBX_BUFFER_SIZE 4096
#endif

/*
 *
 */

/*
 * MUST BE CALLED BY THE TARGET PLATFORM
 * Should be called whenever data is received.
 */
void ubx_uart_receive(char * buffer, size_t buffer_size);

#endif //UBLOX_UBLOX_READ_H
