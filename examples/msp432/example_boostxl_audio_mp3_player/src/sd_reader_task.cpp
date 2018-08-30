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

#include "sd_reader_task.h"

sd_reader_task::sd_reader_task() :
    task("SD reader", 500),
    _req_buff(nullptr),
    _req_btr(0),
    _req_br(0),
    _eof(false),
    _force_eof(false),
    _execute(false)
{ }

void sd_reader_task::start(FatFs * fs, FatFs::FILE * file) {
    _fs   = fs;
    _file = file;
    _eof  = false;
    _force_eof = false;
    _execute   = false;
    task::start();
}

FatFs::FRESULT sd_reader_task::read_data(uint8_t* buff, uint16_t btr, uint16_t* br) {
    // Copy request parameters
    _req_buff = buff;
    _req_btr  = btr;
    _req_br   = br;
    // Trigger task execution
    _execute_mutex.lock();
    _execute = true;
    _execute_mutex.unlock();
    _execute_cv.notify_one();
    // Wait for execution to complete
    _caller_cv.wait(_caller_mutex, [this]() {return !_execute;});
    // Return the result of the execution
    return _req_result;
}

void sd_reader_task::run() {
    do {
        // Wait for a new request
        _execute_cv.wait(_execute_mutex, [this]() {return _execute;});
        // Read in the requested bytes
        _req_result = _fs->read(_file, _req_buff, _req_btr, _req_br);
        _eof = f_eof (_file);
        // Notify end of execution
        _execute = false;
        _caller_cv.notify_one();
    } while (!_eof && !_force_eof);
}
