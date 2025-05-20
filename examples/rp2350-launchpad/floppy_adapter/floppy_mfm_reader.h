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
// This is 'context' for the MFM decoder state machine.
// To use this class, set the expected data size and
// throw in MFM pulses from a floppy track. You get
// back a buffer with the decoded data.
//
#ifndef FLOPPY_MFM_READER_H
#define FLOPPY_MFM_READER_H

#include "floppy_defines.h"
#include "floppy_mfm_reader_states.h"
#include "floppy_error_codes.h"
#include "floppy_statistics.h"

namespace FLOPPY {

    class floppy_mfm_reader {
        // The concrete states are our friend :)
        friend class STATE;
        friend class READ_GAP;
        friend class READ_SYNC;
        friend class READ_MARK;
        friend class READ_DATA;

    public:
        floppy_mfm_reader();

        // Configure the field details based on the
        // used floppy format. This method has to be
        // called before the decoding process begins.
        void set_floppy_format(const floppy_format * format);

        inline void set_data_buffer(uint8_t * ptr) {
            _data_ptr = ptr;
        }

        inline void set_data_size(uint16_t size) {
            _data_size = size;
        }

        inline void reset() {
            // Set initial state
            setState(&_read_gap4a);
        }

        inline ret_t process_pulse(PULSE p) {
            if (_data_size) {
                return _state->pulse(p);
            } else return RET_CODE::SUCCESS;
        }

    private:

        // Current state and state instances
        STATE  *    _state {nullptr};

        inline void setState(STATE * s) {
            _state = s;
            if (_state) { _state->enter(); }
        }

        READ_GAP    _read_gap4a;
        READ_SYNC   _read_sync1;
        READ_MARK   _read_iam;
        READ_GAP    _read_gap1;
        READ_SYNC   _read_sync2;
        READ_MARK   _read_id_am;
        READ_DATA   _read_am;
        READ_GAP    _read_gap2;
        READ_SYNC   _read_sync3;
        READ_MARK   _read_d_am;
        READ_DATA   _read_data;
        READ_GAP    _read_gap3;

        // Attributes for pulse decoder
        bool        _even       {false};
        uint8_t     _byte       {0};
        uint8_t     _bit_count  {0};

        // Attributes for track data
        uint8_t *   _data_ptr  {nullptr};
        uint16_t    _data_size {0};

        // Constants for pulse decoding
        const bool EVEN     = true;
        const bool ODD      = false;
        const bool TWO_BITS = true;
        const bool ONE_BIT  = false;

        struct decode_entry {
            bool    two_bits;
            bool    even;
        } _decode_table[3][2] = {
                //      ODD               EVEN
                { { ONE_BIT,  ODD }, {ONE_BIT,  EVEN} }, // PULSE::S
                { { ONE_BIT,  EVEN}, {TWO_BITS, ODD } }, // PULSE::M
                { { TWO_BITS, ODD }, {TWO_BITS, EVEN} }  // PULSE::L
        };

        // Decode a single MFM pulse
        ret_t decode_pulse(PULSE p);

        inline void write_byte(uint8_t b) {
            *_data_ptr++ = b;
            --_data_size;
        }
    };

}

#endif // FLOPPY_MFM_READER_H
