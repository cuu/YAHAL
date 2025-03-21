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
#include <memory.h>
#include <cassert>

#define LED_PIN    13

#define MP3_FRAME_SIZE 2881

mp3_decoder_task::mp3_decoder_task(pcm_audio_interface & pcm_if, sd_reader_task & sd) :
    task("MP3 decoder", 8200),
    _pcm_if(pcm_if), _sd_reader(sd), _led(LED_PIN), _pcm_rate(0)
{
    _led.gpioMode( GPIO::OUTPUT );
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
    // Cast user defined data. Here we get a pointer
    // to the decoder task!
    mp3_decoder_task * _this = (mp3_decoder_task *)data;
    sd_reader_task  &   sd   = _this->_sd_reader;

    // The following code is inspired by this article:
    // https://stackoverflow.com/questions/39803572/
    int keep; // Number of bytes to keep from the previous buffer.
    int len;  // Length of the new buffer.
    int eof;  // Whether this is the last buffer that we can provide.

    // Figure out how much data we need to move from the end of
    // the previous buffer into the start of the new buffer.
    if (stream->error != MAD_ERROR_BUFLEN) {
        // All data has been consumed, or this is the first call.
        keep = 0;
    } else if (stream->next_frame != nullptr) {
        // The previous buffer was consumed partially.
        // Move the unconsumed portion into the new buffer.
        keep = stream->bufend - stream->next_frame;
    } else if ((stream->bufend - stream->buffer) < MP3_BUF_SIZE) {
        // No data has been consumed at all, but our read buffer
        // isn't full yet, so let's just read more data first.
        keep = stream->bufend - stream->buffer;
    } else {
        // No data has been consumed at all, and our read buffer is already full.
        // Shift the buffer to make room for more data, in such a way that any
        // possible frame position in the file is completely in the buffer at least
        // once.
        keep = MP3_BUF_SIZE - MP3_FRAME_SIZE;
    }

    // Shift the end of the previous buffer to the start of the
    // new buffer if we want to keep any bytes.
    if (keep) {
        memmove(_this->_mp3_buf, stream->bufend - keep, keep);
    }

    // Append new data to the buffer.
    uint16_t br;
    FatFs::FRESULT res = sd.read_data(_this->_mp3_buf + keep, MP3_BUF_SIZE - keep, &br);
    _this->_led.gpioToggle();

    if (res) {
        // Read error.
        assert( false );
        return MAD_FLOW_STOP;
    } else if (sd.eof()) {
        // End of file. Append MAD_BUFFER_GUARD zero bytes to make
        // sure that the last frame is properly decoded.
        if (keep + MAD_BUFFER_GUARD <= MP3_BUF_SIZE) {
            // Append all guard bytes and stop decoding after this buffer.
            memset(_this->_mp3_buf + keep, 0, MAD_BUFFER_GUARD);
            len = keep + MAD_BUFFER_GUARD;
            eof = 1;
        } else {
            // The guard bytes don't all fit in our buffer, so we need to continue
            // decoding and write all fo the guard bytes in the next call to input().
            memset(_this->_mp3_buf + keep, 0, MP3_BUF_SIZE - keep);
            len = MP3_BUF_SIZE;
            eof = 0;
        }
    } else {
        // New buffer length is amount of bytes that we kept from the
        // previous buffer plus the bytes that we read just now.
        len = keep + br;
        eof = 0;
    }

    // Pass the new buffer information to libmad
    mad_stream_buffer(stream, _this->_mp3_buf, len);
    return eof ? MAD_FLOW_STOP : MAD_FLOW_CONTINUE;
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
        task::sleep_ms(5);
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
