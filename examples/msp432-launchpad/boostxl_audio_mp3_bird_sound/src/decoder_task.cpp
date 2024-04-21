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

#include <memory.h>
#include "decoder_task.h"

extern const unsigned char birds[124524];
const unsigned char * bird_ptr = birds;

decoder_task::decoder_task(audio_output & ao) :
    task("MP3 decoder", 8200),
    _audio_output(ao),
    _led(PORT_PIN(1,0))
{
    _led.gpioMode( GPIO::OUTPUT );
}

void decoder_task::run() {

    mad_decoder_init(&_decoder, // the decoder object
                     this,      // parameter for callback functions
                     input,     // input callback
                     header,    // header callback
                     0,         // filter callback
                     output,    // output callback
                     error,     // error  callback
                     0);        // message callback

    mad_decoder_run(&_decoder, MAD_DECODER_MODE_SYNC);

    mad_decoder_finish(&_decoder);
}

///////////////////////////
// libmad input callback //
///////////////////////////
enum mad_flow decoder_task::input(void *data, struct mad_stream *stream) {
    (void)(data);
    // Pass the new buffer information to libmad
    mad_stream_buffer(stream, birds, sizeof(birds));
    return MAD_FLOW_CONTINUE;
}

enum mad_flow decoder_task::header(void *data, struct mad_header const * header) {
    decoder_task * _this = (decoder_task *)data;
    _this->_audio_output.setRate( header->samplerate );
    return MAD_FLOW_CONTINUE;
}

////////////////////////////
// libmad output callback //
////////////////////////////
enum mad_flow decoder_task::output(void *data, mad_header const *header, mad_pcm *pcm)
{
    (void)(header);
    decoder_task * _this = (decoder_task *)data;

    // Wait until the PCM result can be written
    while (_this->_audio_output.fifo_available_put() < pcm->length) {
        _this->sleep_ms(5);
    }
    // Copy PCM samples to PCM fifo. We only have a MONO
    // audio channel, so we calculate the mean value of
    // the left and right channel.
    mad_fixed_t const * left_ch  = pcm->samples[MAD_PCM_CHANNEL_STEREO_LEFT];
    mad_fixed_t const * right_ch = pcm->samples[MAD_PCM_CHANNEL_STEREO_RIGHT];
    for (int i=0; i < pcm->length; ++i) {
        mad_fixed_t mono = (left_ch[i] + right_ch[i]) / 2;
        _this->_audio_output.fifo_put( scale( mono ) );
    }
    return MAD_FLOW_CONTINUE;
}

///////////////////////////
// libmad error callback //
///////////////////////////
enum mad_flow decoder_task::error(void *data,mad_stream *stream, mad_frame *frame)
{
    (void)(data);
    (void)(stream);
    (void)(frame);
    // return MAD_FLOW_BREAK to stop decoding
    return MAD_FLOW_CONTINUE;
}

uint16_t decoder_task::scale(mad_fixed_t sample)
{
    // round
    sample += (1L << (MAD_F_FRACBITS - 14));
    // clip
    if (sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;
    // quantize to signed 14 bit value in
    // the range of -8192...8191
    sample >>= (MAD_F_FRACBITS + 1 - 14);
    // Our DAC expects unsigned values from
    // 0...16383, so we have to add a offset
    sample += 8192;
    return sample;
}
