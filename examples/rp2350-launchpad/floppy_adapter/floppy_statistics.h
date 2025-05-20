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
#ifndef FLOPPY_STATISTICS_H
#define FLOPPY_STATISTICS_H

#include <cstdint>
#include <limits>
#include "floppy_mfm_reader_states.h"

namespace FLOPPY {

    class floppy_mfm_reader;

    struct stat_item {
        stat_item() : count(0), min(UINT32_MAX), max(0), sum(0) {}
        uint32_t count;
        uint32_t min;
        uint32_t max;
        uint32_t sum;
    };

    class floppy_statistics {
    public:

        void show();

        void reset();

        void gap_has_pulse_L(FIELD f, uint16_t len);
        void gap_length(FIELD f, uint16_t len);
        void gap_end_too_early(FIELD f, uint16_t len);
        void gap_missing_end_pulse(FIELD f, uint16_t len);

        void sync_length (FIELD f, uint16_t len);
        void sync_M_too_early(FIELD f, uint16_t);
        void sync_L_pulse(FIELD f, uint16_t len);

        static inline floppy_statistics & inst() {
            return _statistics;
        }

    private:
        // Statistics is singleton
        floppy_statistics() = default;
        static floppy_statistics _statistics;

        void show_sync(FIELD f, const stat_item item[3]);
        void show_gap (FIELD f, const stat_item item[4]);

        uint32_t        _number_of_read_track_ops {0};
        stat_item       _sync_items[3][3] {};
        stat_item       _gap_items[5][4] {};
    };
}

#endif // FLOPPY_STATISTICS_H
