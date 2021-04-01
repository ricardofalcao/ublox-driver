//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>

#include "ublox/internal/ublox_write.h"
#include "ublox/ublox.h"
#include "ublox/uart.h"

void ubx_write_ubx_packet(uint8_t packet_class, uint8_t packet_id, uint8_t *payload, size_t payload_length) {
    // Validate packet checksum
    uint16_t payload_length16 = (uint16_t) payload_length;
    uint8_t payload_length_msb = (payload_length16 >> 8) & 0xFF;
    uint8_t payload_length_lsb = payload_length16 & 0xFF;

    uint8_t ck_a = 0, ck_b = 0;

    ck_a += packet_class; ck_b += ck_a;
    ck_a += packet_id; ck_b += ck_a;
    ck_a += payload_length_lsb; ck_b += ck_a;
    ck_a += payload_length_msb; ck_b += ck_a;

    for(uint16_t i = 0; i < payload_length; i++) {
        ck_a += payload[i];
        ck_b += ck_a;
    }

    static uint8_t sync_1 = UBX_SYNC_CHAR_1;
    static uint8_t sync_2 = UBX_SYNC_CHAR_2;
    ubx_uart_write(&sync_1, sizeof(sync_1));
    ubx_uart_write(&sync_2, sizeof(sync_2));

    ubx_uart_write(&packet_class, sizeof(packet_class));
    ubx_uart_write(&packet_id, sizeof(packet_id));
    ubx_uart_write(&payload_length_lsb, sizeof(payload_length_lsb));
    ubx_uart_write(&payload_length_msb, sizeof(payload_length_msb));
    ubx_uart_write(payload, payload_length);
    ubx_uart_write(&ck_a, sizeof(ck_a));
    ubx_uart_write(&ck_b, sizeof(ck_b));

#ifdef DEBUG
    LOG("%x %x\n", ck_a, ck_b);
#endif
}