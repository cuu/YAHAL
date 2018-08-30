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

#ifndef _MAIN_TASK_H_
#define _MAIN_TASK_H_

#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "sd_spi_drv.h"

#include "task.h"
#include "sd_reader_task.h"
#include "audio_output.h"
#include "mp3_decoder_task.h"
#include "ff.h"

class main_task : public task
{
public:
    main_task()
    : task("Main", 6000),
      _cs (PORT_PIN(10,0)),
      _spi(EUSCI_B3_SPI, _cs),
      _sd (_spi),
      _next(PORT_PIN(1,4)),
      _part(PORT_PIN(1,1)),
      _fs (_sd)
    {
        _next.gpioMode(GPIO::INPUT | GPIO::PULLUP);
        _part.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    }

    void run() override {

        audio_output     audio_output;
        sd_reader_task   sd_reader;
        mp3_decoder_task decoder(sd_reader, audio_output);
        audio_output.start();

        // Mount SD card.
        // If button S1 is not pressed during reset, auto-partition mode is
        // used. If button S1 is pressed, partition 2 on the SD card is used.
        FatFs::FRESULT res = _fs.mount(_part.gpioRead() == LOW ? 2 : 0);

        // Find first MP3 file
        yahal_assert(res == FatFs::FR_OK);
        res = _fs.findfirst(&_dir, &_finfo, "", "*.mp3");

        // Loop over all MP3 files
        while(res == FatFs::FR_OK && _finfo.fname[0]) {
            // Open the MP3 file
            res = _fs.open (&_file, _finfo.fname, FA_OPEN_EXISTING | FA_READ);
            yahal_assert(res == FatFs::FR_OK);

            // Start the SD reader and decoder tasks
            sd_reader.start(&_fs, &_file);
            decoder.start(); //DEFAULT_PRIORITY, true);

            // Wait until file has been played. Check
            // for NEXT-button to skip to next file
            while(sd_reader.isAlive() || decoder.isAlive()) {
                if (_next.gpioRead() == LOW) {
                    // Stop playing the current title
                    sd_reader.force_eof();
                }
                sleep(200);
            }
            // Wait until button is released, so we only
            // skip _one_ song...
            while(_next.gpioRead() == LOW) sleep(100);

            // Close the MP3 file and find next one
            _fs.close(&_file);
            res = _fs.findnext(&_dir, &_finfo);
        }
        // Unmount the SD card
        _fs.umount();
    }

private:
    gpio_msp432_pin _cs;    // CS Line of audio SPI
    spi_msp432      _spi;   // SPI interface used for the SD card reader
    sd_spi_drv      _sd;    // SD card low level driver

    gpio_msp432_pin _next;  // Next button
    gpio_msp432_pin _part;  // Partition button

    FatFs           _fs;
    FatFs::DIR      _dir;
    FatFs::FILEINFO _finfo;
    FatFs::FILE     _file;  // MP3 file on SD
};

#endif // _MAIN_TASK_H_
