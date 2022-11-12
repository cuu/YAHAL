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
// This program uses the backchannel UART
// to read and write data to/from a terminal.
// Backchannel uart means, that the serial
// data, which is produced in the MSP432,
// is forwarded to the debug module on the
// launchpad. The debug module has a USB
// connection to the PC, and generates a
// serial device like /dev/ttyACM0 on the PC,
// which then can be used with a terminal
// program.
// This program also shows some VT100-compatible
// escape sequences to change the color of the
// text output. This only works if the terminal
// understands these escape sequences.
//

#include "uart_rp2040.h"
#include "posix_io.h"
#include <cassert>

int main(void) {
    uart_rp2040 uart; // default is backchannel UART!
    posix_io::inst.register_stderr( uart );

    uart.puts("UART example for interrupt handling\n\r");
    uart.puts("Please type some characters on the keyboard -\n\r");
    uart.puts("they will be echoed by the interrupt handler!\n\r");
    uart.puts("But DON'T press 'Q' ... :)\n\n\r");

    uart.uartAttachIrq([&](char c){
        uart.puts("Received char: ");
        assert(c != 'Q');
        uart.putc(c);
        uart.puts("\r\n");
    });

    while (1) __WFE();
}

