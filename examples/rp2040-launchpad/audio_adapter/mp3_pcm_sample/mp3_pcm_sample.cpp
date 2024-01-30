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
/////////////////////////////////////////////////
// Play a single PCM dataset on the audio adapter
/////////////////////////////////////////////////

#include "pcm_pwm_rp2040_drv.h"
// Some samples
#include "gen/hat1.h"
#include "gen/hat2.h"
#include "gen/kick.h"
#include "gen/snare.h"

int main(void)
{
    // Use the PCM-PWM driver for RP2040. This driver
    // will output the left/right audio on GPIO9 and
    // GPIO11, which fits to the small 3.5mm audio
    // adapter, when connected correctly.
    pcm_pwm_rp2040_drv pcm_if(9, 11);

    // The PCM rate can be seen as a comment in the
    // generated files (here e.g. hat1.h), and 
    // has to be set manually:
    pcm_if.setPcmRate(44100);

    // A single PCM value with left/right data
    pcm_value_t pcm;
    int left, right;
    int count;
    // Loop over all PCM samples for 1 seconds. Because
    // the MP3 and PCM data is stereo, we have 2*44100
    // PCM values per second.
    for (uint32_t i=0; i < 88200; i += 2) {
        // Reset values
        count = 0;
        left  = 0;
        right = 0;
        // Add PCM samples to left/right
        if (i < sizeof(hat1)/sizeof(int16_t)) {
            left  += (int16_t)hat1[i];
            right += (int16_t)hat1[i+1];
            count++;
        }
        if (i < sizeof(hat2)/sizeof(int16_t)) {
            left  += (int16_t)hat2[i];
            right += (int16_t)hat2[i+1];
            count++;
        }
        if (i < sizeof(kick)/sizeof(int16_t)) {
            left  += (int16_t)kick[i];
            right += (int16_t)kick[i+1];
            count++;
        }
        if (i < sizeof(snare)/sizeof(int16_t)) {
            left  += (int16_t)snare[i];
            right += (int16_t)snare[i+1];
            count++;
        }
        // Scale the output so we do not get
        // overflows for int16_t
        left  /= count;
        right /= count;
        // Wait for a free entry in the FIFO
        while (!pcm_if.pcmFifoAvailablePut()) ;
        // Prepare the next PCM value ...
        pcm.left  = (int16_t)left;
        pcm.right = (int16_t)right;
        // ... and put it into the FIFO
        pcm_if.pcmFifoPut(pcm);
    }
}
