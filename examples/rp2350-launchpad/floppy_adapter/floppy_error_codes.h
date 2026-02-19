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
#ifndef FLOPPY_ERROR_CODES_H
#define FLOPPY_ERROR_CODES_H

#include <cstdint>
#include <cstdio>

namespace FLOPPY {

    // All field types within a track
    enum class FIELD : int {
        NONE  = 0, GAP1  = 1, GAP2  = 2, GAP3 = 3, GAP4A =  4, GAP4B =  5,
        SYNC1 = 6, SYNC2 = 7, SYNC3 = 8, IAM  = 9, IDAM  = 10, DAM   = 11,
        DATA_ID = 12, DATA_SECTOR = 13
    };

    // Convert a FIELD type to a C-string
    const char * field_to_str(FIELD f);

    enum class RET_CODE : int {
        SUCCESS             = 1,
        CONTINUE            = 0,
        TOO_MANY_PULSES     = -1,
        WRONG_ADDRESS_MARK  = -2,
        NO_DISK             = -200,
        UNSUPPORTED_FORMAT  = -201,
        SECTOR_NOT_FOUND    = -202,
        DATA_CRC_ERROR      = -203,
        IDAM_CRC_ERROR      = -204
    };

    // Convert an error code to a C-string
    const char * code_to_str(RET_CODE c);

    struct ret_t {
        ret_t(RET_CODE c) : code(c), field(FIELD::NONE), data_ptr(nullptr) {}
        ret_t(RET_CODE c, FIELD f) : code(c), field(f), data_ptr(nullptr) {}
        ret_t(RET_CODE c, uint8_t *p) : code(c), field(FIELD::NONE), data_ptr(p) {}
        ret_t() : ret_t(RET_CODE::SUCCESS, FIELD::NONE) {};

        RET_CODE    code;
        FIELD       field;
        uint8_t *   data_ptr;

        bool operator == (RET_CODE r) const { return code == r; }
        bool operator != (RET_CODE r) const { return !(*this == r); }

        const char * to_str() const {
            static char buffer[100];
            if (field != FIELD::NONE) {
                sprintf(buffer, "%s (%s)", code_to_str(code), field_to_str(field));
                return buffer;
            } else if (data_ptr != nullptr) {
                sprintf(buffer, "%s (%p)", code_to_str(code), data_ptr);
                return code_to_str(code);
            } else {
                return code_to_str(code);
            }
        }
    };

}

#endif // FLOPPY_ERROR_CODES_H
