//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>
#include <ublox/bits.h>
#include <ublox/uart.h>
#include "ublox/message/ubx_ack.h"
#include "ublox/message/ubx_cfg.h"

#ifdef DECODE_UBX

#define ACK_PAYLOAD_LENGTH 2
#define NAK_PAYLOAD_LENGTH 2

void _process_ack_cfg_gnss() {
    LOG("[UBX] Saving receiver configuration\n");
    ubx_config_cfg(0x0000, 0xFFFF, 0x0000);

    LOG("[UBX] Hard resetting\n");
    ubx_config_rst(0xFFFF, UBX_RST_HW_RESET);

    ubx_reinit();
}

void _process_ack_cfg(uint8_t message_id) {
    switch (message_id) {
        case UBX_MESSAGE_CFG_GNSS: {
            _process_ack_cfg_gnss();
            break;
        }
    }
}

void ubx_process_ubx_ack(uint8_t packet_id, uint8_t *payload, size_t payload_length) {
    switch (packet_id) {
        case UBX_MESSAGE_ACK_ACK: {
            if (payload_length != ACK_PAYLOAD_LENGTH) {
                LOGF("Error decoding ACK-ACK packet: Payload length did not match (%d != %d)", payload_length,
                     ACK_PAYLOAD_LENGTH);
                return;
            }

            uint8_t class_id = bits_read_uint8(payload);
            uint8_t message_id = bits_read_uint8(payload + 1);

#ifdef DEBUG_ACK
            LOGF("[ack] (%x %x)\n", class_id, message_id);
#endif

            switch (class_id) {
                case UBX_CLASS_CFG: {
                    _process_ack_cfg(message_id);
                    break;
                }
            }

            break;
        }
        case UBX_MESSAGE_ACK_NAK: {
            if (payload_length != NAK_PAYLOAD_LENGTH) {
                LOGF("Error decoding ACK-NAK packet: Payload length did not match (%d != %d)", payload_length,
                     NAK_PAYLOAD_LENGTH);
                return;
            }

            uint8_t class_id = bits_read_uint8(payload);
            uint8_t message_id = bits_read_uint8(payload + 1);
            LOGF("[NAK] (%x %x)\n", class_id, message_id);

            break;
        }
    }
}

#endif