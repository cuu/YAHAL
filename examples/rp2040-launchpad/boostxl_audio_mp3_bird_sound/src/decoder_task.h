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
#include "dac8311_rp2040_drv.h"
#include "gpio_rp2040.h"
#include "task.h"
#include "mad.h"

#define MP3_BUF_SIZE   4096
#define MP3_FRAME_SIZE 2881

class decoder_task : public task
{
public:
    decoder_task();

    void run() override;

private:
    static enum mad_flow input (void *data, struct mad_stream *stream);
    static enum mad_flow header(void *data, struct mad_header const *);
    static enum mad_flow output(void *data, mad_header const *header, mad_pcm *pcm);
    static enum mad_flow error (void *data, mad_stream *stream, mad_frame *frame);
    static int16_t       scale (mad_fixed_t sample);

    dac8311_rp2040_drv _dac8311;
    mad_decoder        _decoder;
    gpio_rp2040_pin    _led;
    uint8_t            _mp3_buf[MP3_BUF_SIZE];
};

#endif // _MP3_DECODER_TASK_H_
