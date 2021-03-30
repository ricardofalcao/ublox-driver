//
// Created by ricardo on 30/03/21.
//

#include "ublox/ublox_read.h"

#include <stdint.h>

#ifdef DECODE_NMEA
char buffer_nmea[NMEA_BUFFER_SIZE];
char *buffer_nmea_cursor = buffer_nmea;
uint8_t nmea_read_state = NMEA_STATE_READY;
#endif

//

#ifdef DECODE_UBX
char buffer_ubx[UBX_BUFFER_SIZE];
char *buffer_ubx_cursor = buffer_ubx;
uint16_t ubx_payload_length = 0;
uint8_t ubx_read_state = UBX_STATE_READY;
#endif

void ubx_read_inbound(char *buffer, size_t buffer_size) {
    uint8_t c;
    for (size_t i = 0; i < buffer_size; i++) {
        c = (uint8_t) (buffer[i] & 0xFF);

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
                if (buffer_ubx_cursor - buffer_ubx == (6 + ubx_payload_length + 2)) {
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
                    printf("Received NMEA: %s\n", buffer_nmea);

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