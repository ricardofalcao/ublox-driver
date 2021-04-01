//
// Created by ricardo on 31/03/21.
//

#ifndef UBLOX_CONSTANTS_H
#define UBLOX_CONSTANTS_H

/*
 *
 */

#define NMEA_SYNC_CHAR '$'
#define NMEA_TERM_CHAR '\n'

#define UBX_SYNC_CHAR_1             0xB5
#define UBX_SYNC_CHAR_2             0x62

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

#define UBX_CLASS_UPD               0x09
#define UBX_CLASS_MON               0x0A
#define UBX_CLASS_AID               0x0B
#define UBX_CLASS_TIM               0x0D
#define UBX_CLASS_ESF               0x10
#define UBX_CLASS_MGA               0x13
#define UBX_CLASS_LOG               0x21
#define UBX_CLASS_SEC               0x27
#define UBX_CLASS_HNR               0x28

#define UBX_PSM_NONE                0x00
#define UBX_PSM_BALANCED            0x01
#define UBX_PSM_AGGRESSIVE_1        0x03
#define UBX_PSM_AGGRESSIVE_2        0x04
#define UBX_PSM_AGGRESSIVE_4        0x05

/*
 *
 */

#define UBX_PORT_I2C_ID             0x00
#define UBX_PORT_UART_ID            0x01
#define UBX_PORT_USB_ID             0x03
#define UBX_PORT_SPI_ID             0x04

/*
 *
 */

#define UBX_TIME_FLAG_VALID_DATE        0x01
#define UBX_TIME_FLAG_VALID_TIME        0x02
#define UBX_TIME_FLAG_FULLY_RESOLVED    0x04
#define UBX_TIME_FLAG_VALID_MAG         0x08

#define UBX_FIX_NONE                    0x00
#define UBX_FIX_DEAD_RECKONING          0x01
#define UBX_FIX_2D                      0x02
#define UBX_FIX_3D                      0x03
#define UBX_FIX_GNSS_DEAD_RECKONING     0x04
#define UBX_FIX_TIME_ONLY               0x05

#define UBX_FIX_FLAG_OK                 (uint16_t) 0x01
#define UBX_FIX_FLAG_DIFF               (uint16_t) 0x02
#define UBX_FIX_FLAG_HEAD_VALID         (uint16_t) 0x20
#define UBX_FIX_FLAG_CONFIRM_AVAILABLE  (uint16_t) 0x2000
#define UBX_FIX_FLAG_CONFIRMED_DATE     (uint16_t) 0x4000
#define UBX_FIX_FLAG_CONFIRMED_TIME     (uint16_t) 0x8000

#define UBX_FIX_INVALID_POSITION        0x01

#endif //UBLOX_CONSTANTS_H
