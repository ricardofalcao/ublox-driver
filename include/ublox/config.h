//
// Created by ricardo on 31/03/21.
//

#ifndef UBLOX_CONFIG_H
#define UBLOX_CONFIG_H

#include "ublox/constants.h"

#define LOG(f_, ...) printf((f_), __VA_ARGS__)

#define DEBUG

// #define DECODE_NMEA
#define DECODE_UBX

#define UBX_PORT_UART_TX_READY      (int16_t) 0x00

#define UBX_PORT_UART_DATA_LEN      UBX_UART_LEN_8
#define UBX_PORT_UART_PARITY        UBX_UART_PARITY_NONE
#define UBX_PORT_UART_STOPBITS      UBX_UART_SB_1
#define UBX_PORT_UART_BAUD          9600

#define UBX_NAV_MEAS_RATE_MS        (uint16_t) 2000
#define UBX_NAV_CYCLES              (uint16_t) 1

#define UBX_POWERSAVE_MODE          UBX_PSM_BALANCED

// Position/Velocity/Time
#define UBX_SUBSCRIBE_PVT

#ifdef UBX_SUBSCRIBE_PVT
// High precision Position/Velocity/Time
// #define UBX_SUBSCRIBE_HPVT

#endif

#define UBX_SUBSCRIBE_DOP

#endif //UBLOX_CONFIG_H
