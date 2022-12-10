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
#include "gpio_rp2040.h"
#include "posix_io.h"
#include "sd_spi_drv.h"
#include "spi_rp2040.h"
#include "uart_rp2040.h"
#include "yahal_String.h"
#include "yahal_assert.h"

#include <cstdio>
#include <cassert>
#include <cstring>

// Hardware configuration.
#define MISO_PIN  8
#define MOSI_PIN 11
#define SCLK_PIN 10
#define CS_PIN    3
#define SPI1      1

int main(void)
{
    // Set up the red LED as an indicator
    /////////////////////////////////////
    gpio_rp2040_pin led(29);
    led.gpioMode(GPIO::OUTPUT);

    // Set up UART and enable stdin/stdout
    // using printf/scanf
    //////////////////////////////////////
    uart_rp2040 uart; // default is backchannel UART!
    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Set up the driver stack for the SD card
    //////////////////////////////////////////
    gpio_rp2040_pin cs ( CS_PIN );     // CS Line of SPI interface
    spi_rp2040      spi( SPI1, MISO_PIN, MOSI_PIN, SCLK_PIN, cs );
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
    uint32_t z;
    fs.getfree(&z);
    printf("Free blocks: %ld\n", z);

    // Now there are two options to access the CD card:
    // ------------------------------------------------
    // OPTION 1: Use the native FatFs interface
    //           (see also http://elm-chan.org/fsw/ff/00index_e.html)
    // OPTION 2: Use the C standard Posix-interface for
    //           file I/O (fopen, fclose, fread, fwrite, ...)
    // Here we use option 2
    /////////////////////////////////////////////////////////////////

    // Switch on LED so we see that SD card is written
    led = 1;
    // Open file for reading and writing
    FILE * f = fopen("test.dat", "w+");
    yahal_assert(f != NULL);
    // Write numbers 0..99 to file
    for (int i=0; i < 10000; ++i) {
        fprintf(f, "%d\n", i);
    }
    // Switch off LED
    led = 0;

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
