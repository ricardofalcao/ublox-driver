#ifndef UBLOX_UBLOX_H
#define UBLOX_UBLOX_H

#include <stdint.h>
#include <stddef.h>

#include "ublox/constants.h"
#include "ublox/structs.h"
#include "ublox/config.h"

/*
 *
 */

extern GpsFix_t ubx_fix;
extern GpsVelocity_t ubx_velocity;

/*
 *
 */

void ubx_init();

size_t ubx_uart_receive(char * buffer, size_t buffer_size);

#endif//UBLOX_UBLOX_H
