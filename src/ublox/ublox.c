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
    ubx_uart_create();

    config_setup_port(UBX_PORT_UART_BAUD);
    config_nav_rate(UBX_NAV_MEAS_RATE_MS, UBX_NAV_CYCLES);

#ifdef UBX_SUBSCRIBE_PVT
    config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_PVT, 1);
#endif

#ifdef UBX_SUBSCRIBE_HPVT
    config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_HPPOSLLH, 1);
#endif

#ifdef UBX_SUBSCRIBE_DOP
    config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_DOP, 1);
#endif

    config_msg_rate(UBX_CLASS_NAV, UBX_MESSAGE_NAV_EOE, 1);

    config_psm(UBX_POWERSAVE_MODE);
}

size_t ubx_uart_receive(char *buffer, size_t buffer_size) {
  ubx_read_inbound((uint8_t *) buffer, buffer_size);
}