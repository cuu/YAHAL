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
// so only some kind of PCM output is necessary.
//
// The main task will loop over all *.mp3 files and play
// them. During reset, button S1 can be used to select
// the partition on the SD card (see comment below!).
// Button S2 can be used to skip to the next song.
//
// For every new song, the SD reader and MP3 decoder
// tasks are started again.
//
#ifndef _MAIN_TASK_H_
#define _MAIN_TASK_H_

#include "task.h"
#include "audio_output.h"
#include "mp3_decoder_task.h"
#include "stream_reader_task.h"

class main_task : public task
{
public:
    main_task() : task("Main", 6000) { }

    void run() override {

        // tasks objects
        audio_output       audio_output;
        stream_reader_task stream_reader(audio_output);
        mp3_decoder_task   decoder(stream_reader, audio_output);

        // start the tasks
        stream_reader.start();
        audio_output.setRate(49000);
        audio_output.start();
        decoder.start();

        while(1) {
            sleep(1000);
        }
    }

};

#endif // _MAIN_TASK_H_



//        audio_output.start();
//        sleep(6000);
//
//
//        stream_reader.connectToWlan("TG WLAN EG", "7209142041838311");
//        sleep(2000);
//        stream_reader.connectToSrv ("icecast.vrtcdn.be", 80, "/klara-mid.mp3");
//        sleep(2000);
//
//        while(1) {
//            red.gpioWrite  ( LOW );
//            green.gpioWrite( LOW );
//            blue.gpioWrite ( LOW );
//
//            if (threeQuarters.gpioRead()) {
//                blue.gpioWrite( HIGH );
//            } else
//                if (twoQuarters.gpioRead()) {
//                    green.gpioWrite( HIGH );
//                } else
//                    if (oneQuarter.gpioRead()) {
//                        red.gpioWrite( HIGH );
//                    }
//
//            sleep(100);
//        }


// https://dg-wdr-https-dus-dtag-cdn.sslcast.addradio.de/wdr/wdr2/rheinland/mp3/128/stream.mp3
// https://dg-wdr-https-fra-dtag-cdn.sslcast.addradio.de/wdr/wdr5/live/mp3/128/stream.mp3

// /wdr/wdr2/rheinland/mp3/128/stream.mp3
// /wdr/wdr3/live/mp3/128/stream.mp3
// /wdr/wdr5/live/mp3/128/stream.mp3
// http://icecast.vrtcdn.be/klara-high.mp3   http://icecast.vrtcdn.be/klara-high.mp3

//        gpio_msp432_pin oneQuarter(PORT_PIN(9,7));
//        gpio_msp432_pin twoQuarters(PORT_PIN(7,6));
//        gpio_msp432_pin threeQuarters(PORT_PIN(7,7));
//
//        gpio_msp432_pin red(PORT_PIN(2,0));
//        gpio_msp432_pin green(PORT_PIN(2,1));
//        gpio_msp432_pin blue(PORT_PIN(2,2));
//        red.gpioMode(GPIO::OUTPUT);
//        green.gpioMode(GPIO::OUTPUT);
//        blue.gpioMode(GPIO::OUTPUT);
