//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>
#include <ublox/bits.h>
#include "ublox/message/ubx_ack.h"

#ifdef DECODE_UBX

#define ACK_PAYLOAD_LENGTH 2
#define NAK_PAYLOAD_LENGTH 2

void message_process_ubx_ack(uint8_t packet_id, uint8_t *payload, size_t payload_length) {
    switch (packet_id) {
        case UBX_MESSAGE_ACK_ACK: {
            if (payload_length != ACK_PAYLOAD_LENGTH) {
                LOG("Error decoding ACK-ACK packet: Payload length did not match (%d != %d)", payload_length,
                       ACK_PAYLOAD_LENGTH);
                return;
            }

            uint8_t class_id = bits_read_uint8(payload);
            uint8_t message_id = bits_read_uint8(payload + 1);

#ifdef DEBUG
            LOG("ack (%x %x)\n", class_id, message_id);
#endif

            break;
        }
        case UBX_MESSAGE_ACK_NAK: {
            if (payload_length != NAK_PAYLOAD_LENGTH) {
                LOG("Error decoding ACK-NAK packet: Payload length did not match (%d != %d)", payload_length,
                       NAK_PAYLOAD_LENGTH);
                return;
            }

            uint8_t class_id = bits_read_uint8(payload);
            uint8_t message_id = bits_read_uint8(payload + 1);
            LOG("NAK (%x %x)\n", class_id, message_id);

            break;
        }
    }
}

#endif