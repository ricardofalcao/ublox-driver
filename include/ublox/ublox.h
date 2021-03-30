#ifndef UBLOX_UBLOX_H
#define UBLOX_UBLOX_H

#include <stdint.h>

#include <stddef.h>

void ubx_init(unsigned int baud);

size_t ubx_uart_receive(char * buffer, size_t buffer_size);

#endif//UBLOX_UBLOX_H
