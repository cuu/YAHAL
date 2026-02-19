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
#include "floppy_mfm_reader_states.h"
#include "floppy_logger.h"

namespace FLOPPY {

    //////////////////////////
    // READ_GAP implementation
    //////////////////////////
    void READ_GAP::enter() {
        LOG(LOG_DEBUG, "READ_GAP::enter()");
        // Reset tag variables
        _pulse_count  = 0;
        _tag_count    = 0;
        _shift_window = 0;
        _s_counter    = 0;
    }
    ret_t READ_GAP::pulse(PULSE p) {
        LOG(LOG_DEBUG, "READ_GAP::pulse(%d) pulse_count:%d tag_count:%d", p, _pulse_count, _tag_count);
        // Check maximal pulse count
        if (++_pulse_count > _max_pulses) {
            return {RET_CODE::TOO_MANY_PULSES, _field_type};
        }
        // Check for wrong L pulses. The 'window' method
        // used below will simply ignore these wrong pulses,
        // but the statistics class will count them.
        if (p == PULSE::L) {
            floppy_statistics::inst().gap_has_pulse_L(_field_type, _pulse_count);
        }

        // Shift in the pulse into our three-byte window
        _shift_window <<= 2;
        _shift_window |= (uint8_t)p;
        _shift_window &= 0x0fff;

        // Check for MMSSMM pattern (0x4e)
        if (_shift_window == 0x0505) {
            ++_tag_count;
        // Check for MMSSMS pattern (last 0x4e before SYNC)
        } else if (_shift_window == 0x0504) {
            ++_tag_count;
            if (_tag_count >= _tag_threshold) {
                floppy_statistics::inst().gap_length(_field_type, _tag_count);
                _context.setState(_next_state);
            } else {
                floppy_statistics::inst().gap_end_too_early(_field_type, _tag_count);
            }
        }
        // Sometimes the final gap tag MMSSMS is overwritten in GAP2, and
        // the SYNC pulses (S) start without it. So try to detect 5 S pulses
        // in a row, and also change state in this case.
        if (p == PULSE::S) {
            ++_s_counter;
            if (_s_counter > 5 && _tag_count >= _tag_threshold) {
                floppy_statistics::inst().gap_missing_end_pulse(_field_type, _tag_count);
                _context.setState(_next_state);
            }
        } else {
            _s_counter = 0;
        }
        return RET_CODE::CONTINUE;
    }

    ///////////////////////////
    // READ_SYNC implementation
    ///////////////////////////
    void READ_SYNC::enter() {
        LOG(LOG_DEBUG, "READ_SYNC::enter()");
        _pulse_count = 0;
        _s_counter   = 1;
    }
    ret_t READ_SYNC::pulse(PULSE p) {
        LOG(LOG_DEBUG, "READ_SYNC::pulse(%d) _pulse_count=%d", p, _pulse_count);
        if (++_pulse_count > _max_pulses) {
            return {RET_CODE::TOO_MANY_PULSES, _field_type};
        }
        if (p == PULSE::S) {
            // Regular S pulse
            ++_s_counter;
        } else if (p == PULSE::M) {
            ++_s_counter;
            if (_s_counter > 80) {
                floppy_statistics::inst().sync_length(_field_type, _s_counter);
                _context.setState(_next_state);
            } else {
                floppy_statistics::inst().sync_M_too_early(_field_type, _s_counter);
            }
        } else {
            // Wrong L pulse in SYNC
            floppy_statistics::inst().sync_L_pulse(_field_type, _s_counter);
        }
        return RET_CODE::CONTINUE;
    }

    ///////////////////////////
    // Read an MFM address mark
    ///////////////////////////
    void READ_MARK::enter() {
        LOG(LOG_DEBUG, "READ_MARK::enter() tag:0x%x", _mark[3]);
        _pulse_count = 0;
        _mark_index   = 0;
        // Prepare for address mark decoding
        _context._byte = 0;
        _context._even = true;
        _context._bit_count = 0;
    }
    ret_t READ_MARK::pulse(PULSE p) {
        LOG(LOG_DEBUG, "READ_MARK::pulse(%d)", p);
        if (++_pulse_count > _max_pulses) {
            return {RET_CODE::TOO_MANY_PULSES, _field_type};
        } else {
            return _context.decode_pulse(p);
        }
    }
    ret_t READ_MARK::byte(uint8_t b) {
        LOG(LOG_DEBUG, "READ_MARK::byte(0x%x)", b);
        if (b == _mark[_mark_index]) {
            _mark_index++;
            if (_mark_index == _mark.size()) {
                _context.setState(_next_state);
            }
        } else {
            return {RET_CODE::WRONG_ADDRESS_MARK, _field_type};
        }
        return RET_CODE::CONTINUE;
    }

    ////////////////////////////////////////////
    // Read a chunk of data from the MFM stream.
    // The CTOR gets the size in bytes to read.
    ////////////////////////////////////////////
    void READ_DATA::enter() {
        LOG(LOG_DEBUG, "READ_DATA::enter() size:%d", _size);
        _byte_counter = 0;
    }
    ret_t READ_DATA::pulse(FLOPPY::PULSE p) {
        LOG(LOG_DEBUG, "READ_DATA::pulse(%d)", p);
        // We only decode the pulses here, no
        // checking for too many pulses
        return _context.decode_pulse(p);
    }
    ret_t READ_DATA::byte(uint8_t b) {
        LOG(LOG_DEBUG, "READ_DATA::byte(0x%x)", b);
        _context.write_byte(b);
        // Check for end of data transfer
        if (++_byte_counter == _size) {
            _context.setState(_next_state);
        }
        return RET_CODE::CONTINUE;
    }

}
