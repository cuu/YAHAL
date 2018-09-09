#ifndef _SOFT_I2C_SLAVE_H_
#define _SOFT_I2C_SLAVE_H_

#include <gpio_interface.h>
#include <cstdint>

// The names of the states are 'seen' from slave perspective:
// READ  means the master is sending and the slave is reading data
// WRITE means the master is reading and the slave is writing data
namespace I2C {
    enum I2C_event { start, stop, high, low, scl_falling };
    enum I2C_state { IDLE, READ, WRITE_ACK, WRITE, READ_ACK, WAIT };
}

class soft_i2c_slave {
public:
    // The receive() handler passes received data to the user code.
    // The index ranges from 0..N and counts every received/transmitted
    // byte (without the slave addresses) within one start/stop sequence.
    // So for a I2C sequence with repeated starts, the index increases
    // further. It is reset after a stop event.
    // The transmit() handler asks for new user data to be sent. The
    // wantmore() callback is called after the master has sent a ACK,
    // signaling it wants more data during a master read operation.
    // This method can be used to prepare new data, which in turn will
    // be sent via transmit().
    soft_i2c_slave(gpio_pin & sda, gpio_pin & scl,
                   bool    (*receive) (uint8_t index, uint8_t data, void *),
                   uint8_t (*transmit)(uint8_t index, void *),
                   void    (*wantmore)(void *),
                   void     *ptr);
    virtual ~soft_i2c_slave();

    // Getter/Setter for slaves I2C address it listens to
    inline uint8_t getI2cAddress() {
        return _i2c_address;
    }
    inline void setI2cAddress(uint8_t a) {
        _i2c_address = a;
    }

private:
    // The interrupt handler generating the events
    static void sda_handler(gpio_pin_t, void *);
    static void scl_handler(gpio_pin_t, void *);

    // I2C slave state machine
    void handler(I2C::I2C_event e);

    inline void setState(I2C::I2C_state s) {
        _state = s;
        _enter = true;
    }

    // HW attributes
    gpio_pin & _sda;
    gpio_pin & _scl;

    I2C::I2C_state _state;  // current state

    uint8_t   _i2c_address; // the I2C address the slave listens to
    uint8_t   _data;        // data received/to transmit
    int       _bit_mask;    // bit mask for next cycle, 0 if byte complete
    int       _byte_index;  // data byte index 0...N within one start/stop sequence
    bool      _enter;       // true if state is entered the first time
    bool      _send;        // R/W bit, master R -> slave 'send'
    bool      _ack;         // acknowledge state
    bool      _read_addr;   // true if next byte to read is the I2C address

    // callback methods
    bool    (*_receive) (uint8_t index, uint8_t data, void *);
    uint8_t (*_transmit)(uint8_t index, void *);
    void    (*_wantmore)(void *);

    void *    _user_ptr;
};

#endif // _SOFT_I2C_SLAVE_H_
