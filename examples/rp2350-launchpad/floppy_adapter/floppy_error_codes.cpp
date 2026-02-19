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

#include <cassert>
#include "floppy_error_codes.h"

namespace FLOPPY {

    const char *field_to_str(FIELD f) {
        assert((int) f < 140);
        static const char *field_names[14] = {
                "NONE", "GAP1", "GAP2", "GAP3","GAP4a","GAP4b",
                "SYNC1","SYNC2","SYNC3","IAM", "IDAM", "DAM",
                "DATA_ID","DATA_SECTOR"};
        return field_names[(int) f];
    }

    const char * code_to_str(RET_CODE c) {
        switch(c) {
            case RET_CODE::SUCCESS: {
                return "SUCCESS"; break;
            }
            case RET_CODE::CONTINUE: {
                return "CONTINUE"; break;
            }
            case RET_CODE::TOO_MANY_PULSES: {
                return "TOO_MANY_PULSES"; break;
            }
            case RET_CODE::WRONG_ADDRESS_MARK: {
                return "WRONG_ADDRESS_MARK"; break;
            }
            case RET_CODE::NO_DISK: {
                return "NO_DISK"; break;
            }
            case RET_CODE::UNSUPPORTED_FORMAT: {
                return "UNSUPPORTED_FORMAT"; break;
            }
            case RET_CODE::SECTOR_NOT_FOUND: {
                return "SECTOR_NOT_FOUND"; break;
            }
            case RET_CODE::DATA_CRC_ERROR: {
                return "DATA_CRC_ERROR"; break;
            }
            case RET_CODE::IDAM_CRC_ERROR: {
                return "IDAM_CRC_ERROR"; break;
            }
            default:
                return "UNKNOWN_ERROR"; break;
        }
    }
}

