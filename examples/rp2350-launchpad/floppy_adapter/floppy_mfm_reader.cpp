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
#include "floppy_mfm_reader.h"

namespace FLOPPY {

    floppy_mfm_reader::floppy_mfm_reader()
            : _read_gap4a (*this, FIELD::GAP4A,       &_read_sync1),
              _read_sync1 (*this, FIELD::SYNC1,       &_read_iam),
              _read_iam   (*this, FIELD::IAM,         &_read_gap1),
              _read_gap1  (*this, FIELD::GAP1,        &_read_sync2),
              _read_sync2 (*this, FIELD::SYNC2,       &_read_id_am),
              _read_id_am (*this, FIELD::IDAM,        &_read_am),
              _read_am    (*this, FIELD::DATA_ID,     &_read_gap2),
              _read_gap2  (*this, FIELD::GAP2,        &_read_sync3),
              _read_sync3 (*this, FIELD::SYNC3,       &_read_d_am),
              _read_d_am  (*this, FIELD::DAM,         &_read_data),
              _read_data  (*this, FIELD::DATA_SECTOR, &_read_gap3),
              _read_gap3  (*this, FIELD::GAP3,        &_read_sync2) {

        // Set initial state
        reset();
    }

    void floppy_mfm_reader::set_floppy_format(const floppy_format * format) {

        // SYNC fields are always 12 bytes long,
        // which are 12*8 = 96 S-pulses. SYNC fields
        // might be a little bit longer (e.g. SYNC3)
        // due to sector write operations, but should
        // not be longer than 150 pulses.
        _read_sync1.set_max_pulses(150);
        _read_sync2.set_max_pulses(150);
        _read_sync3.set_max_pulses(150);

        // Address marks are always 4 bytes long, which
        // corresponds to a maximum of 4*8 = 32 pulses.
        _read_iam.set_mark(format->I_AM);
        _read_iam.set_max_pulses(32);
        _read_id_am.set_mark(format->ID_AM);
        _read_id_am.set_max_pulses(32);
        _read_d_am.set_mark(format->D_AM);
        _read_d_am.set_max_pulses(32);

        // The GAP field have different length, and
        // use the pattern 0x4e, which is encoded in
        // 6 pulses as MMSSMM. Multiply with 4/3 for
        // the maximal pulse count and with 3/4 for
        // the threshold (minimal number of 0x4E pattern).
        _read_gap1.set_max_pulses    ((format->gap1_size*6*4)/3);
        _read_gap1.set_tag_threshold ((format->gap1_size*3)/4);
        _read_gap2.set_max_pulses    ((format->gap2_size*6*4)/3);
        _read_gap2.set_tag_threshold ((format->gap2_size*3)/4);
        _read_gap4a.set_max_pulses   ((format->gap4a_size*6*4)/3);
        _read_gap4a.set_tag_threshold((format->gap4a_size*3)/4);

        // GAP3 is often longer than expected, and sometimes
        // also shorter due to sector write operations. So
        // use a bigger tolerance here.
        _read_gap3.set_max_pulses(format->gap3_size*6*2);
        _read_gap3.set_tag_threshold(format->gap3_size/2);

        // Set data sizes. The address mark is always
        // 4 bytes + 2 bytes CRC, so 6 in total. The
        // sizes of the sector data has to be increased
        // by 2 CRC bytes!
        _read_am.set_size(sizeof(id_am_format));
        _read_data.set_size(format->sector_size+2);
    }

    ret_t floppy_mfm_reader::decode_pulse(PULSE p) {
        auto * e = &_decode_table[(uint8_t)p][_even];
        bool new_byte_flag = false;
        uint8_t new_byte {0};

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
        return RET_CODE::CONTINUE;
    }

}

