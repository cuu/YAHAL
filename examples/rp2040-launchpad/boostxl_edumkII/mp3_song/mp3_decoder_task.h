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
#ifndef _MP3_DECODER_TASK_H_
#define _MP3_DECODER_TASK_H_

#include <cstdint>
#include "pcm_audio_interface.h"
#include "gpio_rp2040.h"
#include "task.h"
#include "mad.h"

#define MP3_BUF_SIZE   4096

class mp3_decoder_task : public task
{
public:
    mp3_decoder_task(pcm_audio_interface & pcm_if);

    void run() override;

private:
    static enum mad_flow input (void *data, struct mad_stream *stream);
    static enum mad_flow header(void *data, struct mad_header const *);
    static enum mad_flow output(void *data, mad_header const *header, mad_pcm *pcm);
    static enum mad_flow error (void *data, mad_stream *stream, mad_frame *frame);
    static int16_t       scale (mad_fixed_t sample);

    pcm_audio_interface &   _pcm_if;
    mad_decoder             _decoder;
    uint8_t                 _mp3_buf[MP3_BUF_SIZE];
    uint32_t                _pcm_rate;
};

#endif // _MP3_DECODER_TASK_H_
