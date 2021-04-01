//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>
#include <ublox/bits.h>
#include <ublox/structs.h>
#include "ublox/message/ubx_nav.h"

#ifdef DECODE_UBX

#define PVT_PAYLOAD_LENGTH 92
#define HPPOSLLH_PAYLOAD_LENGTH 36
#define DOP_PAYLOAD_LENGTH 18
#define EOE_PAYLOAD_LENGTH 4

GpsFix_t _fix;
GpsVelocity_t _velocity;

#ifdef UBX_SUBSCRIBE_PVT
void _process_pvt(uint8_t *payload, size_t payload_length) {
    if (payload_length != PVT_PAYLOAD_LENGTH) {
        LOG("Error decoding NAV-PVT packet: Payload length did not match (%d != %d)", payload_length,
            PVT_PAYLOAD_LENGTH);
        return;
    }

    // time
    _fix.time.time_of_week = bits_read_uint32(payload + 0);
    _fix.time.year = bits_read_uint16(payload + 4);
    _fix.time.month = bits_read_uint8(payload + 6);
    _fix.time.day = bits_read_uint8(payload + 7);
    _fix.time.hour = bits_read_uint8(payload + 8);
    _fix.time.minute = bits_read_uint8(payload + 9);
    _fix.time.second = bits_read_uint8(payload + 10);
    _fix.time.validity = bits_read_uint8(payload + 11);
    _fix.time.accuracy = bits_read_uint32(payload + 12);
    _fix.time.nanosecond = bits_read_int32(payload + 16);

    _fix.type = bits_read_uint8(payload + 20);

    uint8_t flags = bits_read_uint8(payload + 21);
    uint8_t flags2 = bits_read_uint8(payload + 22);
    _fix.flags = ((uint16_t) flags2 << 8) | flags;

    _fix.satellites = bits_read_uint8(payload + 23);
    _fix.longitude = (double) bits_read_int32(payload + 24) * 1E-7;
    _fix.latitude = (double) bits_read_int32(payload + 28) * 1E-7;
    _fix.height = (float) bits_read_int32(payload + 32);
    _fix.height_msl = (float) bits_read_int32(payload + 36);
    _fix.horizontal_accuracy = bits_read_uint32(payload + 40);
    _fix.vertical_accuracy = bits_read_uint32(payload + 44);

    _velocity.velocity_north = bits_read_int32(payload + 48);
    _velocity.velocity_east = bits_read_int32(payload + 52);
    _velocity.velocity_down = bits_read_int32(payload + 56);
    _velocity.ground_speed = bits_read_int32(payload + 60);
    _velocity.motion_heading = (float) bits_read_int32(payload + 64) * 1E-5;
    _velocity.speed_accuracy = bits_read_uint32(payload + 68);
    _velocity.heading_accuracy = (float) bits_read_uint32(payload + 72) * 1E-5;

    _fix.invalidity = bits_read_uint8(payload + 78);

    _velocity.vehicle_heading = (float) bits_read_int32(payload + 84) * 1E-5;
    _velocity.magnetic_declination = (float) bits_read_int16(payload + 88) * 1E-2;
    _velocity.magnetic_declination_accuracy = (float) bits_read_uint16(payload + 90) * 1E-2;
}
#endif

#ifdef UBX_SUBSCRIBE_HPVT
void _process_hpposllh(uint8_t *payload, size_t payload_length) {
    if (payload_length != HPPOSLLH_PAYLOAD_LENGTH) {
        LOG("Error decoding NAV-HPPOSLLH packet: Payload length did not match (%d != %d)", payload_length,
            PVT_PAYLOAD_LENGTH);
        return;
    }

    _fix.validity = bits_read_uint8(payload + 3);

    _fix.time.time_of_week = bits_read_uint32(payload + 4);

    _fix.longitude = (double) bits_read_int32(payload + 8) * 1E-7;
    _fix.latitude = (double) bits_read_int32(payload + 12) * 1E-7;
    _fix.height = (float) bits_read_int32(payload + 16);
    _fix.height_msl = (float) bits_read_int32(payload + 20);

    _fix.longitude += (double) bits_read_uint8(payload + 24) * 1E-9;
    _fix.latitude += (double) bits_read_uint8(payload + 25) * 1E-9;
    _fix.height += (float) bits_read_uint8(payload + 26) * 0.1f;
    _fix.height_msl += (float) bits_read_uint8(payload + 27) * 0.1f;

    _fix.horizontal_accuracy = bits_read_uint32(payload + 28);
    _fix.vertical_accuracy = bits_read_uint32(payload + 32);
}
#endif

#ifdef UBX_SUBSCRIBE_DOP
void _process_dop(uint8_t *payload, size_t payload_length) {
    if (payload_length != DOP_PAYLOAD_LENGTH) {
        LOG("Error decoding NAV-DOP packet: Payload length did not match (%d != %d)", payload_length,
            PVT_PAYLOAD_LENGTH);
        return;
    }

    // time
    _fix.time.time_of_week = bits_read_uint32(payload + 0);
    _fix.dop.geometric = (float) bits_read_uint16(payload + 4) * 0.01f;
    _fix.dop.position = (float) bits_read_uint16(payload + 6) * 0.01f;
    _fix.dop.time = (float) bits_read_uint16(payload + 8) * 0.01f;
    _fix.dop.vertical = (float) bits_read_uint16(payload + 10) * 0.01f;
    _fix.dop.horizontal = (float) bits_read_uint16(payload + 12) * 0.01f;
    _fix.dop.northing = (float) bits_read_uint16(payload + 14) * 0.01f;
    _fix.dop.easting = (float) bits_read_uint16(payload + 16) * 0.01f;
}
#endif

void _process_eoe(uint8_t *payload, size_t payload_length) {
    if (payload_length != EOE_PAYLOAD_LENGTH) {
        LOG("Error decoding NAV-EOE packet: Payload length did not match (%d != %d)", payload_length,
            PVT_PAYLOAD_LENGTH);
        return;
    }

    _fix.time.time_of_week = bits_read_uint32(payload + 0);
    ubx_fix = _fix;
    ubx_velocity = _velocity;

    LOG("[%d/%d/%d %d:%d:%d.%d] Fix: %d(%d)  |  Lat: %.9f deg  | Lon: %.9f deg  | H: %.2f mm\n", ubx_fix.time.day, ubx_fix.time.month, ubx_fix.time.year, ubx_fix.time.hour, ubx_fix.time.minute, ubx_fix.time.second, ubx_fix.time.nanosecond, ubx_fix.type, !!(ubx_fix.flags & UBX_FIX_FLAG_OK), ubx_fix.latitude, ubx_fix.longitude, ubx_fix.height_msl);
}

void ubx_process_ubx_nav(uint8_t packet_id, uint8_t *payload, size_t payload_length) {
    switch (packet_id) {
#ifdef UBX_SUBSCRIBE_PVT
        case UBX_MESSAGE_NAV_PVT: {
            _process_pvt(payload, payload_length);
            break;
        }
#endif

#ifdef UBX_SUBSCRIBE_HPVT
        case UBX_MESSAGE_NAV_HPPOSLLH: {
            _process_hpposllh(payload, payload_length);
            break;
        }
#endif

#ifdef UBX_SUBSCRIBE_DOP
        case UBX_MESSAGE_NAV_DOP: {
            _process_dop(payload, payload_length);
            break;
        }
#endif

        case UBX_MESSAGE_NAV_EOE: {
            _process_eoe(payload, payload_length);
            break;
        }
    }
}

#endif