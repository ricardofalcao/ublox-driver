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

/*
 * Holds the current epoch fix data
 */
extern GpsFix_t ubx_fix;

/*
 * Holds the current epoch velocity data
 */
extern GpsVelocity_t ubx_velocity;

/*
 * Initializes the driver. This opens the connection to the configured serial port, and exchanges configuration messages with the receiver.
 */
void ubx_init();

/*
 * Reinitializes the driver. This reopens the connection to the configured serial port.
 */
void ubx_reinit();

#endif//UBLOX_UBLOX_H
