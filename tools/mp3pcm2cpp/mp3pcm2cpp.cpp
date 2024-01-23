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
// Small program to decode a MP3 file to its PCM data,
// and store this data into a C/C++ struct or a raw
// binary file.
//
#define MP3_BUF_SIZE   4096
#define MP3_FRAME_SIZE 2881

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <getopt.h>
#include <libgen.h>
#include <memory.h>

#include "mad.h"

using namespace std;

enum out_mode {
    mono, stereo, left_ch, right_ch
};

uint8_t mp3_buf[MP3_BUF_SIZE];
FILE *mp3_file;
ofstream ofs_cpp;
ofstream ofs_h;
uint32_t byte_counter = 0;
out_mode mode = stereo;  // Default is stereo
bool raw  = false;   // Default is C++ struct output
int pass = 1;
uint32_t pcm_size = 0;

void usage() {
    cout << "Usage: mp3pcm2cpp [-r] [-m <mode>] [-o outfile] file.mp3"   << endl;
    cout << endl;
    cout << "-r          : Generate raw binary data"                     << endl;
    cout << "-m <mode>   : mode is: mono, stereo (default), left, right" << endl;
    cout << "-o outfile  : The output filename. Default is file.cpp"     << endl;
    cout << "file.mp3    : A valid MP3 file" << endl;
    exit(1);
}

///////////////////////////
// libmad input callback //
///////////////////////////
enum mad_flow decoder_input(void *data, struct mad_stream *stream) {
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
        memmove(mp3_buf, stream->bufend - keep, keep);
    }

    // Append new data to the buffer.
    uint16_t br = fread(mp3_buf + keep, 1, MP3_BUF_SIZE - keep, mp3_file);

    if (ferror(mp3_file)) {
        // Read error.
        assert( false );
        return MAD_FLOW_STOP;
    } else if (feof(mp3_file)) {
        // End of file. Append MAD_BUFFER_GUARD zero bytes to make
        // sure that the last frame is properly decoded.
        if (keep + MAD_BUFFER_GUARD <= MP3_BUF_SIZE) {
            // Append all guard bytes and stop decoding after this buffer.
            memset(mp3_buf + keep, 0, MAD_BUFFER_GUARD);
            len = keep + MAD_BUFFER_GUARD;
            eof = 1;
        } else {
            // The guard bytes don't all fit in our buffer, so we need to continue
            // decoding and write all fo the guard bytes in the next call to input().
            memset(mp3_buf + keep, 0, MP3_BUF_SIZE - keep);
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
    mad_stream_buffer(stream, mp3_buf, len);
    return eof ? MAD_FLOW_STOP : MAD_FLOW_CONTINUE;
}

////////////////////////////
// libmad header callback //
////////////////////////////
enum mad_flow decoder_header(void *data, struct mad_header const * header) {
    static bool samplerate_written = false;
    if ((pass == 1) && !samplerate_written) {
        ofs_cpp << "// MP3 data type : ";
        ofs_h   << "// MP3 data type : ";
        switch(header->mode) {
            case MAD_MODE_SINGLE_CHANNEL:
                ofs_cpp << "SINGLE CHANNEL";
                ofs_h   << "SINGLE CHANNEL";
                break;
            case MAD_MODE_DUAL_CHANNEL:
                ofs_cpp << "DUAL CHANNEL";
                ofs_h   << "DUAL CHANNEL";
                break;
            case MAD_MODE_JOINT_STEREO:
                ofs_cpp << "JOINT STEREO";
                ofs_h   << "JOINT STEREO";
                break;
            case MAD_MODE_STEREO:
                ofs_cpp << "STEREO";
                ofs_h   << "STEREO";
                break;
        }
        ofs_cpp << endl;
        ofs_h   << endl;
        ofs_cpp << "// MP3 samplerate: " << header->samplerate << endl;
        ofs_h   << "// MP3 samplerate: " << header->samplerate << endl;
        samplerate_written = true;
    }
    return MAD_FLOW_CONTINUE;
}

/////////////////////////////////
// scale a pcm value to a int16_t
/////////////////////////////////
int16_t scale(mad_fixed_t sample)
{
    // libmad does a good job calculating the correct
    // values in the range betwenn -MAD_F_ONE and MAD_F_ONE.
    // Therefore rounding and clipping is normally not
    // necessary!

    // round
    sample += (1L << (MAD_F_FRACBITS - 16));
    // clip
    if (sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;

    // Convert to a standard 16 bit PCM value
    // (signed) in the range of -32768...32767
    sample >>= (MAD_F_FRACBITS + 1 - 16);
    return sample;
}

/////////////////////////////////////
// write a single pcm value to a file
/////////////////////////////////////
void write_pcm_value(int16_t pcm) {
    byte_counter += 2;
    if (pass != 2) return;
    if (raw) {
        ofs_cpp.write((char*) &pcm, sizeof(int16_t));
    } else {
        ofs_cpp << "0x" << hex << setw(4) << setfill('0') << pcm;
        if (byte_counter != pcm_size) ofs_cpp << ", ";
        if ((byte_counter) % 16 == 0) ofs_cpp << endl;
    }
}

////////////////////////////
// libmad output callback //
////////////////////////////
enum mad_flow decoder_output(void *data, mad_header const *header, mad_pcm *pcm)
{
    // Copy PCM samples to PCM fifo
    mad_fixed_t const * left_channel  = pcm->samples[MAD_PCM_CHANNEL_STEREO_LEFT];
    mad_fixed_t const * right_channel = pcm->samples[MAD_PCM_CHANNEL_STEREO_RIGHT];

    int16_t pcm_value;
    for (int i=0; i < pcm->length; ++i) {
        switch(mode) {
            case mono:
                pcm_value = scale((left_channel[i] + right_channel[i])/2);
                write_pcm_value(pcm_value);
                break;
            case stereo:
                write_pcm_value(scale(left_channel[i]));
                write_pcm_value(scale(right_channel[i]));
                break;
            case left_ch:
                write_pcm_value(scale(left_channel[i]));
                break;
            case right_ch:
                write_pcm_value(scale(right_channel[i]));
                break;
        }
    }
    return MAD_FLOW_CONTINUE;
}

///////////////////////////
// libmad error callback //
///////////////////////////
enum mad_flow decoder_error(void *data,mad_stream *stream, mad_frame *frame)
{
    (void)(data);
    (void)(stream);
    (void)(frame);
    // return MAD_FLOW_BREAK to stop decoding
    return MAD_FLOW_CONTINUE;
}


int main(int argc, char *argv[]) {
    // Process the command line arguments
    string      infile;
    string      outfile_cpp;
    string      outfile_h;

    int opt;
    while ((opt = getopt(argc, argv, ":rm:o:")) != -1) {
        switch (opt) {
            case 'r': {
                raw = true;
                break;
            }
            case 'm': {
                string m = optarg;
                if (m == "mono") {
                    mode = mono;
                } else if (m == "stereo") {
                    mode = stereo;
                } else if (m == "left") {
                    mode = left_ch;
                } else if (m == "right") {
                    mode = right_ch;
                } else {
                    cerr << "Wrong mode " << m << ". Exiting ..." << endl;
                    exit(1);
                }
                break;
            }
            case 'o': {
                outfile_cpp = optarg;
                break;
            }
            case ':': {
                cerr << "Option needs a value!" << endl;
                usage();
                break;
            }
            case '?': {
                cerr << "Unknown option '" << (char)optopt << "'" << endl;
                usage();
                break;
            }
        }
    }
    if (optind == (argc-1)) {
        infile = argv[optind];
    } else {
        cerr << "No or too many filenames given!" << endl;
        usage();
    }

    // Process the file name
    size_t dot = infile.find_last_of('.');
    string name_we;
    if (dot != string::npos) {
        name_we = infile.substr(0, dot);
    } else {
        name_we = infile;
    }
    if (outfile_cpp.size()==0) {
        // Set the default output name
        outfile_cpp = name_we;
        if (raw) outfile_cpp += ".bin";
        else     outfile_cpp += ".cpp";
    }
    outfile_h = name_we + ".h";

    string base = basename( (char*)name_we.c_str() );
    // Dashes are not valid in variable names, so replace them
    std::replace(base.begin(), base.end(), '-', '_');

    mp3_file = fopen(infile.c_str(), "r");
    ofs_cpp.open(outfile_cpp, raw ? std::ios_base::binary : std::ios_base::out);
    ofs_h.open(outfile_h);

    mad_decoder decoder;

    /////////
    // Pass 1
    /////////
    mad_decoder_init(&decoder,      // the decoder object
                     nullptr,       // parameter for callback functions
                     decoder_input, // input callback
                     decoder_header,// header callback
                     nullptr,       // filter callback
                     decoder_output,// output callback
                     decoder_error, // error  callback
                     nullptr);      // message callback

    mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);
    mad_decoder_finish(&decoder);
    pcm_size = byte_counter;

    if (!raw) {
        ofs_cpp << "//" << endl;
        ofs_cpp << "// This file was generated by mp3pcm2cpp, a small" << endl;
        ofs_cpp << "// program to convert a MP3 file into a raw binary" << endl;
        ofs_cpp << "// data file or a C/C++ struct of PCM value (int16_t)." << endl;
        ofs_cpp << "//" << endl;
        ofs_cpp << "//  Source file was: " << infile << endl;
        ofs_cpp << "//" << endl;
        ofs_cpp << "#include <cstdint>" << endl;
        ofs_cpp << endl;
        ofs_cpp << "extern const int16_t " << base << "[" << pcm_size/2 << "] = {"
                << endl;

        ofs_h << "//" << endl;
        ofs_h << "// This file was generated by mp3pcm2cpp, a small" << endl;
        ofs_h << "// program to convert a MP3 file into a raw binary" << endl;
        ofs_h << "// data file or a C/C++ struct of PCM value (int16_t)." << endl;
        ofs_h << "//" << endl;
        ofs_h << "//  Source file was: " << infile << endl;
        ofs_h << "//" << endl;
        ofs_h << "#include <cstdint>" << endl;
        ofs_h << endl;
        ofs_h << "extern const int16_t " << base << "[" << pcm_size/2 << "];"
              << endl;
    }

    /////////
    // Pass 2
    /////////
    pass = 2;
    fseek(mp3_file, 0, SEEK_SET);
    byte_counter = 0;

    mad_decoder_init(&decoder,      // the decoder object
                     nullptr,       // parameter for callback functions
                     decoder_input, // input callback
                     decoder_header,// header callback
                     nullptr,       // filter callback
                     decoder_output,// output callback
                     decoder_error, // error  callback
                     nullptr);      // message callback

    mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);
    mad_decoder_finish(&decoder);

    if (!raw) ofs_cpp << "};" << endl;

    fclose(mp3_file);
    ofs_cpp.close();
    ofs_h.close();

    return 0;
}
