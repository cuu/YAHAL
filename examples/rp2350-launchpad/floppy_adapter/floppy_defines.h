// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
#ifndef FLOPPY_DEFINES_H
#define FLOPPY_DEFINES_H

#include <cstdint>
#include <array>
#include "gpio_interface.h"

// Type for the various address marks within a track:
//  * IAM:  Index address mark
//  * IDAM: Sector ID address mark
//  * DAM:  Sector Data address mark
// All marks are 4 bytes long
typedef std::array<uint8_t, 4> MARK_TYPE;

namespace FLOPPY {

    // A struct containing all gpio (interfaces)
    // which we need to connect to the floppy drive
    struct floppy_pins {
        gpio_interface & index;
        gpio_interface & drive_select;
        gpio_interface & motor_on;
        gpio_interface & direction_select;
        gpio_interface & step;
        gpio_interface & write_data;
        gpio_interface & write_gate;
        gpio_interface & track_00;
        gpio_interface & write_protect;
        gpio_interface & read_data;
        gpio_interface & side_one_select;
        gpio_interface & disk_change;
    };

    // Size enum for floppy drives and floppy disks
    enum class FLOPPY_SIZE : uint8_t {
        _3_inch, _3_5_inch, _5_25_inch, _8_inch
    };

    // Struct describing a floppy disk drive
    struct floppy_drive {
        const char *    name;
        // Basic floppy drive items
        FLOPPY_SIZE     floppy_size;
        uint16_t        number_of_tracks;
        uint16_t        number_of_heads;
        // Step configuration
        uint16_t        step_pulse_ms;
        uint16_t        step_interval_ms;
        uint16_t        step_settle_time_ms;
        // Motor configuration
        uint16_t        motor_speed_rpm;
        uint16_t        motor_on_delay_ms;
        uint16_t        motor_follow_up_time_ms;
        // Head load configuration
        bool            has_head_load;
        uint16_t        head_load_time_ms;
    };

    // Struct describing a floppy disk format
    struct floppy_format {
        const char *    name;
        FLOPPY_SIZE     floppy_size;
        uint16_t        data_rate_kHz;
        uint16_t        number_of_tracks;
        bool            double_sided;
        uint16_t        sector_size;
        uint16_t        sectors_per_track;
        // MFM format details
        MARK_TYPE       I_AM;
        MARK_TYPE       ID_AM;
        MARK_TYPE       D_AM;
        uint16_t        gap1_size;
        uint16_t        gap2_size;
        uint16_t        gap3_size;
        uint16_t        gap4a_size;
        uint16_t        gap4b_size;
    };

    // Struct describing the sector ID, which follows
    // the sector ID address mark (IDAM) for every sector
    struct __attribute__((__packed__)) id_am_format {
        uint8_t     cylinder;
        uint8_t     head;
        uint8_t     sector;
        uint8_t     sector_size;
        uint16_t    crc_id;
    };

    // List of all available floppy disk drive definitions
    extern floppy_drive  TEAC_FD_235HF;

    // List of all available floppy disk formats
    extern floppy_format    IBM_1440_kB;
    extern floppy_format    IBM_1680_kB;
    extern floppy_format    IBM_720_kB;

    // List of all available floppy disk formats.
    extern std::array<floppy_format *, 3> floppy_formats;
}

#endif // FLOPPY_DEFINES_H
