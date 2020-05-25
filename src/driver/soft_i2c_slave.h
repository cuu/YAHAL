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
//  The I2C protocol is decoded with 2 GPIO line,
//  which need support for edge interrupts. The
//  interrupt handlers generate 5 events (start, stop,
//  high, low, SCL falling), which in turn are processed
//  by a state machine. The user code has to provide 3 callback methods,
//  which are used within the state machine:
//
//      bool receive(uint8_t index, uint8_t data, void *)
//
//  This method is called when the state machine has
//  received a complete byte. The index is a number
//  being incremented within one Start sequence, starting
//  from 0.
//
//     uint8_t transmit(uint8_t index, void *)
//
//  This method is called when the state machine needs
//  a new byte to send.
//
//     void stop(void *)
//
//  This method is called when a stop-condition is detected.
//  It can be used to recognize restart conditions.

#ifndef _SOFT_I2C_SLAVE_H_
#define _SOFT_I2C_SLAVE_H_

#include <gpio_interface.h>
#include <cstdint>
#include "soft_i2c_slave_states.h"

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
    soft_i2c_slave(gpio_pin & sda, gpio_pin & scl,
                   bool    (*receive) (uint16_t index, uint8_t data, void *),
                   uint8_t (*transmit)(uint16_t index, void *),
                   void    (*stop)(void *),
                   void     *user_ptr,
                   bool     pullup = false);
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
    bool     (*_receive) (uint16_t index, uint8_t data, void *);
    uint8_t  (*_transmit)(uint16_t index, void *);
    void     (*_stop)    (void *);
    void *     _user_ptr;

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

    // The interrupt handlers generating the events
    static void sda_handler(gpio_pin_t, void *);
    static void scl_handler(gpio_pin_t, void *);
};

#endif // _SOFT_I2C_SLAVE_H_
