//
// Created by andreas on 13.05.25.
//

#ifndef MFM_READER_H
#define MFM_READER_H

#include "MFM_reader_states.h"
#include "MFM_errors.h"

class MFM_reader {

    friend class MFM::STATE;
    friend class MFM::READ_GAP;
    friend class MFM::READ_SYNC;
    friend class MFM::READ_TAG;
    friend class MFM::READ_DATA;

    public:
    explicit MFM_reader(uint8_t * data_ptr);

    inline void set_data_size(uint16_t size) {
        _data_size = size;
    }

    inline int process_pulse(MFM::PULSE p) {
        if (_data_size) {
            return _state->pulse(p);
        } else return MFM::FINISHED;
    }

private:

    // Current state and state instances
    MFM::STATE  *   _state {nullptr};

    MFM::READ_GAP   _read_gap4a;
    MFM::READ_SYNC  _read_sync1;
    MFM::READ_TAG   _read_iam;
    MFM::READ_GAP   _read_gap1;
    MFM::READ_SYNC  _read_sync2;
    MFM::READ_TAG   _read_id_am;
    MFM::READ_DATA  _read_am;
    MFM::READ_GAP   _read_gap2;
    MFM::READ_SYNC  _read_sync3;
    MFM::READ_TAG   _read_d_am;
    MFM::READ_DATA  _read_data;
    MFM::READ_GAP   _read_gap3;

    // Attributes for pulse decoder
    bool            _even       {false};
    uint8_t         _byte       {0};
    uint8_t         _bit_count  {0};

    // Attributes for track data
    uint8_t *       _data_ptr;
    uint16_t        _data_size {0};

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

    inline void setState(MFM::STATE * s) {
        _state = s;
        if (_state) { _state->enter(); }
    }

    inline int decode_pulse(MFM::PULSE p) {
        auto * e = &_decode_table[(uint8_t)p][_even];
        bool new_byte_flag = false;
        uint8_t new_byte;

        // Shift in first bit
        _byte <<= 1;
        _byte |= _even;
        _bit_count++;
        // Check if we have a complete byte to store
        if (_bit_count == 8) {
            _bit_count  = 0;
            new_byte_flag = true;
            new_byte = _byte;
        }
        // Shift in second bit if necessary
        if (e->two_bits) {
            _byte <<= 1;
            _bit_count++;
            // Check if we have a complete byte to store
            if (_bit_count == 8) {
                _bit_count  = 0;
                new_byte_flag = true;
                new_byte = _byte;
            }
        }
        // Set the new even value
        _even = e->even;

        // Let the current state process the byte
        if (new_byte_flag) {
            return _state->byte(new_byte);
        }
        return MFM::WORKING;
    }

    inline void write_byte(uint8_t b) {
        *_data_ptr++ = b;
        --_data_size;
    }
};

#endif // MFM_READER_H
