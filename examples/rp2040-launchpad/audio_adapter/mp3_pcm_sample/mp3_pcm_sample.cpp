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
///////////////////////////////////////////
// Play a single MP3 file from flash memory
///////////////////////////////////////////
//
// main() only prepares the infrastructure, namely:
//  - redirects stdout/stderr
//  - starts the main task
//  - starts the task monitor
//  - starts the scheduler
// The program logic is contained in the main_task
// and not here!

#include "pcm_pwm_rp2040_drv.h"
#include "gen/surprise.h"

int main(void)
{
    // Use the PCM-PWM driver for RP2040. This driver
    // will output the left/right audio on GPIO9 and
    // GPIO11, which fits to the small 3.5mm audio
    // adapter, when connected correctly.
    pcm_pwm_rp2040_drv pcm_if(9, 11);

    // The PCM rate can be seen as a comment in the
    // generated files (here surprise.h/.cpp), and 
    // has to be set manually.
    pcm_if.setPcmRate(32000);

    // A single PCM value with left/right data
    pcm_value_t pcm;
    
    // Loop over all PCM samples. Note that sizeof() report
    // the size of the PCM array in BYTES!
    for (uint32_t i=0; i < sizeof(surprise)/sizeof(int16_t); ++i) {
        // Wait for a free entry in the FIFO
        while (!pcm_if.pcmFifoAvailablePut()) ;
        // Load the next PCM value ...
        pcm.left  = (int16_t)surprise[i];
        pcm.right = (int16_t)surprise[i];
        // ... and put it to the FIFO
        pcm_if.pcmFifoPut(pcm);
    }
}
