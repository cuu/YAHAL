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
#include <cstdio>
#include <cstring>
#include "floppy_statistics.h"
#include "floppy_drv.h"

namespace FLOPPY {

    floppy_statistics floppy_statistics::_statistics;

    void floppy_statistics::show() {
        printf("\n");
        printf("Floppy statistics\n");
        printf("=================\n");
        printf("Number of read_track() operations: %ld\n", _number_of_read_track_ops);

        show_gap(FIELD::GAP1,  _gap_items[0]);
        show_gap(FIELD::GAP2,  _gap_items[1]);
        show_gap(FIELD::GAP3,  _gap_items[2]);
        show_gap(FIELD::GAP4A, _gap_items[3]);

        show_sync(FIELD::SYNC1, _sync_items[0]);
        show_sync(FIELD::SYNC2, _sync_items[1]);
        show_sync(FIELD::SYNC3, _sync_items[2]);
    }


    void floppy_statistics::gap_length(FIELD f, uint16_t len) {
        stat_item * item = &_gap_items[(int)f-(int)FIELD::GAP1][0];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }

    void floppy_statistics::gap_has_pulse_L(FIELD f, uint16_t len) {
        stat_item * item = &_gap_items[(int)f-(int)FIELD::GAP1][1];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }

    void floppy_statistics::gap_end_too_early(FIELD f, uint16_t len) {
        stat_item * item = &_gap_items[(int)f-(int)FIELD::GAP1][2];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }

    void floppy_statistics::gap_missing_end_pulse(FIELD f, uint16_t len) {
        stat_item * item = &_gap_items[(int)f-(int)FIELD::GAP1][3];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }


    void floppy_statistics::sync_length(FIELD f, uint16_t len) {
        stat_item * item = &_sync_items[(int)f-(int)FIELD::SYNC1][0];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }

    void floppy_statistics::sync_L_pulse(FIELD f, uint16_t len) {
        stat_item * item = &_sync_items[(int)f-(int)FIELD::SYNC1][1];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }

    void floppy_statistics::sync_M_too_early(FIELD f, uint16_t len) {
        stat_item * item = &_sync_items[(int)f-(int)FIELD::SYNC1][2];
        item->count++;
        item->sum += len;
        if (len > item->max) item->max = len;
        if (len < item->min) item->min = len;
    }

    void floppy_statistics::show_gap(FIELD f, const stat_item item[4]) {
        printf("%s: ", field_to_str(f));
        int len=0;
        switch(f) {
            case FIELD::GAP1: len = floppy_drv::inst->_format->gap1_size; break;
            case FIELD::GAP2: len = floppy_drv::inst->_format->gap2_size; break;
            case FIELD::GAP3: len = floppy_drv::inst->_format->gap3_size; break;
            case FIELD::GAP4A: len = floppy_drv::inst->_format->gap4a_size; break;
            default: break;
        }
        printf("(Length: %d bytes / %d pulses)\n", len, len * 6);

        printf("        Number of measurements: %lu\n", item[0].count);
        printf("        Measured byte length:  Min=%lu, Max=%lu, Mean=%lu\n",
                        item[0].min, item[0].max, item[0].sum/item[0].count);

        if (item[1].count) {
            printf("        Detected wrong L pulse in %lu cases (pulse %lu to %lu)\n",
                            item[1].count, item[1].min, item[1].max);
        }

        if (item[2].count) {
            printf("        Detected early GAP end in %lu cases (byte %lu to %lu)\n",
                            item[2].count, item[2].min, item[2].max);
        }

        if (item[3].count) {
            printf("        Detected missing end pulse in %lu cases (byte %lu to %lu)\n",
                   item[3].count, item[3].min, item[3].max);
        }

        puts("");
    }

    void floppy_statistics::show_sync(FIELD f, const stat_item item[3]) {
        printf("%s: ", field_to_str(f));
        printf("(Length: 12 bytes / 96 pulses)\n");

        printf("        Number of measurements: %lu\n", item[0].count);
        printf("        Measured pulse length:  Min=%lu, Max=%lu, Mean=%lu\n",
                        item[0].min, item[0].max, item[0].sum/item[0].count);

        if (item[1].count) {
            printf("        Detected wrong L pulse in %lu cases (pulse %lu to %lu)\n",
                   item[1].count, item[1].min, item[1].max);
        }

        if (item[2].count) {
            printf("        Detected too early M pulse in %lu cases (pulse %lu to %lu)\n",
                            item[2].count, item[2].min, item[2].max);
        }
        puts("");
    }

    void floppy_statistics::reset() {
        _number_of_read_track_ops = 0;
        memset(_sync_items, 0, sizeof _sync_items);
        memset(_gap_items, 0, sizeof _gap_items);

        for (auto & _sync_item : _sync_items) {
            for (auto & j : _sync_item) {
                j.min = UINT32_MAX;
            }
        }
        for (auto & _gap_item : _gap_items) {
            for (auto & j : _gap_item) {
                j.min = UINT32_MAX;
            }
        }
    }
}