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

#define VT100_COLOR "%c[%dm",27
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

#include <cstdio>
#include "uart_rp2040.h"
#include "posix_io.h"
#include "yahal_String.h"

int main(void)
{
	uart_rp2040 uart; // default is backchannel UART!

    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Print out a simple ASCII table
    printf(VT100_COLOR, BLACK);
    printf("ASCII Tabelle\n\n");
    for (char c=33; c < 127; ++c) {
        String dec = to_String(c);
        String hex = to_String(c, 16);
        printf("Char: %c, dec: %s, hex: %s\n", c, dec.c_str(), hex.c_str());
    }

    // Some simple input/output with printf and scanf (C API)
    char buf1[50], buf2[50];

    printf(VT100_COLOR, GREEN);
    printf("\nPlease enter first and last name: ");
    fflush( stdout );
    scanf("%50s %50s", buf1, buf2);

    printf(VT100_COLOR, RED);
    printf("\nHello %s %s. Nice to meet you!\n\n", buf1, buf2);

    return 0;
}

