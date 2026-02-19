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

#include "Memory.h"

uint16_t Memory::inc(uint16_t address) {
    uint16_t tmp = coreMemory[address];
    tmp += 1;
    tmp &= 07777;
    coreMemory[address] = tmp;
    return tmp;
}

