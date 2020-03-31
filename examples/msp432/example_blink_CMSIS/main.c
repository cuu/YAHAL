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
// Port 1 pin 0. We use the Cortex-M Software
// Interface Standard interface (CMSIS) to access
// the hardware. This standard includes component
// and register definitions. See file msp432p401r.h
// for details.

// This is a generic include file for various types
// of msp432 processors. When you 'walk down'
// starting from this file, you find the (large)
// include file msp432p401r.h mentioned above.
#include "msp.h"

int main(void)
{
    // Switch P1.0 to gpio mode (mode 0)
    // This step is not really necessary,
    // because the gpio mode is the default.
    P1->SEL0 &= ~BIT0;  // Reset bit 0 in the SEL0 register
    P1->SEL1 &= ~BIT0;  // Reset bit 0 in the SEL1 register

    // Switch P1.0 to output mode
    P1->DIR |= BIT0;

    // Endless loop
    while (1) {
        // Set P1.0 (Port 1, BIT 0) to 1 (on, true, 3.3V, active ...)
        P1->OUT |= BIT0;
        for (int i=0; i < 100000; ++i) ; // delay
        // Set P1.0 to 0 (off, false, 0V, not active ...)
        P1->OUT &= ~BIT0;
        for (int i=0; i < 100000; ++i) ; // delay
    }
    return 0;
}
