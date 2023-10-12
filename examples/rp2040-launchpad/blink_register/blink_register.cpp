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
// A simple blink example using the red LED on
// GPIO 13. We do not use YAHAL here, but only
// the register definitions of the RP2040!
// See file RP2040.h for details.

#include "RP2040.h"
using namespace _PADS_BANK0_;
using namespace _IO_BANK0_;
using namespace _SIO_;

#define GPIO13_MASK (1 << 13)

int main(void)
{
    // Set 2ma drive current
    PADS_BANK0.GPIO[13].DRIVE = GPIO_DRIVE__4mA;
    // Switch GPIO mode to SIO
    IO_BANK0.GPIO13_CTRL.FUNCSEL = GPIO_CTRL_FUNCSEL__sio;
    // Enable GPIO 13 as output
    SIO.GPIO_OE_SET = GPIO13_MASK;

    // Endless loop
    while (1) {
        // Set GPIO 13 to 1 (on, true, 3.3V, active ...)
        SIO.GPIO_OUT_SET = GPIO13_MASK;
        for (int i=0; i < 10000000; ++i) ; // delay
        // Set GPIO 13 to 0 (off, false, 0V, not active ...)
        SIO.GPIO_OUT_CLR = GPIO13_MASK;
        for (int i=0; i < 10000000; ++i) ; // delay
    }
    return 0;
}
