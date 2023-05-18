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

        stream_reader.connectToWlan("TG WLAN", "Wanja&Mikesch2007");

        // KLARA
        const char * server = "icecast-servers.vrtcdn.be";

        const char * stream = "/klara-mid.mp3";
//        const char * stream = "/klaracontinuo-mid.mp3";
//        const char * stream = "/radio1-mid.mp3";
//        const char * stream = "/ra2ant-mid.mp3";
//        const char * stream = "/ra2lim-mid.mp3";
//        const char * stream = "/mnm_urb-mid.mp3";
//        const char * stream = "/mnm_hits-mid.mp3";
//        const char * stream = "/mnm_90s00s-mid.mp3";
//        const char * stream = "/mnm_urb-mid.mp3";
//        const char * stream = "/ketnetradio-mid.mp3";

        // WDR
//        const char * server = "f121.rndfnk.com";

//        const char * stream = "/ard/wdr/wdr2/aachenundregion/mp3/128/stream.mp3?cid=01FBS09GH8H34FYWE8CX7TCZP1&sid=2PxeelnwAFfnsOCSLRf5nBVzDUG&token=4xpNtDrfVdasHjoCv-mxCrX_oV5JeHc0C70qykl_nt0&tvf=VuNapXtHYBdmMTIxLnJuZGZuay5jb20";

        stream_reader.connectToSrv (server, 80, stream);
        audio_output.start();
        mp3_decoder_task decoder(stream_reader, audio_output);
        decoder.start();

        while(1) {
            sleep(1000);
        }
    }

};

#endif // _MAIN_TASK_H_

