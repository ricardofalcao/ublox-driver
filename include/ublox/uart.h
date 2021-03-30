//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_UART_H
#define UBLOX_UART_H

#include <stddef.h>

void ubx_uart_create(unsigned int baud);

void ubx_uart_destroy();

void ubx_uart_write(char data);

size_t ubx_uart_read(char * buffer, size_t buffer_size);

#endif//UBLOX_UART_H
