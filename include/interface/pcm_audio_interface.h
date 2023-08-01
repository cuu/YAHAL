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
// This file defines a generic and abstract C++
// interface for a PCM audio interface.

#ifndef _PCM_AUDIO_INTERFACE_H_
#define _PCM_AUDIO_INTERFACE_H_

#include <cstdint>
#include "FIFO.h"

// PCM samples are signed 16 bit integers
typedef struct {
    int16_t   left;
    int16_t   right;
} pcm_value_t;

class pcm_audio_interface {
public:
    pcm_audio_interface(uint16_t fifo_size)
    : pcmFIFO(fifo_size) { }

    // Set the PCM outout rate in Hz.
    // Default is 44.1 kHz
    void setPcmRate(uint32_t Hz = 44100);

    // Check how many values can be written to
    // the PCM FIFO.
    inline int pcmFifoAvailablePut() {
        return pcmFIFO.available_put();
    }

    // Write a PCM sample to the PCM FIFO.
    // It has to be checked before if the
    // FIFO has enough space (see method above).
    inline bool pcmFifoPut(pcm_value_t & v) {
        return pcmFIFO.put(v);
    }

    // Read a PCM sample from the PCM FIFO.
    // Method will return false if no data is
    // available. Otherwise, v will contain
    // the PCM sample.
    inline bool pcmFifoGet(pcm_value_t & v) {
        return pcmFIFO.get(v);
    }

protected:
    // PCM FIFO buffer to store the PCM samples
    FIFO<pcm_value_t> pcmFIFO;

    ~pcm_audio_interface() = default;
};

#endif // _PCM_AUDIO_INTERFACE_H_
