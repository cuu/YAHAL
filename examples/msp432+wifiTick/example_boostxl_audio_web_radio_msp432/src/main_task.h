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

        stream_reader.start();

        // Wait for reset of ESP8266
        sleep(2000);

        stream_reader.connectToWlan("TG WLAN EG", "7209142041838311");

        // KLARA
        stream_reader.connectToSrv ("icecast.vrtcdn.be", 80, "/klara-mid.mp3");
//        stream_reader.connectToSrv ("dg-wdr-http-fra-dtag-cdn.cast.addradio.de", 80, "/wdr/wdr2/rheinland/mp3/128/stream.mp3");
//        stream_reader.connectToSrv ("dg-wdr-http-dus-dtag-cdn.cast.addradio.de", 80, "/wdr/wdr4/live/mp3/128/stream.mp3");
//        stream_reader.connectToSrv ("s9.viastreaming.net", 9620, "/;stream/1");
//        stream_reader.connectToSrv ("s1.distortionradio.com", 80, "/aggression-64");

        audio_output.start();

        mp3_decoder_task decoder(stream_reader, audio_output);
        decoder.start();

        while(1) {
            sleep(1000);
        }
    }

};

#endif // _MAIN_TASK_H_

