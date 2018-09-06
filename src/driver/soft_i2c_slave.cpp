
#include "soft_i2c_slave.h"

soft_i2c_slave::soft_i2c_slave(gpio_pin & sda, gpio_pin & scl,
                               bool    (*r)(uint8_t index, uint8_t data),
                               uint8_t (*t)(uint8_t index),
                               void    (*m)())
: _sda(sda), _scl(scl), _state(I2C::IDLE),
  _i2c_address(0), _data(0),  _bit_mask(0), _byte_index(0),
  _enter(false), _send(false), _ack(false), _read_addr(false),
  _receive(r), _transmit(t), _wantmore(m)
{
    _sda.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH);
    _scl.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH);
    _sda.gpioAttachIrq(GPIO::FALLING | GPIO::RISING, sda_handler, this);
    _scl.gpioAttachIrq(GPIO::FALLING | GPIO::RISING, scl_handler, this);
}

soft_i2c_slave::~soft_i2c_slave() {
    _sda.gpioMode(GPIO::INPUT);
    _scl.gpioMode(GPIO::INPUT);
    _sda.gpioDetachIrq();
    _scl.gpioDetachIrq();
}

// event-generating interrupt handlers
void soft_i2c_slave::sda_handler(gpio_pin_t, void * arg) {
    soft_i2c_slave * _this = (soft_i2c_slave *)arg;
    if (!_this->_scl.gpioRead()) return;
    _this->handler(_this->_sda.gpioRead() ? I2C::stop : I2C::start);
}

void soft_i2c_slave::scl_handler(gpio_pin_t, void * arg) {
    soft_i2c_slave * _this = (soft_i2c_slave *)arg;
    if (_this->_scl.gpioRead()) {
        _this->handler(_this->_sda.gpioRead() ? I2C::high : I2C::low);
    } else {
        _this->handler(I2C::scl_falling);
    }
}

// I2C slave state machine
void soft_i2c_slave::handler(I2C::I2C_event e)
{
    do {
        switch (_state) {
            ////////////////
            // STATE IDLE //
            ////////////////
            case I2C::IDLE: {
                // enter code
                if (_enter) {
                    _byte_index = 0;
                    _enter = false;
                }
                // events
                if (e == I2C::start) {
                    _read_addr = true;
                    setState(I2C::READ);
                    break;
                }
                return;
            }
            ////////////////
            // STATE READ //
            ////////////////
            case I2C::READ: {
                // enter code
                if (_enter) {
                    _data      = 0;
                    _bit_mask  = 0x80;
                    _enter     = false;
                    return;
                }
                // events
                if (e == I2C::high) {
                    _data |= _bit_mask;
                    _bit_mask >>= 1;
                    return;
                }
                else if (e == I2C::low) {
                    _bit_mask >>= 1;
                    return;
                }
                else if (e == I2C::scl_falling) {
                    // check if complete byte has been received
                    if (!_bit_mask) {
                        if (_read_addr) {
                            // process device address
                            _send = _data & 0x01;
                            _data >>= 1;
                            _ack  = (_data == _i2c_address);
                            _read_addr = false;
                        } else {
                            // process user data and stretch clock
                            _scl.gpioWrite(LOW);
                            _ack = _receive(_byte_index++, _data);
                            _scl.gpioWrite(HIGH);
                        }
                        setState(I2C::WRITE_ACK);
                        break;
                    }
                    return;
                }
                else if (e == I2C::start) {
                    _read_addr = true;
                    setState(I2C::READ);
                    break;
                }
                else if (e == I2C::stop) {
                    setState(I2C::IDLE);
                    break;
                }
                return;
            }
            /////////////////////
            // STATE WRITE ACK //
            /////////////////////
            case I2C::WRITE_ACK: {
                // enter code
                if (_enter) {
                    _sda.gpioWrite(!_ack);
                    _enter = false;
                    return;
                }
                // events
                if (e == I2C::scl_falling) {
                    // release SDA line
                    _sda.gpioWrite(HIGH);
                    if (_ack) {
                        setState(_send ? I2C::WRITE : I2C::READ);
                    } else {
                        setState(I2C::WAIT);
                    }
                    break;
                }
                else if (e == I2C::start) {
                    _read_addr = true;
                    setState(I2C::READ);
                    break;
                }
                else if (e == I2C::stop) {
                    setState(I2C::IDLE);
                    break;
                }
                return;
            }
            /////////////////
            // STATE WRITE //
            /////////////////
            case I2C::WRITE: {
                // enter code
                if (_enter) {
                    _bit_mask = 0x80;
                    // Read in the byte to send
                    _scl.gpioWrite(LOW);
                    _data = _transmit(_byte_index++);
                    _scl.gpioWrite(HIGH);
                    // set first bit
                    _sda.gpioWrite(_data & _bit_mask);
                    _bit_mask >>= 1;
                    _enter = false;
                    return;
                }
                // events
                if (e == I2C::scl_falling) {
                    if (_bit_mask) {
                        // send next bit
                        _sda.gpioWrite(_data & _bit_mask);
                        _bit_mask >>= 1;
                        return;
                    } else {
                        // release SDA line
                        _sda.gpioWrite(HIGH);
                        setState(I2C::READ_ACK);
                        break;
                    }
                }
                else if (e == I2C::start) {
                    _read_addr = true;
                    setState(I2C::READ);
                    break;
                }
                else if (e == I2C::stop) {
                    setState(I2C::IDLE);
                    break;
                }
                return;
            }
            ////////////////////
            // STATE READ ACK //
            ////////////////////
            case I2C::READ_ACK: {
                // enter code
                if (_enter) {
                    _enter = false;
                    return;
                }
                // events
                if (e == I2C::high) {
                    _ack = false;
                    return;
                }
                else if (e == I2C::low) {
                    _ack = true;
                    return;
                }
                else if (e == I2C::scl_falling) {
                    if (_ack) {
                        _scl.gpioWrite(LOW);
                        _wantmore();
                        _scl.gpioWrite(HIGH);
                        setState(I2C::WRITE);
                    } else {
                        setState(I2C::WAIT);
                    }
                    break;
                }
                else if (e == I2C::start) {
                    _read_addr = true;
                    setState(I2C::READ);
                    break;
                }
                else if (e == I2C::stop) {
                    setState(I2C::IDLE);
                    break;
                }
                return;
            }
            ////////////////
            // STATE WAIT //
            ////////////////
            case I2C::WAIT: {
                // enter code
                if (_enter) {
                    _enter = false;
                    return;
                }
                // events
                if (e == I2C::start) {
                    _read_addr = true;
                    setState(I2C::READ);
                    break;
                }
                else if (e == I2C::stop) {
                    setState(I2C::IDLE);
                    break;
                }
                return;
            }
        }
    } while (true);
}



