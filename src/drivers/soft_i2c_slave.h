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
//  This is a I2C slave driver  implemented in SW.
//  The I2C protocol is decoded with 2 GPIO lines,
//  which need support for both edge interrupts. The
//  interrupt handlers generate 5 events (start, stop,
//  high, low, SCL falling), which in turn are processed
//  by a state machine. The user code has to provide 3
//  callback methods, which are used within the state
//  machine:
//
//      bool receive(uint8_t index, uint8_t data)
//
//  This method is called when the state machine has
//  received a complete byte. The index is a number
//  being incremented within one Start sequence, starting
//  from 0.
//
//     uint8_t transmit(uint8_t index)
//
//  This method is called when the state machine needs
//  a new byte to send.
//
//     void stop()
//
//  This method is called when a stop-condition is detected.
//  It can be used to recognize restart conditions.

#ifndef _SOFT_I2C_SLAVE_H_
#define _SOFT_I2C_SLAVE_H_

#include <gpio_interface.h>
#include "soft_i2c_slave_states.h"

#include <cstdint>
#include <functional>

class soft_i2c_slave {

    // The I2C states are our friends
    friend class I2C::STATE;
    friend class I2C::IDLE;
    friend class I2C::READ_ADDR;
    friend class I2C::WRITE_ACK;
    friend class I2C::READ_DATA;
    friend class I2C::WRITE_DATA;
    friend class I2C::READ_ACK;

public:
    // The receive() handler passes received data to the user code.
    // The index ranges from 0..N and counts every received/transmitted
    // byte (without the slave addresses) after a start condition.
    // So for a I2C sequence with repeated starts, the index starts
    // with 0 after every start condition. Stop conditions can be
    // detected with the stop() callback.
    // The transmit() handler asks for new user data to be sent. The
    // index is the save as for read operations (0 for the first byte
    // after the I2C address).
    soft_i2c_slave(gpio_pin & sda, gpio_pin & scl, bool pullup = false);

    void set_callbacks(std::function<bool(uint16_t index, uint8_t data)> receive,
                       std::function<uint8_t(uint16_t index)> transmit,
                       std::function<void()> stop);

    virtual ~soft_i2c_slave();

    // Getter/Setter for slaves I2C address it listens to
    inline uint8_t getI2cAddress() {
        return _i2c_address;
    }
    inline void setI2cAddress(uint8_t a) {
        if (!_init) init();
        _i2c_address = a;
    }

    // No copy, no assignment
    soft_i2c_slave              (const soft_i2c_slave &) = delete;
    soft_i2c_slave & operator = (const soft_i2c_slave &) = delete;

private:
    // HW attributes
    gpio_pin & _sda;
    gpio_pin & _scl;
    bool       _init;
    bool       _pullup;

    // callback methods
    std::function<bool   (uint16_t index, uint8_t data)>  _receive;
    std::function<uint8_t(uint16_t index)>                _transmit;
    std::function<void()> _stop;

    uint8_t    _i2c_address; // the I2C address of the slave

    // State instances
    I2C::STATE  *   _state; // current state
    I2C::IDLE       _idle;
    I2C::READ_ADDR  _read_addr;
    I2C::WRITE_ACK  _write_ack;
    I2C::READ_DATA  _read_data;
    I2C::WRITE_DATA _write_data;
    I2C::READ_ACK   _read_ack;

    // Variables for inter-State communication
    bool _ack;          // acknowledge state
    int  _byte_index;   // data byte index 0...N within one start sequence
    bool _send;         // I2C read or write

    void init();

    inline void setState(I2C::STATE * s) {
        if (_state) { _state->leave();  }
        _state = s;
        if (_state) { _state->enter(); }
    }
};

#endif // _SOFT_I2C_SLAVE_H_
