//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>
#include "ublox/uart.h"
#include "ublox/ublox.h"

#define READ_BUFFER_LENGTH 1024

int main() {
    ubx_init(460800);

    char buffer[READ_BUFFER_LENGTH];

    while (1) {
        size_t bytes_read = ubx_uart_read(buffer, sizeof(buffer));

        if (bytes_read > 0) {
            ubx_uart_receive(buffer, bytes_read);
        }
    }

    return 0;
}