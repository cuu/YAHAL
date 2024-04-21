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
// This program will play an approximates sin-signal
// short MP3 files, which
// is located in the Flash memory of the MSP432.
// The MP3 contains some bird chirping.

#ifndef _MAIN_TASK_H_
#define _MAIN_TASK_H_

#include <cmath>

#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "sd_spi_drv.h"

#include "task.h"
#include "audio_output.h"
#include <cmath>

class main_task : public task
{
public:
    main_task() : task("Main", 6000) {
    }

    void run() override {
        audio_output audio_output;
        audio_output.enable_output(true);
        audio_output.setRate(10000);
        audio_output.start();

        // Fill sin table. We only have 10 samples
        // per full sin wave.
        uint16_t table[10];
        for (int i=0; i < 9; ++i) {
            table[i] = 2000.0 * sin(2 * M_PI / 10.0 * i) + 8192;
        }

        // Fill the FIFO with the sin-data
        int i = 0;
        while(true) {
            if (audio_output.fifo_available_put()) {
                audio_output.fifo_put(table[i++]);
                i %= 10;
            } else {
                task::sleep_ms(10);
            }
        }
    }
};

#endif // _MAIN_TASK_H_
