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
#include "sd_reader_task.h"
#include "audio_output.h"
#include "gpio_msp432.h"
#include "task.h"
#include "mad.h"

#define MP3_BUF_SIZE   4096
#define MP3_FRAME_SIZE 2881

class mp3_decoder_task : public task
{
public:
    mp3_decoder_task(sd_reader_task & sd, audio_output & ao);

    void run() override;

private:
    static enum mad_flow input (void *data, struct mad_stream *stream);
    static enum mad_flow header(void *, struct mad_header const *);
    static enum mad_flow output(void *data, mad_header const *header, mad_pcm *pcm);
    static enum mad_flow error (void *data, mad_stream *stream, mad_frame *frame);
    static uint16_t      scale (mad_fixed_t sample);

    sd_reader_task  & _sd_reader;
    audio_output &    _audio_output;
    mad_decoder       _decoder;
    gpio_msp432_pin   _led;
    uint8_t           _mp3_buf[MP3_BUF_SIZE];
};

#endif // _MP3_DECODER_TASK_H_
