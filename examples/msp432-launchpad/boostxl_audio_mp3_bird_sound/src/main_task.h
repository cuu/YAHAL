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
///////////////////////////////////
// MP3 player for MSP432 Launchpad
///////////////////////////////////
//
// This program will play a short MP3 files, which
// is located in the Flash memory of the MSP432.
// The MP3 contains some bird chirping.

#ifndef _MAIN_TASK_H_
#define _MAIN_TASK_H_

#include "audio_output.h"
#include "decoder_task.h"

#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "sd_spi_drv.h"
#include "task.h"

#include <cmath>

class main_task : public task
{
public:
    main_task() : task("Main", 6000) {
    }

    void run() override {

        audio_output audio_output;
        decoder_task decoder(audio_output);
        audio_output.enable_output(true);
        audio_output.setRate(44000);
        audio_output.start();

        // Start decoder tasks to play the MP3
        decoder.start();

        // Wait until file has been played
        while(true) {
            sleep(200);
        }
    }
};

#endif // _MAIN_TASK_H_
