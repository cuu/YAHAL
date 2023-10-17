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

#include "task.h"
#include "decoder_task.h"

class main_task : public task
{
public:
    main_task() : task("Main", 6000) {
    }

    void run() override {

        decoder_task decoder;
        // Start decoder tasks to play the MP3
        decoder.start();

        // Wait until file has been played
        while(true) {
            sleep(200);
        }
    }
};

#endif // _MAIN_TASK_H_
