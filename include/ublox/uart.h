//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UART_H
#define UBLOX_UART_H

#include <stddef.h>
#include <stdint.h>

/*
 * UART data length
 */
#define UBX_UART_LEN_8               (uint32_t) 0xC0

/*
 * UART parity
 */
#define UBX_UART_PARITY_EVEN        (uint32_t) 0x000
#define UBX_UART_PARITY_ODD         (uint32_t) 0x200
#define UBX_UART_PARITY_NONE        (uint32_t) 0x800

/*
 * UART stop bits
 */
#define UBX_UART_SB_1               (uint32_t) 0x0000
#define UBX_UART_SB_1_5             (uint32_t) 0x1000
#define UBX_UART_SB_2               (uint32_t) 0x2000
#define UBX_UART_SB_0_5             (uint32_t) 0x3000

/*
 * UART messages protocols
 */
#define UBX_UART_PROTO_UBX          (uint16_t) 0x1
#define UBX_UART_PROTO_NMEA         (uint16_t) 0x2

/*
 * MUST BE IMPLEMENTED BY THE TARGET PLATFORM
 * Opens a connection to the configured serial port.
 */
uint8_t ubx_uart_create();

/*
 * MUST BE IMPLEMENTED BY THE TARGET PLATFORM
 * Closes the active serial port connection.
 */
uint8_t ubx_uart_destroy();

/*
 * MUST BE IMPLEMENTED BY THE TARGET PLATFORM
 * Writes to the active serial port connection.
 */
void ubx_uart_write(char * data, size_t data_length);

#endif//UBLOX_UART_H
