//
// Created by ricardo on 30/03/21.
//

#include "ublox/ublox.h"
#include "ublox/internal/ublox_read.h"
#include "ublox/message/ubx_nav.h"
#include "ublox/message/ubx_ack.h"
#include "ublox/message/ubx_cfg.h"

#include <stdint.h>
#include <stdio.h>

#ifdef DECODE_NMEA
#define NMEA_STATE_READY 0
#define NMEA_STATE_SYNC 1
#define NMEA_STATE_RECVDATA 2
#endif

/*
 *
 */

#ifdef DECODE_UBX
#define UBX_STATE_READY 0
#define UBX_STATE_SYNC 1
#define UBX_STATE_WAIT_LEN 2
#define UBX_STATE_RECVDATA 3
#endif

/*
 *
 */

#ifdef DECODE_NMEA
uint8_t buffer_nmea[NMEA_BUFFER_SIZE];
uint8_t *buffer_nmea_cursor = buffer_nmea;
uint8_t nmea_read_state = NMEA_STATE_READY;

void _process_nmea() {
    LOG("Received NMEA: %s\n", buffer_nmea);
}
#endif

//

#ifdef DECODE_UBX
uint8_t buffer_ubx[UBX_BUFFER_SIZE];
uint8_t *buffer_ubx_cursor = buffer_ubx;
uint16_t ubx_payload_length = 0;
uint8_t ubx_read_state = UBX_STATE_READY;

void _process_ubx(uint8_t *buffer, size_t buffer_length, size_t payload_length) {
    // Validate packet checksum
    uint8_t *buffer_ubx_ck_data = &buffer[2];
    uint8_t ck_a = 0, ck_b = 0;
    for (uint16_t i = 0; i < 4 + payload_length; i++) {
        ck_a += buffer_ubx_ck_data[i];
        ck_b += ck_a;
    }

    if (ck_a != buffer[buffer_length - 2] || ck_b != buffer[buffer_length - 1]) {
        LOGF("Error validating UBX checksum: Expected %x %x, got %x %x.\n", ck_a, ck_b, buffer[buffer_length - 2],
             buffer[buffer_length - 1]);
        return;
    }

    uint8_t packet_class = buffer[2];
    uint8_t packet_id = buffer[3];
    uint8_t *buffer_ubx_payload = &buffer[6];

    switch (packet_class) {
        case UBX_CLASS_NAV: {
            ubx_process_ubx_nav(packet_id, buffer_ubx_payload, payload_length);
            break;
        }
        case UBX_CLASS_ACK: {
            ubx_process_ubx_ack(packet_id, buffer_ubx_payload, payload_length);
            break;
        }
        case UBX_CLASS_CFG: {
            ubx_process_ubx_cfg(packet_id, buffer_ubx_payload, payload_length);
            break;
        }
    }
}

#endif

void ubx_uart_receive(char *_buffer, size_t buffer_size) {
    uint8_t *buffer = (uint8_t *) _buffer;

    uint8_t c;
    for (size_t i = 0; i < buffer_size; i++) {
        c = (buffer[i] & 0xFF);

#ifdef DECODE_UBX
        switch (ubx_read_state) {
            case UBX_STATE_READY: {
                // We must allow NMEA to insert this character into the buffer because the
                // next char might not be the UBX sync char 2
                if (c == UBX_SYNC_CHAR_1) {
                    *buffer_ubx_cursor = c;
                    buffer_ubx_cursor++;
                    ubx_read_state = UBX_STATE_SYNC;
                }

                break;
            }

            case UBX_STATE_SYNC: {
                // Only continue ubx decode process if second sync char arrives
                if (c == UBX_SYNC_CHAR_2) {
                    *buffer_ubx_cursor = c;
                    buffer_ubx_cursor++;
                    ubx_read_state = UBX_STATE_WAIT_LEN;
                    continue;
                }

                // Reset otherwise and allow further NMEA buffer changes
                ubx_read_state = UBX_STATE_READY;
                buffer_ubx_cursor = buffer_ubx;
                break;
            }

            case UBX_STATE_WAIT_LEN: {
                // We are now decoding a UBX packet. We must wait for the arrival of the
                // next 4 bytes, to ensure we received the payload length

                *buffer_ubx_cursor = c;
                buffer_ubx_cursor++;

                // 2 sync bytes + 1 message class byte + 1 message id byte + 2 payload
                // length bytes
                if (buffer_ubx_cursor - buffer_ubx == 6) {
                    ubx_payload_length =
                            (*(buffer_ubx_cursor - 1) << 8) | (*(buffer_ubx_cursor - 2) & 0xFF);
                    ubx_read_state = UBX_STATE_RECVDATA;
                }

                continue;
            }

            case UBX_STATE_RECVDATA: {
                *buffer_ubx_cursor = c;
                buffer_ubx_cursor++;

                // We only stop the decoding process when all the bytes are received (6
                // from the header, N from the payload, 2 for the checksum)
                size_t buffer_length = buffer_ubx_cursor - buffer_ubx;
                if (buffer_length == (6 + ubx_payload_length + 2)) {
                    _process_ubx(buffer_ubx, buffer_length, ubx_payload_length);

                    ubx_read_state = UBX_STATE_READY;
                    buffer_ubx_cursor = buffer_ubx;
                }

                continue;
            }
        }
#endif

#ifdef DECODE_NMEA
        switch (nmea_read_state) {
            case NMEA_STATE_READY: {
                if (c == NMEA_SYNC_CHAR) {
                    *buffer_nmea_cursor = c;
                    buffer_nmea_cursor++;
                    nmea_read_state = NMEA_STATE_SYNC;
                    continue;
                }

                break;
            }

            case NMEA_STATE_SYNC: {
                // Only continue NMEA decode process if second sync char is not UBX
                if (c != UBX_SYNC_CHAR_2) {
                    *buffer_nmea_cursor = c;
                    buffer_nmea_cursor++;
                    nmea_read_state = NMEA_STATE_RECVDATA;
                    continue;
                }

                // Reset otherwise
                nmea_read_state = NMEA_STATE_READY;
                buffer_nmea_cursor = buffer_nmea;
                break;
            }

            case NMEA_STATE_RECVDATA: {
                if (c == NMEA_TERM_CHAR) {
                    // Replace the last read character (\r) with string termination char.
                    *(buffer_nmea_cursor - 1) = '\0';
                    _process_nmea();

                    nmea_read_state = NMEA_STATE_READY;
                    buffer_nmea_cursor = buffer_nmea;
                    continue;
                }

                *buffer_nmea_cursor = c;
                buffer_nmea_cursor++;
                continue;
            }
        }
#endif
    }

}

void ubx_uart_reset() {
#ifdef DECODE_NMEA
    buffer_nmea_cursor = buffer_nmea;
    nmea_read_state = NMEA_STATE_READY;
#endif


#ifdef DECODE_UBX
    buffer_ubx_cursor = buffer_ubx;
    ubx_payload_length = 0;
    ubx_read_state = UBX_STATE_READY;
#endif
}