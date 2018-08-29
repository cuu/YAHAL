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

#include "msp.h"
#undef PC

#include "yahal_assert.h"
#include "Device_TTO.h"
#include "CPU.h"

unsigned short Device_TTO::getDeviceNumber() {
    return 004;
}

void Device_TTO::cycle() {
    if (!last && (UCA0IFG & UCTXIFG)) {
        last = true;
        FLAG = true;
    }
}

void Device_TTO::clearFlag() {
    FLAG = false;
}

bool Device_TTO::intRequest() {
    return FLAG;
}

void Device_TTO::processPulse(unsigned int pulse, CPU & cpu) {

    switch (pulse) {
    // TSF (Skip if teleprinter flag is 1)
    //////////////////////////////////////
    case 1: {
        if (FLAG) cpu.skip();		 // Normal operation
        break;
    }
    // TCF (Clear teleprinter flag)
    ///////////////////////////////
    case 2: {
        FLAG=false;
        break;
    }
    // TLS (Load TTO from AC, clear flag and print/punch character)
    ///////////////////////////////////////////////////////////////
    case 6:
        FLAG=false;
    case 4: { // TPC (Load TTO from AC and print/punch character)
        char c = cpu.getAC() & 0177;
        if (c==127) c = 7;
        if (c!=12)
            UCA0TXBUF = c;
        last = false;
        break;
    }
    default:
        yahal_assert(0);
        break;
    }
}
