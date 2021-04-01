//
// Created by ricardo on 31/03/21.
//

#ifndef UBLOX_CONSTANTS_H
#define UBLOX_CONSTANTS_H

/*
 *
 */

// Character used to mark the beggining of a new NMEA message
#define NMEA_SYNC_CHAR '$'
// Character used to mark the end of a new NMEA message
#define NMEA_TERM_CHAR '\n'

// UBX packet start bytes (0xB5 0x62)
#define UBX_SYNC_CHAR_1             0xB5
#define UBX_SYNC_CHAR_2             0x62

/*
 * UBX packet classes and packet ids
 */
#define UBX_CLASS_NAV               0x01
#define UBX_MESSAGE_NAV_PVT         0x07
#define UBX_MESSAGE_NAV_HPPOSLLH    0x14
#define UBX_MESSAGE_NAV_DOP         0x04
#define UBX_MESSAGE_NAV_EOE         0x61

#define UBX_CLASS_RXM               0x02
#define UBX_CLASS_INF               0x04

#define UBX_CLASS_ACK               0x05
#define UBX_MESSAGE_ACK_ACK         0x01
#define UBX_MESSAGE_ACK_NAK         0x00

#define UBX_CLASS_CFG               0x06
#define UBX_MESSAGE_CFG_PORT        0x00
#define UBX_MESSAGE_CFG_MSG         0x01
#define UBX_MESSAGE_CFG_RATE        0x08
#define UBX_MESSAGE_CFG_PSM         0x86
#define UBX_MESSAGE_CFG_SBAS        0x16

#define UBX_CLASS_UPD               0x09
#define UBX_CLASS_MON               0x0A
#define UBX_CLASS_AID               0x0B
#define UBX_CLASS_TIM               0x0D
#define UBX_CLASS_ESF               0x10
#define UBX_CLASS_MGA               0x13
#define UBX_CLASS_LOG               0x21
#define UBX_CLASS_SEC               0x27
#define UBX_CLASS_HNR               0x28

/*
 * UBX Power saving mode
 */
#define UBX_PSM_NONE                0x00
#define UBX_PSM_BALANCED            0x01
#define UBX_PSM_AGGRESSIVE_1        0x03
#define UBX_PSM_AGGRESSIVE_2        0x04
#define UBX_PSM_AGGRESSIVE_4        0x05

/*
 *
 */

/*
 * UBX Port IDs
 */
#define UBX_PORT_I2C_ID             0x00
#define UBX_PORT_UART_ID            0x01
#define UBX_PORT_USB_ID             0x03
#define UBX_PORT_SPI_ID             0x04

/*
 *
 */

/*
 * GPS Time flags
 */
#define UBX_TIME_FLAG_VALID_DATE        0x01
#define UBX_TIME_FLAG_VALID_TIME        0x02
#define UBX_TIME_FLAG_FULLY_RESOLVED    0x04
#define UBX_TIME_FLAG_VALID_MAG         0x08

/*
 * GPS Fix type
 */
#define UBX_FIX_TYPE_NONE                    0x00
#define UBX_FIX_TYPE_DEAD_RECKONING          0x01
#define UBX_FIX_TYPE_2D                      0x02
#define UBX_FIX_TYPE_3D                      0x03
#define UBX_FIX_TYPE_GNSS_DEAD_RECKONING     0x04
#define UBX_FIX_TYPE_TIME_ONLY               0x05

/*
 * GPS Fix flags
 */
#define UBX_FIX_FLAG_OK                 (uint16_t) 0x01
#define UBX_FIX_FLAG_DIFF               (uint16_t) 0x02
#define UBX_FIX_FLAG_HEAD_VALID         (uint16_t) 0x20
#define UBX_FIX_FLAG_CONFIRM_AVAILABLE  (uint16_t) 0x2000
#define UBX_FIX_FLAG_CONFIRMED_DATE     (uint16_t) 0x4000
#define UBX_FIX_FLAG_CONFIRMED_TIME     (uint16_t) 0x8000

#define UBX_FIX_INVALID_POSITION        0x01

/*
 * SBAS Usage
 */
#define UBX_SBAS_USE_RANGE              0x01
#define UBX_SBAS_USE_CORRECTIONS        0x02
#define UBX_SBAS_USE_INTEGRITY          0x04

#endif //UBLOX_CONSTANTS_H
