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
#ifndef FLOPPY_ERRORS_CODES_H
#define FLOPPY_ERRORS_CODES_H

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
        SECTOR_NOT_FOUND    = -202
    };

    // Convert an error code to a C-string
    const char * code_to_str(RET_CODE c);

    struct ret_t {
        ret_t(RET_CODE c, FIELD f = FIELD::NONE) : code(c), field(f) {}
        ret_t() : ret_t(RET_CODE::SUCCESS) {};
        RET_CODE code;
        FIELD    field;
        bool operator == (RET_CODE r) { return code == r; }
        bool operator != (RET_CODE r) { return !(*this == r); }

        const char * to_str() {
            static char buffer[100];
            if (field == FIELD::NONE) {
                return code_to_str(code);
            } else {
                sprintf(buffer, "%s (%s)", code_to_str(code), field_to_str(field));
                return buffer;
            }
        }
    };

}

#endif // FLOPPY_ERRORS_CODES_H
