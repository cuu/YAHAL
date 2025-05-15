//
// Created by andreas on 13.05.25.
//

#ifndef MFM_READER_STATES_H
#define MFM_READER_STATES_H

#include <cstdint>
#include <cstdio>
#include <array>
#include "MFM_reader.h"
#include "MFM_errors.h"

class MFM_reader;

namespace MFM {

    enum class PULSE : uint8_t {
        S = 0, M = 1, L = 2
    };

    class STATE {
    public:
        explicit STATE(MFM_reader &r,
                       int error_offset)
        : _context(r), _error_offset(error_offset) {}
        virtual ~STATE() = default;

        virtual void enter() {}
        virtual int  pulse(PULSE p);
        virtual int  byte(uint8_t);

    protected:
        MFM_reader & _context;
        int          _error_offset;
    };


    class READ_GAP : public STATE {
    public:
        explicit READ_GAP(MFM_reader &r,
                          int     error_offset,
                          uint8_t threshold,
                          uint16_t max_pulses,
                          STATE *next_state)
        : STATE(r, error_offset), _threshold(threshold),
          _next_state(next_state), _max_pulses(max_pulses) {}

        void enter() override;
        int  pulse(PULSE p) override;

    private:
        uint8_t _threshold;
        STATE * _next_state;

        uint8_t _tag_index{0};
        uint8_t _tag_count{0};

        const uint16_t _max_pulses;
        uint16_t _pulse_count {0};

        PULSE _tag[5] {
            PULSE::M, PULSE::M, PULSE::S, PULSE::S, PULSE::M
        };

    };

    class READ_SYNC : public STATE {
    public:
        explicit READ_SYNC(MFM_reader &r,
                           int error_offset,
                           STATE *next_state)
        : STATE(r, error_offset), _next_state(next_state) {}

        int pulse(PULSE p) override;

    private:
        STATE * _next_state;
    };

    class READ_TAG : public STATE {
    public:
        explicit READ_TAG(MFM_reader &r,
                          int error_offset,
                          const std::array<uint8_t,4> tag,
                          STATE *next_state)
        : STATE(r, error_offset), _tag(tag), _next_state(next_state) {}

        void enter() override;
        int  byte(uint8_t b) override;

    private:
        uint8_t _tag_index{0};
        const std::array<uint8_t, 4> _tag;
        STATE * _next_state;
    };

    class READ_DATA : public STATE {
    public:
        explicit READ_DATA(MFM_reader &r,
                           uint16_t size,
                           STATE *next_state)
        : STATE(r, 0), _size(size), _next_state(next_state) {}

        void enter() override;
        int  byte(uint8_t b) override;

    private:
        const uint16_t  _size;
        uint8_t         _counter {0};
        STATE *         _next_state;
    };

}

#endif // MFM_READER_STATES_H
