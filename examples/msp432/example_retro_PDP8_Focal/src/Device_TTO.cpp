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

#undef PC

#include "yahal_assert.h"
#include "Device_TTO.h"
#include "CPU.h"

unsigned short Device_TTO::getDeviceNumber() {
    return 004;
}

void Device_TTO::cycle() {
}

void Device_TTO::clearFlag() {
    FLAG = false;
}

bool Device_TTO::intRequest() {
    return FLAG;
}

// The Teleprinter FLAG has to stay cleared after a TCF, so
// that the Focal interpreter has a chance to produce new
// characters to output. Only in the case of a TLS/TPC, the
// FLAG will be automatically set if the Teleprinter is ready
// to receive the next character. Here the FLAG is set
// immediately after a character is printed.

void Device_TTO::processPulse(unsigned int pulse, CPU & cpu) {

    switch (pulse) {
    // TFL (Teleprinter Flag set)
    /////////////////////////////
    case 0: {
        FLAG=true;
        break;
    }
    // TSF (Teleprinter Skip if Flag)
    /////////////////////////////////
    case 1: {
        if (FLAG) cpu.skip();
        break;
    }
    // TCF (Teleprinter Clear Flag)
    ///////////////////////////////
    case 2: {
        FLAG=false;
        break;
    }
    // TLS (Teleprinter Load and start)
    ///////////////////////////////////
    case 6:
        FLAG=false;
    // TPC (Teleprinter Print Character)
    ////////////////////////////////////
    //no break
    case 4: {
        char c = cpu.getAC() & 0177;
        if (c == 127) c = 7;
        if (c !=  12) _uart.putc(c);
        // Ready to receive the next character
        FLAG=true;
        break;
    }
    default:
        yahal_assert(0);
        break;
    }
}
