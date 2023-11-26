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
#include "mp3_decoder_task.h"
#include "song.h"
#include <cstdio>

mp3_decoder_task::mp3_decoder_task(pcm_audio_interface & pcm_if) :
    task("MP3 decoder", 8500), _pcm_if(pcm_if), _pcm_rate(0) {
}

void mp3_decoder_task::run() {

    mad_decoder_init(&_decoder, // the decoder object
                     this,      // parameter for callback functions
                     input,     // input callback
                     header,    // header callback
                     nullptr,   // filter callback
                     output,    // output callback
                     error,     // error  callback
                     nullptr);  // message callback

    mad_decoder_run(&_decoder, MAD_DECODER_MODE_SYNC);
    mad_decoder_finish(&_decoder);
}

///////////////////////////
// libmad input callback //
///////////////////////////
enum mad_flow mp3_decoder_task::input(void *data, struct mad_stream *stream) {
    (void)(data);
    // Pass the new buffer information to libmad
    mad_stream_buffer(stream, song, sizeof(song));
    return MAD_FLOW_CONTINUE;
}

////////////////////////////
// libmad header callback //
////////////////////////////
enum mad_flow mp3_decoder_task::header(void *data, struct mad_header const * header) {
    mp3_decoder_task * _this = (mp3_decoder_task *)data;
    if (header->samplerate != _this->_pcm_rate) {
        _this->_pcm_rate = header->samplerate;
        _this->_pcm_if.setPcmRate( header->samplerate );
    }
    return MAD_FLOW_CONTINUE;
}

////////////////////////////
// libmad output callback //
////////////////////////////
enum mad_flow mp3_decoder_task::output(void *data, mad_header const *header, mad_pcm *pcm)
{
    (void)(header);
    mp3_decoder_task * _this = (mp3_decoder_task *)data;

    // Wait until the PCM result can be written
    while (_this->_pcm_if.pcmFifoAvailablePut() < pcm->length) {
        task::sleep(5);
    }
    // Copy PCM samples to PCM fifo
    mad_fixed_t const * left_ch  = pcm->samples[MAD_PCM_CHANNEL_STEREO_LEFT];
    mad_fixed_t const * right_ch = pcm->samples[MAD_PCM_CHANNEL_STEREO_RIGHT];
    pcm_value_t pcm_value;
    for (int i=0; i < pcm->length; ++i) {
        pcm_value.left  = scale(left_ch[i]);
        pcm_value.right = scale(right_ch[i]);
        _this->_pcm_if.pcmFifoPut(pcm_value);
    }
    return MAD_FLOW_CONTINUE;
}

///////////////////////////
// libmad error callback //
///////////////////////////
enum mad_flow mp3_decoder_task::error(void *data,mad_stream *stream, mad_frame *frame)
{
    (void)(data);
    (void)(stream);
    (void)(frame);
    // return MAD_FLOW_BREAK to stop decoding
    return MAD_FLOW_CONTINUE;
}

int16_t mp3_decoder_task::scale(mad_fixed_t sample)
{
    // libmad does a good job calculating the correct
    // values in the range betwenn -MAD_F_ONE and MAD_F_ONE.
    // Therefore rounding and clipping is normally not
    // necessary!
#if 0
    // round
    sample += (1L << (MAD_F_FRACBITS - 16));
    // clip
    if (sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;
#endif
    // Convert to a standard 16 bit PCM value
    // (signed) in the range of -32768...32767
    sample >>= (MAD_F_FRACBITS + 1 - 16);
    return sample;
}
