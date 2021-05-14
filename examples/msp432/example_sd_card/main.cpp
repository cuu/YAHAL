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
// This program demonstrates the use of a SD card
// as a file storage. The SD card has to be formatted
// with a FAT-filesystem.

#include "ff.h"
#include "gpio_msp432.h"
#include "posix_io.h"
#include "sd_spi_drv.h"
#include "spi_msp432.h"
#include "uart_msp432.h"
#include "yahal_String.h"
#include "yahal_assert.h"

#include <cstdio>
#include <cassert>
#include <cstring>

// Hardware configuration.
#define CS_PIN  PORT_PIN(10,0)
#define SPI_IF  EUSCI_B3_SPI

int main(void)
{
    // Set up the red LED as an indicator
    /////////////////////////////////////
    gpio_msp432_pin led(PORT_PIN(1, 0));
    led.gpioMode(GPIO::OUTPUT);

    // Set up UART and enable stdin/stdout
    // using printf/scanf
    //////////////////////////////////////
    uart_msp432 uart; // default is backchannel UART!
    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Set up the driver stack for the SD card
    //////////////////////////////////////////
    gpio_msp432_pin cs ( CS_PIN );     // CS Line of SPI interface
    spi_msp432      spi( SPI_IF, cs ); // SPI interface connected to SD card
    sd_spi_drv      sd ( spi );        // SD card low level driver
    FatFs           fs ( sd );         // FatFs driver
    // Register FatFs driver for Posix-style I/O
    // (fopen, fclose, fprintf, ...)
    posix_io::inst.register_fileio( fs );

    // Mount the SD card. Using this command,
    // the SD-card is opened by the FatFs driver
    ////////////////////////////////////////////
    yahal_assert(fs.mount() == FatFs::FR_OK);
    // Print out number of 512 Byte blocks on SD card
    printf("Block count: %ld\n", sd.getBlockCount());

    // Now there are two options to access the CD card:
    // ------------------------------------------------
    // OPTION 1: Use the native FatFs interface
    //           (see also http://elm-chan.org/fsw/ff/00index_e.html)
    // OPTION 2: Use the C standard Posix-interface for
    //           file I/O (fopen, fclose, fread, fwrite, ...)
    // Here we use option 2
    /////////////////////////////////////////////////////////////////

    // Switch on LED so we see that SD card is written
    led.gpioWrite(1);
    // Open file for reading and writing
    FILE * f = fopen("test.dat", "w+");
    yahal_assert(f != NULL);
    // Write numbers 0..99 to file
    for (int i=0; i < 100; ++i) {
        fprintf(f, "%d\n", i);
    }
    // Switch off LED
    led.gpioWrite(0);

    // Go back to beginning of file
    fseek(f, 0, SEEK_SET);

    char buf[200], *s;
    do {
        // Read a line up to CR/LF
        s = fgets(buf, 200, f);
        // Print line on stdout
        printf("%s", buf);
    } while(s);

    // Finally close file
    fclose(f);

    // Unmount the SD card
    yahal_assert(fs.umount() == FatFs::FR_OK);

    return 0;
}
