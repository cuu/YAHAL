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
///////////////////////////////////////////////////////
// MP3 player for RP2040 launchpad and boostxl-audio //
///////////////////////////////////////////////////////
//
// This program will read MP3 files from a SD card, and
// play them on the RP2040 launchpad with a boostxl audio
// boosterpack. The MP3 decoder is implemented in software,
// so only some kind of PCM output is necessary, which is
// provided by the audio booster pack.
//
// The main task will loop over all *.mp3 files and play
// them. During reset, button S1 can be used to select
// the partition on the SD card (see comment below!).
// Button S2 can be used to skip to the next song.
//
// For every new song, the SD reader and MP3 decoder
// tasks are started again.
//
// Make sure you connect the SD-card PCB to the correct
// SPI interface (see pin assignment below), and provide
// some MP3 files without too high quality (128kbps
// will work fine!)

#ifndef _MAIN_TASK_H_
#define _MAIN_TASK_H_

#include "gpio_rp2040.h"
#include "spi_rp2040.h"
#include "sd_spi_drv.h"
#include "dac8311_rp2040_drv.h"
#include "task.h"
#include "sd_reader_task.h"
#include "mp3_decoder_task.h"
#include "ff.h"
#include <cassert>

// SPI interface for SD card
#define SD_MISO_PIN  8
#define SD_MOSI_PIN 11
#define SD_SCLK_PIN 10
#define SD_CS_PIN    3
#define SD_SPI1      1

// SPI interface for DA converter
#define DA_MOSI_PIN  7
#define DA_SCLK_PIN 22
#define DA_SYNC_PIN 15
#define DA_EN_PIN    5

#define LED_PIN    13

// Button configuration
///////////////////////
#define PART_BUTTON  16
#define NEXT_BUTTON  17

class main_task : public task
{
public:
    main_task() : task("Main", 6000),
      _cs (SD_CS_PIN),
      _spi(SD_SPI1, SD_MISO_PIN, SD_MOSI_PIN, SD_SCLK_PIN, _cs ),
      _sd (_spi),
      _next(NEXT_BUTTON),
      _part(PART_BUTTON),
      _fs (_sd)
    {
        _next.gpioMode(GPIO::INPUT | GPIO::PULLUP);
        _part.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    }

    void run() override {

        dac8311_rp2040_drv  pcm_drv(DA_MOSI_PIN, DA_SCLK_PIN, DA_SYNC_PIN, DA_EN_PIN);
        sd_reader_task      sd_reader;
        mp3_decoder_task    decoder(pcm_drv, sd_reader);

        // Mount the SD card.
        // If button S1 is not pressed during reset, auto-partition mode is
        // used. If button S1 is pressed, partition 2 on the SD card is used.
        FatFs::FRESULT res = _fs.mount(_part.gpioRead() == LOW ? 2 : 0);

        // Find first MP3 file
        assert(res == FatFs::FR_OK);
        res = _fs.findfirst(&_dir, &_finfo, "", "*.mp3");

        // Loop over all MP3 files
        while(res == FatFs::FR_OK && _finfo.fname[0]) {
            // Open the MP3 file
            res = _fs.open (&_file, _finfo.fname, FA_OPEN_EXISTING | FA_READ);
            assert(res == FatFs::FR_OK);

            // Start the SD reader and decoder tasks
            // to play the song :)
            sd_reader.start(&_fs, &_file);
            decoder.start();

            // Wait until file has been played. Check
            // for NEXT-button to skip to next file
            while(sd_reader.isAlive() || decoder.isAlive()) {
                if (_next.gpioRead() == LOW) {
                    // Stop playing the current title
                    sd_reader.force_eof();
                }
                sleep_ms(200);
            }
            // Wait until button is released, so we only
            // skip _one_ song...
            while(_next.gpioRead() == LOW) sleep_ms(100);

            // Close the MP3 file and find next one
            _fs.close(&_file);
            res = _fs.findnext(&_dir, &_finfo);
        }
        // Unmount the SD card
        _fs.umount();
    }

private:
    gpio_rp2040_pin _cs;    // CS Line of SD card SPI interface
    spi_rp2040      _spi;   // SPI interface used for the SD card reader
    sd_spi_drv      _sd;    // SD card low level driver

    gpio_rp2040_pin _next;  // Next button
    gpio_rp2040_pin _part;  // Partition button

    FatFs           _fs;
    FatFs::DIR      _dir;
    FatFs::FILEINFO _finfo;
    FatFs::FILE     _file;  // MP3 file on SD
};

#endif // _MAIN_TASK_H_
