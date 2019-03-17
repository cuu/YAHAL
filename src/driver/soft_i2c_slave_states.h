/*
 * soft_i2c_slave_states.h
 *
 *  Created on: 16.03.2019
 *      Author: student
 */

#ifndef _SOFT_I2C_SLAVE_STATES_H_
#define _SOFT_I2C_SLAVE_STATES_H_

#include <cstdint>

class soft_i2c_slave;

namespace I2C
{

class STATE {
public:
    STATE(soft_i2c_slave & c) : _context(c) {}

    virtual void enter() { }
    virtual void leave() { }

    void start();
    void stop();
    virtual void high()  { }
    virtual void low()   { }
    virtual void scl_falling() { }

protected:
    soft_i2c_slave & _context;
};

class IDLE : public STATE {
public:
    IDLE(soft_i2c_slave & c) :  STATE(c) {}
    void enter() override;
};

class READ_ADDR : public STATE {
public:
    READ_ADDR(soft_i2c_slave & c) :  STATE(c), _data(0), _bit_mask(0) {}
    void enter() override;
    void high()  override;
    void low()   override;
    void scl_falling() override;
private:
    uint8_t _data;
    int     _bit_mask;
};

class WRITE_ACK : public STATE {
public:
    WRITE_ACK(soft_i2c_slave & c) :  STATE(c) {}
    void enter() override;
    void scl_falling() override;
};

class READ_DATA : public STATE {
public:
    READ_DATA(soft_i2c_slave & c) :  STATE(c), _data(0), _bit_mask(0) {}
    void enter() override;
    void high()  override;
    void low()   override;
    void scl_falling() override;
private:
    uint8_t   _data;
    int       _bit_mask;
};

class WRITE_DATA : public STATE {
public:
    WRITE_DATA(soft_i2c_slave & c) :  STATE(c) {}
    void enter() override;
    void scl_falling() override;
private:
    uint8_t   _data;
    int       _bit_mask;
};

class READ_ACK : public STATE {
public:
    READ_ACK(soft_i2c_slave & c) :  STATE(c) {}
    void high()  override;
    void low()   override;
    void scl_falling() override;
};

} // namespace I2C

#endif // _SOFT_I2C_SLAVE_STATES_H_
