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
// GPIO 38. We do not use YAHAL here, but only
// the register definitions of the RP2350!
// See file RP2350.h for details.
//
#include "board.h"
#include "RP2350.h"

using namespace _PADS_BANK0_;
using namespace _IO_BANK0_;
using namespace _SIO_;

#define GPIO38_MASK   (1 << (LED_RED_GPIO-32))

int main()
{
    // Set 4ma drive current
    PADS_BANK0.GPIO[LED_RED_GPIO].DRIVE = GPIO_DRIVE__4mA;
    // Switch off PAD isolation (RP2040 didn't have that)
    PADS_BANK0.GPIO[LED_RED_GPIO].ISO = 0;
    // Switch GPIO mode to SIO
    IO_BANK0.GPIO38_CTRL.FUNCSEL = GPIO_CTRL_FUNCSEL__sio;
    // Enable GPIO 38 as output
    SIO.GPIO_HI_OE_SET = GPIO38_MASK;

    // Endless loop
    while (1) {
        // Set GPIO 38 to 1 (on, true, 3.3V, active ...)
        SIO.GPIO_HI_OUT_SET = GPIO38_MASK;
        for (int i=0; i < 10000000; ++i) ; // delay
        // Set GPIO 38 to 0 (off, false, 0V, not active ...)
        SIO.GPIO_HI_OUT_CLR = GPIO38_MASK;
        for (int i=0; i < 10000000; ++i) ; // delay
    }
}
