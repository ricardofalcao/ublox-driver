#include "ublox/ublox.h"
#include "ublox/internal/ublox_read.h"
#include "ublox/internal/ublox_write.h"

#include "ublox/message/ubx_cfg.h"

#include "ublox/uart.h"

#include <stdio.h>

/*
 *
 */

GpsFix_t ubx_fix;
GpsVelocity_t ubx_velocity;

void ubx_init() {
    if (!ubx_uart_create()) {
        return;
    }

    ubx_config_setup_port(UBX_PORT_UART_BAUD);
    ubx_config_nav_rate(UBX_NAV_MEAS_RATE_MS, UBX_NAV_MEAS_CYCLES);

#ifdef UBX_SBAS_ENABLE
    ubx_config_sbas(0x01, UBX_SBAS_USAGE, UBX_SBAS_MAX, UBX_SBAS_SCANMODE, UBX_SBAS_SCANMODE2);
#else
    ubx_config_sbas(0, 0, 0, 0, 0);
#endif

#ifdef UBX_SUBSCRIBE_PVT
    ubx_config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_PVT, 1);
#endif

#ifdef UBX_SUBSCRIBE_HPVT
    ubx_config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_HPPOSLLH, 1);
#endif

#ifdef UBX_SUBSCRIBE_DOP
    ubx_config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_DOP, 1);
#endif

    ubx_config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_EOE, 1);

    ubx_config_psm(UBX_POWERSAVE_MODE);
}