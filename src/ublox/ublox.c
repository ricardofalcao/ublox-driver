#include "ublox/ublox.h"
#include "ublox/internal/ublox_read.h"
#include "ublox/internal/ublox_write.h"

#include "ublox/message/ubx_cfg.h"

#include "ublox/uart.h"

#include <stdio.h>
#include <time.h>

/*
 *
 */

#define UNSUBSCRIBE_NAV_LENGTH 25
static int unsubscribe_nav[UNSUBSCRIBE_NAV_LENGTH] = {
        0x60, 0x22, 0x36, 0x31, 0x04, 0x61, 0x39, 0x09, 0x34,
        0x01, 0x02, 0x07, 0x35, 0x32, 0x06, 0x03, 0x30, 0x24,
        0x25,0x23, 0x20, 0x26, 0x21, 0x11, 0x12
};

#define UNSUBSCRIBE_MON_LENGTH 6
static int unsubscribe_mon[UNSUBSCRIBE_MON_LENGTH] = {
        0x0b, 0x09, 0x02, 0x06, 0x07, 0x08
};

#define UNSUBSCRIBE_RXM_LENGTH 4
static int unsubscribe_rxm[UNSUBSCRIBE_RXM_LENGTH] = {
        0x61, 0x14, 0x15, 0x20
};

#define UNSUBSCRIBE_TIM_LENGTH 4
static int unsubscribe_tim[UNSUBSCRIBE_TIM_LENGTH] = {
        0x04, 0x03, 0x01, 0x06
};

/*
 *
 */

GpsFix_t ubx_fix;
GpsVelocity_t ubx_velocity;

void ubx_init() {
    LOG("[UBX] Initializing driver\n");

    if (!ubx_uart_create()) {
        LOG("[ERROR] Could not connect to the serial port.");
        return;
    }

    LOG("[UBX] Setting up UART ports\n");
    ubx_config_setup_port(UBX_PORT_UART_BAUD);
    ubx_config_ant(UBX_ANT_FLAGS, UBX_ANT_PINS);

    ubx_config_inf(0, UBX_INF_MASK_UBX);
    ubx_config_inf(1, UBX_INF_MASK_NMEA);

    ubx_config_nav_rate(UBX_NAV_MEAS_RATE_MS, UBX_NAV_MEAS_CYCLES);

    LOG("[UBX] Clearing message rates\n");
    for(uint8_t i = 0; i < UNSUBSCRIBE_NAV_LENGTH; i++) {
        ubx_config_msg_rate(UBX_CLASS_NAV, unsubscribe_nav[i], 0);
    }

    for(uint8_t i = 0; i < UNSUBSCRIBE_MON_LENGTH; i++) {
        ubx_config_msg_rate(UBX_CLASS_MON, unsubscribe_mon[i], 0);
    }

    for(uint8_t i = 0; i < UNSUBSCRIBE_RXM_LENGTH; i++) {
        ubx_config_msg_rate(UBX_CLASS_RXM, unsubscribe_rxm[i], 0);
    }

    for(uint8_t i = 0; i < UNSUBSCRIBE_TIM_LENGTH; i++) {
        ubx_config_msg_rate(UBX_CLASS_TIM, unsubscribe_tim[i], 0);
    }

    LOG("[UBX] Setting message rates\n");
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
    ubx_config_dynmodel(UBX_NAV_DYNMODEL);

    GNSSConfig_t configs[7];
    configs[0].id = 0; // GPS
    configs[0].minimumChannels = UBX_GNSS_GPS_MINIMUM_CHANNELS;
    configs[0].maximumChannels = UBX_GNSS_GPS_MAXIMUM_CHANNELS;
    configs[0].flags = UBX_GNSS_GPS_FLAGS;

    configs[1].id = 1; // SBAS
    configs[1].minimumChannels = UBX_GNSS_SBAS_MINIMUM_CHANNELS;
    configs[1].maximumChannels = UBX_GNSS_SBAS_MAXIMUM_CHANNELS;
    configs[1].flags = UBX_GNSS_SBAS_FLAGS;

    configs[2].id = 2; // GALILEO
    configs[2].minimumChannels = UBX_GNSS_GALILEO_MINIMUM_CHANNELS;
    configs[2].maximumChannels = UBX_GNSS_GALILEO_MAXIMUM_CHANNELS;
    configs[2].flags = UBX_GNSS_GALILEO_FLAGS;

    configs[3].id = 3; // BEIDOU
    configs[3].minimumChannels = UBX_GNSS_BEIDOU_MINIMUM_CHANNELS;
    configs[3].maximumChannels = UBX_GNSS_BEIDOU_MAXIMUM_CHANNELS;
    configs[3].flags = UBX_GNSS_BEIDOU_FLAGS;

    configs[4].id = 4; // IMES
    configs[4].minimumChannels = UBX_GNSS_IMES_MINIMUM_CHANNELS;
    configs[4].maximumChannels = UBX_GNSS_IMES_MAXIMUM_CHANNELS;
    configs[4].flags = UBX_GNSS_IMES_FLAGS;

    configs[5].id = 5; // QZSS
    configs[5].minimumChannels = UBX_GNSS_QZSS_MINIMUM_CHANNELS;
    configs[5].maximumChannels = UBX_GNSS_QZSS_MAXIMUM_CHANNELS;
    configs[5].flags = UBX_GNSS_QZSS_FLAGS;

    configs[6].id = 6; // GLONASS
    configs[6].minimumChannels = UBX_GNSS_GLONASS_MINIMUM_CHANNELS;
    configs[6].maximumChannels = UBX_GNSS_GLONASS_MAXIMUM_CHANNELS;
    configs[6].flags = UBX_GNSS_GLONASS_FLAGS;

    LOG("[UBX] Configuring constellations\n");

    ubx_config_gnss(UBX_GNSS_TRACKING_CHANNELS, UBX_GNSS_USED_CHANNELS, configs, 7);
}

void ubx_reinit() {
    time_t start = time(NULL);
    while (difftime(time(NULL), start) < 1);

    if (!ubx_uart_create()) {
        LOG("[ERROR] Could not connect to the serial port.");
        return;
    }

}