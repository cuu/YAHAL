//
// Created by andreas on 13.05.25.
//

#include "MFM_reader.h"
#include "MFM_reader_states.h"

namespace MFM {

    ////////////////////////////
    // STATE base class defaults
    ////////////////////////////
    int STATE::pulse(MFM::PULSE p) {
        return _context.decode_pulse(p);
    }
    int STATE::byte(uint8_t) {
        return MFM::WORKING;
    }

    //////////////////////////////////////////////
    // Read a MFM GAP (0x4e) until a SYNC pattern
    // starts. For performance reasons, the 0x4e
    // bytes are not decoded.
    //////////////////////////////////////////////
    void READ_GAP::enter() {
        // Reset tag variables
        _tag_index = 0;
        _tag_count = 0;
    }
    int READ_GAP::pulse(MFM::PULSE p) {
        // Check maximal pulse count
        if (++_pulse_count >= _max_pulses) {
            return _error_offset + ERROR_NOT_FOUND;
        }
        // Check the last pulse
        if (_tag_index == sizeof(_tag)) {
            _tag_count++;
            switch (p) {
                case PULSE::S: {
                    if (_tag_count >= _threshold) {
                        _context.setState(_next_state);
                    } else {
                        // We received an S but too early.
                        // So start over again...
                        _tag_index = 0;
                        _tag_count = 0;
                    }
                    break;
                }
                case PULSE::M: {
                    // Obviously there is one more 0x4e pattern
                    _tag_index = 0;
                    break;
                }
                case PULSE::L: {
                    // Pulse L should never occur here.
                    // Try to start over ...
                    _tag_index = 0;
                    _tag_count = 0;
                    break;
                }
            }
            return MFM::WORKING;
        }
        // Check the tag pulses
        if (p == _tag[_tag_index]) {
            _tag_index++;
        } else if (p == _tag[0]) {
            _tag_index = 1;
            _tag_count = 0;
        } else {
            _tag_index = 0;
            _tag_count = 0;
        }
        return MFM::WORKING;
    }

    /////////////////////////////////////////////////
    // Read in MFM SYNC bytes (0x00). The data
    // stream is not decoded into bytes, because
    // after GAP2 there might be some extra S-pulses,
    // which might disturb the following data bytes.
    /////////////////////////////////////////////////
    int READ_SYNC::pulse(PULSE p) {
        switch (p) {
            case PULSE::S:
                break;
            case PULSE::M:
                _context.setState(_next_state);
                break;
            case PULSE::L:
                return _error_offset + MFM::ERROR_SYNC;
        }
        return MFM::WORKING;
    }

    ///////////////////////////////////////////////
    // Read an MFM address mark (called tag here).
    // The bytes to read are passed as a std::array
    // to the CTOR.
    ///////////////////////////////////////////////
    void READ_TAG::enter() {
        _tag_index = 0;
        // Prepare for address mark
        _context._byte = 0;
        _context._even = true;
        _context._bit_count = 0;
    }
    int READ_TAG::byte(uint8_t b) {
        if (b == _tag[_tag_index]) {
            _tag_index++;
            if (_tag_index == _tag.size()) {
                _context.setState(_next_state);
            }
        } else {
            return _error_offset + MFM::ERROR_READ_TAG;
        }
        return MFM::WORKING;
    }

    ////////////////////////////////////////////
    // Read a chunk of data from the MFM stream.
    // The CTOR gets the size in bytes to read.
    ////////////////////////////////////////////
    void READ_DATA::enter() {
        _counter = 0;
    }
    int READ_DATA::byte(uint8_t b) {
        _context.write_byte(b);
        if (++_counter == _size) {
            _context.setState(_next_state);
        }
        return MFM::WORKING;
    }

}
