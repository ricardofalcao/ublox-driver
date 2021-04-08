//
// Created by ricardo on 31/03/21.
//

#ifndef UBLOX_CONFIG_H
#define UBLOX_CONFIG_H

#include "ublox/constants.h"

/*
 * The method used by to library for logging
 */
#define LOG(f_) printf(f_)
#define LOGF(f_, ...) printf((f_), __VA_ARGS__)

/*
 * Activate DEBUG messages
 */

// Debug sent packets infomation
// #define DEBUG_PACKETS

// Debug received ack packets
//#define DEBUG_ACK

// Debug current epoch information
#define DEBUG_INFO

/*
 * Uncomment if you want to include the protocol functionality
 */
// #define DECODE_NMEA
#define DECODE_UBX

// Antenna flags
#define UBX_ANT_FLAGS               UBX_ANT_FLAG_RECOVERY | UBX_ANT_FLAG_PD_SCD | UBX_ANT_FLAG_SCD | UBX_ANT_FLAG_SVCS
// Antenna flag pins (leave 0 if unchanged)
#define UBX_ANT_PINS                0xB9F0

#ifdef DECODE_UBX
#define UBX_INF_MASK_UBX            UBX_INF_ERROR | UBX_INF_WARNING | UBX_INF_NOTICE
#else
#define UBX_INF_MASK_UBX            0
#endif

#ifdef DECODE_NMEA
#define UBX_INF_MASK_NMEA           UBX_INF_ERROR | UBX_INF_WARNING | UBX_INF_NOTICE
#else
#define UBX_INF_MASK_NMEA           0
#endif

#define UBX_GNSS_TRACKING_CHANNELS          32
#define UBX_GNSS_USED_CHANNELS              32

#define UBX_GNSS_GPS_FLAGS                  UBX_GNSS_FLAG_ENABLE | UBX_GNSS_FLAG_GPS_L1CA
#define UBX_GNSS_GPS_MINIMUM_CHANNELS       8
#define UBX_GNSS_GPS_MAXIMUM_CHANNELS       16

#define UBX_GNSS_SBAS_FLAGS                 UBX_GNSS_FLAG_ENABLE | UBX_GNSS_FLAG_SBAS_L1CA
#define UBX_GNSS_SBAS_MINIMUM_CHANNELS      1
#define UBX_GNSS_SBAS_MAXIMUM_CHANNELS      3

#define UBX_GNSS_GALILEO_FLAGS              UBX_GNSS_FLAG_ENABLE | UBX_GNSS_FLAG_GALILEO_E1
#define UBX_GNSS_GALILEO_MINIMUM_CHANNELS   4
#define UBX_GNSS_GALILEO_MAXIMUM_CHANNELS   8

#define UBX_GNSS_BEIDOU_FLAGS               0
#define UBX_GNSS_BEIDOU_MINIMUM_CHANNELS    8
#define UBX_GNSS_BEIDOU_MAXIMUM_CHANNELS    16

#define UBX_GNSS_IMES_FLAGS                 0
#define UBX_GNSS_IMES_MINIMUM_CHANNELS      0
#define UBX_GNSS_IMES_MAXIMUM_CHANNELS      8

#define UBX_GNSS_QZSS_FLAGS                 UBX_GNSS_FLAG_ENABLE | UBX_GNSS_FLAG_QZSS_L1CA
#define UBX_GNSS_QZSS_MINIMUM_CHANNELS      0
#define UBX_GNSS_QZSS_MAXIMUM_CHANNELS      3

#define UBX_GNSS_GLONASS_FLAGS              UBX_GNSS_FLAG_ENABLE | UBX_GNSS_FLAG_GLONASS_L1
#define UBX_GNSS_GLONASS_MINIMUM_CHANNELS   8
#define UBX_GNSS_GLONASS_MAXIMUM_CHANNELS   14

// Serial port TX Ready (Don't change if unsure)
#define UBX_PORT_UART_TX_READY      (int16_t) 0x00

// Serial port data length
#define UBX_PORT_UART_DATA_LEN      UBX_UART_LEN_8
// Serial port data parity
#define UBX_PORT_UART_PARITY        UBX_UART_PARITY_NONE
// Serial port data number of stop bits
#define UBX_PORT_UART_STOPBITS      UBX_UART_SB_1
// Serial port data baud rate
#define UBX_PORT_UART_BAUD          9600

// The time between GNSS measurements (in ms)
#define UBX_NAV_MEAS_RATE_MS        (uint16_t) 2000
// The ratio between the number of measurements and the number of navigation solutions (in cycles)
#define UBX_NAV_MEAS_CYCLES         (uint16_t) 1
// The dynamic model of the receiver
#define UBX_NAV_DYNMODEL            UBX_DYNMODEL_AUTOMOTIVE

// UBX Power saving mode
#define UBX_POWERSAVE_MODE          UBX_PSM_BALANCED

// Position/Velocity/Time
#define UBX_SUBSCRIBE_PVT

#ifdef UBX_SUBSCRIBE_PVT
// High precision Position/Velocity/Time
// #define UBX_SUBSCRIBE_HPVT

#endif

// DOP
#define UBX_SUBSCRIBE_DOP

#endif //UBLOX_CONFIG_H
