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
// This class implements the 4 states of the MFM decoder
// state machine (READ_GAP, READ_SYNC, READ_MARK, READ_DATA).
// Together with the class MFM_reader (the 'context'), these
// classes implement a classical state machine design pattern.

#ifndef FLOPPY_MFM_READER_STATES_H
#define FLOPPY_MFM_READER_STATES_H

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <array>
#include "floppy_error_codes.h"

namespace FLOPPY {

    class floppy_mfm_reader;

    // The MFM pulse types (Short, Medium, Long).
    // The concrete duration depends on the data
    // rate (e.g. 250bps or 500bps)
    enum class PULSE : uint8_t {
        S = 0, M = 1, L = 2
    };

    ////////////////////////////
    // Base class for all states
    ////////////////////////////
    class STATE {
    public:
        STATE(floppy_mfm_reader &r, FIELD field_type, STATE * next)
        : _context(r), _field_type(field_type), _next_state(next) {}
        virtual ~STATE() = default;

        // Method to be called when a new state is entered
        virtual void enter() = 0;
        // Method to be called when a new MFM pulse is detected
        virtual ret_t pulse(PULSE) = 0;
        // Method to be called when a complete byte has been decoded
        virtual ret_t byte(uint8_t) { return RET_CODE::SUCCESS; };

        // Set the maximum number of MFM pulses, which
        // are to be processed by the concrete state.
        inline void set_max_pulses(const uint16_t p) {
            _max_pulses = p;
        }

    protected:
        floppy_mfm_reader & _context;
        FIELD        _field_type;
        STATE *      _next_state;
        // Most states need to limit the number of
        // processed pulses. So provide related
        // attributes in the base class
        uint16_t _pulse_count {0};
        uint16_t _max_pulses  {0};
    };

    //////////////////////////////////////////////
    // Read an MFM GAP (0x4e) until a SYNC pattern
    // starts. See implementation for details.
    //////////////////////////////////////////////
    class READ_GAP : public STATE {
    public:
        READ_GAP(floppy_mfm_reader &r,
                 FIELD field,
                 STATE * next)
        : STATE(r, field, next) {}

        void  enter() override;
        ret_t pulse(PULSE p) override;

        // Set the minimum number of 0x4e pattern to
        // successfully leave this state
        inline void set_tag_threshold(const uint8_t t) {
            _tag_threshold = t;
        }

    private:
        uint16_t _tag_count {0};
        uint16_t _tag_threshold {0};

        uint16_t _shift_window {0};
        uint16_t _s_counter {0};
    };

    //////////////////////////////////
    // Read in MFM SYNC bytes (0x00).
    // See implementation for details.
    //////////////////////////////////
    class READ_SYNC : public STATE {
    public:
        READ_SYNC(floppy_mfm_reader &r,
                  FIELD field,
                  STATE * next)
        : STATE(r, field, next) {}

        void  enter() override;
        ret_t pulse(PULSE p) override;
    private:
        uint16_t _s_counter {0};
    };

    /////////////////////////////////////
    // Read a four-byte MFM address mark.
    // See implementation for details.
    /////////////////////////////////////
    class READ_MARK : public STATE {
    public:
        READ_MARK(floppy_mfm_reader &r,
                  FIELD field,
                  STATE * next)
        : STATE(r, field, next) {}

        void enter() override;
        ret_t pulse(PULSE p) override;
        ret_t byte(uint8_t b) override;

        // Set the mark to be processed by this state
        inline void set_mark(std::array<uint8_t, 4> mark) {
            _mark = mark;
        }

    private:
        std::array<uint8_t, 4> _mark {};
        uint8_t _mark_index {0};
    };

    ///////////////////////////////////////////
    // Read a chunk of data from the MFM stream.
    ///////////////////////////////////////////
    class READ_DATA : public STATE {
    public:
        READ_DATA(floppy_mfm_reader &r,
                  FIELD field,
                  STATE * next)
        : STATE(r, field, next) {}

        void enter() override;
        ret_t pulse(PULSE P) override;
        ret_t byte(uint8_t b) override;

        // Set the number of bytes to be read by this state
        inline void set_size(uint16_t s) {
            _size = s;
        }

    private:
        uint16_t  _size {0};
        uint16_t  _byte_counter {0};
    };

}

#endif // FLOPPY_MFM_READER_STATES_H
