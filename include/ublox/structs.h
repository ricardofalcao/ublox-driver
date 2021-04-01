//
// Created by ricardo on 31/03/21.
//

#ifndef UBLOX_STRUCTS_H
#define UBLOX_STRUCTS_H

#include <stdint.h>

typedef struct {
    uint32_t time_of_week;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t nanosecond;

    uint8_t flags;
    uint32_t accuracy;
} GpsTime_t;

typedef struct {
    float geometric;
    float position;
    float time;
    float vertical;
    float horizontal;
    float northing;
    float easting;
} GpsDOP_t;

typedef struct {
    GpsTime_t time;
    GpsDOP_t dop;

    uint8_t type;
    uint8_t validity;
    uint16_t flags;
    uint8_t satellites;

    // in rad
    double longitude;
    double latitude;

    // in mm
    float height;
    float height_msl;

    // in mm
    uint32_t horizontal_accuracy;
    uint32_t vertical_accuracy;
} GpsFix_t;

typedef struct {
    int32_t velocity_north;
    int32_t velocity_east;
    int32_t velocity_down;
    int32_t ground_speed;

    float motion_heading;
    float vehicle_heading;

    uint32_t speed_accuracy;
    float heading_accuracy;

    float magnetic_declination;
    float magnetic_declination_accuracy;
} GpsVelocity_t;

#endif //UBLOX_STRUCTS_H
