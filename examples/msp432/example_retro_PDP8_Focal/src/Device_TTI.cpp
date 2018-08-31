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
    if (!FLAG && (UCA0IFG & UCRXIFG)) {
        FLAG = true;
        c = toUpper(UCA0RXBUF);
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
    case 01: { // KSF (Skip if keyboard flag is 1)
        if (FLAG) cpu.skip();
        break;
    }
    case 02: { // KCC (Clear AC and keyboard flag)
        cpu.setAC(0);
        // while (kbhit()) getchar();
        FLAG = false;
        break;
    }
    case 04: { // KRS (Read keyboard buffer static
        cpu.setAC( cpu.getAC() | c);
        break;
    }
    case 06: { // KRB (Clear AC and keyboard flag, read char)
        FLAG = false;
        cpu.setAC(c);
        break;
    }
    default:
        yahal_assert(0);
        break;
    }

}

