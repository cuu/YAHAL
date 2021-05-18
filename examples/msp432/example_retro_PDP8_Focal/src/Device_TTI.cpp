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

#include "Device_TTI.h"
#include "CPU.h"

unsigned short Device_TTI::getDeviceNumber() {
    return 003;
}

char Device_TTI::toUpper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a'-'A');
    else
        return c;
}

void Device_TTI::cycle() {
    if (!FLAG && _uart.available()) {
        FLAG = true;
        c = toUpper(_uart.getc());
        // Use CTRL-D as RUBOUT
        if (c==4) c = 0x7f;
    }
}

void Device_TTI::clearFlag() {
    FLAG = false;
}

bool Device_TTI::intRequest() {
    return FLAG;
}

void Device_TTI::processPulse(unsigned int pulse, CPU & cpu) {

    switch (pulse) {
    // KCF (Keyboard Clear Flags)
    /////////////////////////////
    case 00: {
        FLAG=false;
        break;
    }
    // KSF (Keyboard Skip if Flag)
    //////////////////////////////
    case 01: {
        if (FLAG) cpu.skip();
        break;
    }
    // KCC (Keyboard Clear and read character)
    //////////////////////////////////////////
    case 02: {
        cpu.setAC(0);
        FLAG = false;
        break;
    }
    // KRB (Keyboard Read and begin next read)
    //////////////////////////////////////////
    case 06: {
        cpu.setAC(0);
        FLAG = false;
    }
    // KRS (Keyboard Read Static)
    /////////////////////////////
    // no break
    case 04: {
        cpu.setAC( cpu.getAC() | c);
        break;
    }
    default:
        yahal_assert(0);
        break;
    }

}

