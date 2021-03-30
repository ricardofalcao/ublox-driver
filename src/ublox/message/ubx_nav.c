//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>
#include <ublox/bits.h>
#include "ublox/message/ubx_nav.h"

#ifdef DECODE_UBX

#define PVT_PAYLOAD_LENGTH 92

void _process_pvt(uint8_t packet_id, uint8_t *payload, size_t payload_length) {
    if (payload_length != PVT_PAYLOAD_LENGTH) {
        printf("Error decoding NAV-PVT packet: Payload length did not match (%d != %d)", payload_length,
               PVT_PAYLOAD_LENGTH);
        return;
    }

    uint32_t tow = bits_read_uint32(payload + 0);
    uint16_t year = bits_read_uint16(payload + 4);
    uint8_t month = bits_read_uint8(payload + 6);
    uint8_t day = bits_read_uint8(payload + 7);
    uint8_t hour = bits_read_uint8(payload + 8);
    uint8_t minute = bits_read_uint8(payload + 9);
    uint8_t second = bits_read_uint8(payload + 10);
    uint8_t valid = bits_read_uint8(payload + 11);
    uint32_t time_accuracy = bits_read_uint32(payload + 12);
    int32_t nano = bits_read_int32(payload + 16);
    uint8_t fix = bits_read_uint8(payload + 20);
    uint8_t flags = bits_read_uint8(payload + 21);
    uint8_t flags2 = bits_read_uint8(payload + 22);
    uint8_t satellites_num = bits_read_uint8(payload + 23);
    int32_t longitude = bits_read_int32(payload + 24);
    int32_t latitude = bits_read_int32(payload + 28);
    int32_t height = bits_read_int32(payload + 32);
    int32_t height_msl = bits_read_int32(payload + 36);
    uint32_t horizontal_accuracy = bits_read_uint32(payload + 40);
    uint32_t vertical_accuracy = bits_read_uint32(payload + 44);
    int32_t velocity_n = bits_read_int32(payload + 48);
    int32_t velocity_e = bits_read_int32(payload + 52);
    int32_t velocity_d = bits_read_int32(payload + 56);
    int32_t ground_speed = bits_read_int32(payload + 60);
    int32_t motion_heading = bits_read_int32(payload + 64);
    uint32_t speed_accuracy = bits_read_uint32(payload + 68);
    uint32_t heading_accuracy = bits_read_uint32(payload + 72);
    uint16_t position_dop = bits_read_uint16(payload + 76);
    uint8_t flags3 = bits_read_uint8(payload + 78);
    int32_t vehicle_heading = bits_read_int32(payload + 84);
    int16_t magnetic_declination = bits_read_int16(payload + 88);
    uint16_t magnetic_declination_accuracy = bits_read_uint16(payload + 90);

    printf("Lat: %f deg | Lon: %f deg | H: %d mm\n", (double) latitude * 1e-7, (double) longitude * 1e-7, height);
}

void message_process_ubx_nav(uint8_t packet_id, uint8_t *payload, size_t payload_length) {
    switch (packet_id) {
        case UBX_MESSAGE_NAV_PVT: {
            _process_pvt(packet_id, payload, payload_length);
            break;
        }
    }
}

#endif