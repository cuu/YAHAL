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
// This small program demonstrates an interrupt
// handler attached to an uart object.
// All typed characters are simply echoed. If
// a magic key is pressed ('Q'), an assertion
// fails and the program ends. The main program
// loop lets the CPU sleep until the next event
// (interrupt).
//
#include "uart_rp2350.h"
#include "posix_io.h"
#include <cassert>

int main(void) {
    uart_rp2350 uart; // default is backchannel UART!
    posix_io::inst.register_stderr( uart );

    uart.puts("UART example for interrupt handling\n\r");
    uart.puts("Please type some characters on the keyboard -\n\r");
    uart.puts("they will be echoed by the interrupt handler!\n\r");
    uart.puts("But DON'T press 'Q' ... :)\n\n\r");

    uart.uartAttachIrq([&](char c){
        uart.puts("Received char: ");
        assert((c != 'Q') && "I told you NOT to press 'Q' !!!!");
        uart.putc(c);
        uart.puts("\r\n");
    });

    while (true) __WFE();
}

