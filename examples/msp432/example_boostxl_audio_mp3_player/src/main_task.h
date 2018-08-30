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
      _btn(PORT_PIN(1,4)),
      _fs (_sd)
    {
        _btn.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    }

    void run() override {

        audio_output     audio_output;
        sd_reader_task   sd_reader;
        mp3_decoder_task decoder(sd_reader, audio_output);
        audio_output.start();

        // Mount SD card (auto partition)
        FatFs::FRESULT res = _fs.mount();

        // Find first MP3 file
        yahal_assert(res == FatFs::FRESULT::FR_OK);
        res = _fs.findfirst(&_dir, &_finfo, "", "*.mp3");

        // Loop over all MP3 files
        while(res == FatFs::FR_OK && _finfo.fname[0]) {
            // Open the MP3 file
            res = _fs.open (&_file, _finfo.fname, FA_OPEN_EXISTING | FA_READ);
            yahal_assert(res == FatFs::FRESULT::FR_OK);

            // Start the SD reader and decoder tasks
            sd_reader.start(&_fs, &_file);
            decoder.start(); //DEFAULT_PRIORITY, true);

            // Wait until file has been played. Check
            // for NEXT-button to skip to next file
            while(sd_reader.isAlive() || decoder.isAlive()) {
                if (_btn.gpioRead() == LOW) {
                    // Stop playing the current title
                    sd_reader.force_eof();
                }
                sleep(200);
            }
            // Wait until button is released
            while(_btn.gpioRead() == LOW) sleep(100);

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

    gpio_msp432_pin _btn;   // Next button

    FatFs           _fs;
    FatFs::DIR      _dir;
    FatFs::FILEINFO _finfo;
    FatFs::FILE     _file;  // MP3 file on SD
};

#endif // _MAIN_TASK_H_
