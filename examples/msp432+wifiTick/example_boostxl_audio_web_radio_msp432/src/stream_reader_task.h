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

#ifndef _STREAM_READER_TASK_H_
#define _STREAM_READER_TASK_H_

#include <cstdint>
#include "task.h"
#include "lock_base_msp432.h"
#include "mutex.h"
#include "condition_variable.h"
#include "gpio_msp432.h"
#include "soft_i2c_master.h"
#include "spi_msp432.h"

class stream_reader_task : public task
{
public:
    stream_reader_task();

    void connectToWlan(const char *ssid, const char *passwd);
    void connectToSrv (const char *host, int port, const char *path);

    // Read some data from the file
    int read_data(uint8_t* buff, uint16_t btr, uint16_t* br);
    void run() override;

    // EOF handling
    inline bool eof() { return false; }

private:

    // I2C objects
    gpio_msp432_pin _sda;
    gpio_msp432_pin _scl;
    soft_i2c_master _i2c;
    //gpio_msp432_pin _reset;

    gpio_msp432_pin _esp_spi_cs;
    spi_msp432      _esp_spi;

    gpio_msp432_pin _oneQuarter;
    gpio_msp432_pin _twoQuarters;
    gpio_msp432_pin _threeQuarters;

    uint32_t        _ctrl7_backup;

    uint8_t *       _req_buff;
    uint16_t        _req_btr;
    uint16_t *      _req_br;
    int             _req_result;

    volatile bool                         _execute;
    mutex<lock_base_msp432>               _execute_mutex;
    condition_variable<lock_base_msp432>  _execute_cv;

    mutex<lock_base_msp432>               _caller_mutex;
    condition_variable<lock_base_msp432>  _caller_cv;
};

#endif // _STREAM_READER_TASK_H_
