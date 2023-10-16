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
// I2C driver for RP2040. It support master
// and client mode. Interrupts are supported
// for client mode (RX interrupts).
//
#ifndef _I2C_RP2040_H_
#define _I2C_RP2040_H_

#include "i2c_interface.h"
#include "gpio_rp2040.h"
#include "RP2040.h"

using namespace _I2C0_;
using namespace _I2C1_;

class i2c_rp2040 : public i2c_interface {

public:

    i2c_rp2040(uint8_t     index,
               gpio_pin_t  sda_pin,
               gpio_pin_t  scl_pin,
               uint16_t    mode);

    ~i2c_rp2040();

    int16_t i2cRead (uint16_t addr, uint8_t *rxbuf,
                     uint16_t len, bool sendStop=true) override;
    int16_t i2cWrite(uint16_t addr, uint8_t *txbuf,
                     uint16_t len, bool sendStop=true) override;

    void setSpeed(uint32_t) override;

private:
    bool        _initialized;
    void        initialize();

    int         _index;
    gpio_rp2040_pin  _sda;
    gpio_rp2040_pin  _scl;

//    bool        _master;
    uint16_t    _mode;
    bool        _restart_on_next;

    I2C0_t *    _i2c;
    I2C0_t *    _i2c_set;
    I2C0_t *    _i2c_clr;
};

#endif // _I2C_RP2040_H_
