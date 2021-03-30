#ifndef UBLOX_UBLOX_H
#define UBLOX_UBLOX_H

#include <stdint.h>
#include <stddef.h>

/*
 *
 */

// #define DECODE_NMEA
#define DECODE_UBX

#define UBX_CLASS_NAV           0x01
#define UBX_MESSAGE_NAV_PVT     0x07

#define UBX_CLASS_RXM           0x02
#define UBX_CLASS_INF           0x04
#define UBX_CLASS_ACK           0x05
#define UBX_CLASS_CFG           0x06
#define UBX_CLASS_UPD           0x09
#define UBX_CLASS_MON           0x0A
#define UBX_CLASS_AID           0x0B
#define UBX_CLASS_TIM           0x0D
#define UBX_CLASS_ESF           0x10
#define UBX_CLASS_MGA           0x13
#define UBX_CLASS_LOG           0x21
#define UBX_CLASS_SEC           0x27
#define UBX_CLASS_HNR           0x28

/*
 *
 */

void ubx_init(unsigned int baud);

size_t ubx_uart_receive(char * buffer, size_t buffer_size);

#endif//UBLOX_UBLOX_H
