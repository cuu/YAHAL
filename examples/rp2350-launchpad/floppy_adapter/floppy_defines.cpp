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
#include "floppy_defines.h"

namespace FLOPPY {

    floppy_drive TEAC_FD_235HF = {
            .name                       = "TEAC FD 235HF 3.5 inch disk drive",
            .floppy_size                = FLOPPY_SIZE::_3_5_inch,
            .number_of_tracks           = 80,
            .number_of_heads            = 2,
            .step_pulse_ms              = 1,
            .step_interval_ms           = 4,
            .step_settle_time_ms        = 16,
            .motor_speed_rpm            = 300,
            .motor_on_delay_ms          = 500,
            .motor_follow_up_time_ms    = 3000,
            .has_head_load              = false,
            .head_load_time_ms          = 0
    };

    floppy_format IBM_1440_kB {
            .name               = "IBM 1.44MB (DS,HD,80 tracks,18 sec/track)",
            .floppy_size        = FLOPPY_SIZE::_3_5_inch,
            .data_rate_kHz      = 500,
            .number_of_tracks   = 80,
            .number_of_heads    = 2,
            .sector_size        = 512,
            .sectors_per_track  = 18,
            .I_AM               = {0xc2, 0xc2, 0xc2, 0xfc},
            .ID_AM              = {0xa1, 0xa1, 0xa1, 0xfe},
            .D_AM               = {0xa1, 0xa1, 0xa1, 0xfb},
            .gap1_size          = 50,
            .gap2_size          = 22,
            .gap3_size          = 80,
            .gap4a_size         = 80,
            .gap4b_size         = 80
    };

    floppy_format IBM_1680_kB {
            .name               = "IBM 1.68MB DMF format (DS,HD,80 tracks,21 sec/track)",
            .floppy_size        = FLOPPY_SIZE::_3_5_inch,
            .data_rate_kHz      = 500,
            .number_of_tracks   = 80,
            .number_of_heads    = 2,
            .sector_size        = 512,
            .sectors_per_track  = 21,
            .I_AM               = {0xc2, 0xc2, 0xc2, 0xfc},
            .ID_AM              = {0xa1, 0xa1, 0xa1, 0xfe},
            .D_AM               = {0xa1, 0xa1, 0xa1, 0xfb},
            .gap1_size          = 50,
            .gap2_size          = 22,
            .gap3_size          = 8,
            .gap4a_size         = 80,
            .gap4b_size         = 80
    };

    floppy_format IBM_720_kB {
            .name               = "IBM 720kB (DS,DD,80 tracks,9 sec/track)",
            .floppy_size        = FLOPPY_SIZE::_3_5_inch,
            .data_rate_kHz      = 250,
            .number_of_tracks   = 80,
            .number_of_heads    = 2,
            .sector_size        = 512,
            .sectors_per_track  = 9,
            .I_AM               = {0xc2, 0xc2, 0xc2, 0xfc},
            .ID_AM              = {0xa1, 0xa1, 0xa1, 0xfe},
            .D_AM               = {0xa1, 0xa1, 0xa1, 0xfb},
            .gap1_size          = 50,
            .gap2_size          = 22,
            .gap3_size          = 80,
            .gap4a_size         = 60,
            .gap4b_size         = 80
    };

    // Array of all available floppy formats. This
    // array will be used during the auto-detection process.
    std::array<floppy_format *, 3> floppy_formats {
        &IBM_1440_kB,
        &IBM_1680_kB,
        &IBM_720_kB
    };
}

