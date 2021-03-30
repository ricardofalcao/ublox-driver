//
// Created by ricardo on 30/03/21.
//

#include "ublox/bits.h"

uint8_t bits_read_uint8(uint8_t * buffer) {
    return buffer[0];
}

int8_t bits_read_int8(uint8_t * buffer) {
    return (int8_t) buffer[0];
}

uint16_t bits_read_uint16(uint8_t * buffer) {
    return (uint16_t) buffer[0] | (uint16_t) (buffer[1] << 8);
}

int16_t bits_read_int16(uint8_t * buffer) {
    return (int16_t) buffer[0] | (int16_t) (buffer[1] << 8);
}

uint32_t bits_read_uint32(uint8_t * buffer) {
    return (uint32_t) buffer[0] | (uint32_t) (buffer[1] << 8) | (uint32_t) (buffer[2] << 16) | (uint32_t) (buffer[3] << 24);
}

int32_t bits_read_int32(uint8_t * buffer) {
    return (int32_t) buffer[0] | (int32_t) (buffer[1] << 8) | (int32_t) (buffer[2] << 16) | (int32_t) (buffer[3] << 24);
}
