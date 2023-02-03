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
// MP3 player for MSP432 launchpad and boostxl-audio //
///////////////////////////////////////////////////////
//
// This program will read MP3 files from a SD card, and
// play them on the MPS432 launchpad with a boostxl audio
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

#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "sd_spi_drv.h"

#include "task.h"
#include "sd_reader_task.h"
#include "audio_output.h"
#include "mp3_decoder_task.h"
#include "ff.h"

// SD card interface configuration
//////////////////////////////////
// Connect this pin to the SD-card
// CS line:
#define CS_PIN  PORT_PIN(10,0)

// Here are the other 3 pins you have to
// connect to the SD-card PCB, depending
// on the used SPI port:
//
//                CLK    MISO    MOSI
// -------------+------+-------+-------
// EUSCI_A0_SPI   P1.1   P1.2    P1.3
// EUSCI_A1_SPI   P2.1   P2.2    P2.3
// EUSCI_A2_SPI   P3.1   P3.2    P3.3
// EUSCI_A3_SPI   P9.5   P9.6    P9.7
// EUSCI_B0_SPI   P1.5   P1.7    P1.6
// EUSCI_B1_SPI   P6.3   P6.5    P6.4
// EUSCI_B2_SPI   P3.5   P3.7    P3.6
// EUSCI_B3_SPI   P10.1  P10.3   P10.2
#define SPI_IF  EUSCI_B3_SPI

// Button configuration
///////////////////////
#define NEXT_BUTTON  PORT_PIN(1,4)
#define PART_BUTTON  PORT_PIN(1,1)

class main_task : public task
{
public:
    main_task() : task("Main", 6000),
      _cs (CS_PIN),
      _spi(SPI_IF, _cs),
      _sd (_spi),
      _next(NEXT_BUTTON),
      _part(PART_BUTTON),
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

        // Mount the SD card.
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
