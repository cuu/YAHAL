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

#include <mp3_decoder_task.h>
#include <memory.h>

mp3_decoder_task::mp3_decoder_task(stream_reader_task & sr, audio_output & ao) :
    task("MP3 decoder", 8200),
    _stream_reader(sr),
    _audio_output(ao),
    _led(PORT_PIN(8,0))
{
    _led.gpioMode ( GPIO::OUTPUT );
}

void mp3_decoder_task::run() {

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
enum mad_flow mp3_decoder_task::input(void *data, struct mad_stream *stream) {
    // Cast user defined data. Here we get a pointer
    // to the decoder task!
    mp3_decoder_task * _this = (mp3_decoder_task *)data;
    stream_reader_task & sr  = _this->_stream_reader;

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
    int res = sr.read_data(_this->_mp3_buf + keep, MP3_BUF_SIZE - keep, &br);
    _this->_led.gpioToggle();

    if (res) {
        // Read error.
        yahal_assert( false );
        return MAD_FLOW_STOP;
    } else if (sr.eof()) {
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

enum mad_flow mp3_decoder_task::header(void *data, struct mad_header const * header) {
    mp3_decoder_task * _this = (mp3_decoder_task *)data;
    _this->_audio_output.setRate( header->samplerate );
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
    while (_this->_audio_output.fifo_available_put() < pcm->length) {
        _this->sleep(5);
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
enum mad_flow mp3_decoder_task::error(void *data,mad_stream *stream, mad_frame *frame)
{
    (void)(data);
    (void)(stream);
    (void)(frame);
    // return MAD_FLOW_BREAK to stop decoding
    return MAD_FLOW_CONTINUE;
}

uint16_t mp3_decoder_task::scale(mad_fixed_t sample)
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
