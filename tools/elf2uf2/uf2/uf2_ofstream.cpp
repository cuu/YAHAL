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

#include "uf2_ofstream.h"

std::ostream & operator << (std::ostream & os, const family_id_t & fam) {
        switch (fam) {
            case family_id_t::RP2040:
                os << "RP2040";
                break;
            case family_id_t::RP2XXX_ABSOLUTE:
                os << "RP2xxx_ABSOLUTE";
                break;
            case family_id_t::RP2XXX_DATA:
                os << "RP2xxx_DATA";
                break;
            case family_id_t::RP2350_ARM_S:
                os << "RP2350_ARM_S";
                break;
            case family_id_t::RP2350_RISCV:
                os << "RP2350_RISCV";
                break;
            case family_id_t::RP2350_ARM_NS:
                os << "RP2350_NS";
                break;
            default:
                os << "????";
                break;
        }
        return os;
}
