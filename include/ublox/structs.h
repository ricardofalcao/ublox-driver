//
// Created by ricardo on 31/03/21.
//

#ifndef UBLOX_STRUCTS_H
#define UBLOX_STRUCTS_H

#include <stdint.h>

typedef struct {
    // time of week of the navigation epoch.
    uint32_t time_of_week;

    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    int32_t nanosecond;

    /*
     * Validity flags
     * Use the UBX_TIME_FLAG_X macros
     */
    uint8_t validity;

    /*
     * Time accuracy estimate in ns (UTC)
     */
    uint32_t accuracy;
} GpsTime_t;

typedef struct {
    // Geometric DOP
    float geometric;
    // Position DOP
    float position;
    // Time DOP
    float time;
    // Vertical DOP
    float vertical;
    // Horizontal DOP
    float horizontal;
    // Northing DOP
    float northing;
    // Easting DOP
    float easting;
} GpsDOP_t;

typedef struct {
    // GPS Time
    GpsTime_t time;
    // GPS DOP
    GpsDOP_t dop;

    /*
     * Fix type
     * Use the UBX_FIX_TYPE_X macros
     */
    uint8_t type;
    /*
     * Invalidity fields
     * Use the UBX_FIX_INVALID_POSITION macro
     */
    uint8_t invalidity;
    /*
     * Validity flags
     * Use the UBX_FIX_FLAG_X macros
     */
    uint16_t flags;
    // Number of satellites
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
    // in mm/s
    int32_t velocity_north;
    int32_t velocity_east;
    int32_t velocity_down;
    int32_t ground_speed;

    // in deg
    float motion_heading;
    float vehicle_heading;

    // in mm/s
    uint32_t speed_accuracy;

    // in deg
    float heading_accuracy;

    // in deg
    float magnetic_declination;
    float magnetic_declination_accuracy;
} GpsVelocity_t;

#endif //UBLOX_STRUCTS_H
