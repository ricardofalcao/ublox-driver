//
// Created by ricardo on 30/03/21.
//

#ifndef UBLOX_BITS_H
#define UBLOX_BITS_H

#include <stdint.h>

uint8_t bits_read_uint8(uint8_t * buffer);

int8_t bits_read_int8(uint8_t * buffer);

uint16_t bits_read_uint16(uint8_t * buffer);

int16_t bits_read_int16(uint8_t * buffer);

uint32_t bits_read_uint32(uint8_t * buffer);

int32_t bits_read_int32(uint8_t * buffer);

/*
 *
 */

void bits_write_uint8(uint8_t * buffer, uint8_t value);

void bits_write_int8(uint8_t * buffer, int8_t value);

void bits_write_uint16(uint8_t * buffer, uint16_t value);

void bits_write_int16(uint8_t * buffer, int16_t value);

void bits_write_uint32(uint8_t * buffer, uint32_t value);

void bits_write_int32(uint8_t * buffer, int32_t value);

#endif //UBLOX_BITS_H
