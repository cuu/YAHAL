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

#include "soft_i2c_slave.h"

soft_i2c_slave::soft_i2c_slave(gpio_pin & sda, gpio_pin & scl,
                               bool    (*r)(uint16_t index, uint8_t data, void *),
                               uint8_t (*t)(uint16_t index, void *),
                               void    (*s)(void *),
                               void     * user_ptr,
                               bool       pullup)
    : _sda(sda), _scl(scl), _init(false), _pullup(pullup),
      _receive(r), _transmit(t), _stop(s),_user_ptr(user_ptr),
      _i2c_address(0),
      _state     (nullptr),
      _idle      (*this), _read_addr (*this), _write_ack (*this),
      _read_data (*this), _write_data(*this), _read_ack  (*this)
{
    // Set start state
    setState(&_idle);
}

soft_i2c_slave::~soft_i2c_slave() {
    // Check if we need to de-configure
    if (!_init) return;
    _sda.gpioMode(GPIO::INPUT);
    _scl.gpioMode(GPIO::INPUT);
    _sda.gpioDetachIrq();
    _scl.gpioDetachIrq();
}

void soft_i2c_slave::init() {
    uint16_t mode = GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH;
    if (_pullup) {
        mode |= GPIO::PULLUP;
    }
    _sda.gpioMode(mode);
    _scl.gpioMode(mode);

    /////////////////////////////////////////////
    // The event-generating interrupt handlers //
    /////////////////////////////////////////////

    _sda.gpioAttachIrq(GPIO::FALLING | GPIO::RISING, [this](void *) {
        // SDA interrupt handler
        ////////////////////////
        if (!_scl.gpioRead()) return;
        _sda.gpioRead() ? _state->stop() : _state->start();
    });

    _scl.gpioAttachIrq(GPIO::FALLING | GPIO::RISING, [this](void *) {
        // SCL interrupt handler
        ////////////////////////
        if (_scl.gpioRead()) {
            _sda.gpioRead() ? _state->high() : _state->low();
        } else {
            _state->scl_falling();
        }
    });
    _init = true;
}

