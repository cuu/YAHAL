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
//  This is a I2C master driver implemented in SW.
//  The I2C protocol is simulated by 2 GPIO line.

#ifndef _SOFT_I2C_MASTER_H_
#define _SOFT_I2C_MASTER_H_

#include <i2c_interface.h>
#include <gpio_interface.h>

class soft_i2c_master: public i2c_interface
{
public:

    soft_i2c_master(gpio_pin & sda, gpio_pin & scl, void (*delay)(uint32_t us),
                    bool pullup = false);
    virtual ~soft_i2c_master();

    int16_t i2cRead(uint16_t addr, uint8_t *rxbuf, uint8_t len,
                    bool sendStop = true) override;

    int16_t i2cWrite(uint16_t addr, uint8_t *txbuf, uint8_t len,
                     bool sendStop = true) override;

    void setSpeed(uint32_t);

    void init();

    // No copy, no assignment
    soft_i2c_master              (const soft_i2c_master &) = delete;
    soft_i2c_master & operator = (const soft_i2c_master &) = delete;

private:

    uint8_t read_byte(bool nack);
    bool write_byte(uint8_t byte);
    bool read_bit();
    bool write_bit(bool bit);
    bool send_start();
    void send_stop();
    bool check_bus_idle();

    bool _init;

    gpio_pin & _sda;
    gpio_pin & _scl;
    void     (*_delay)(uint32_t us);
    bool       _pullup;
    uint32_t   _us;
};

#endif // _SOFT_I2C_MASTER_H_
