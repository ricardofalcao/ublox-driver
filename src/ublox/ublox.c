#include "ublox/ublox.h"
#include "ublox/ublox_read.h"

#include "ublox/uart.h"

#include <stdio.h>

/*
 *
 */

void ubx_init(unsigned int baud) { ubx_uart_create(baud); }

size_t ubx_uart_receive(char *buffer, size_t buffer_size) {
  ubx_read_inbound(buffer, buffer_size);
}