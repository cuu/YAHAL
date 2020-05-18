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

#include "soft_i2c_master.h"

soft_i2c_master::soft_i2c_master(gpio_pin & sda, gpio_pin & scl,
                                 void (*delay)(uint32_t us), bool pullup)
    : _init(false),
      _sda(sda),
      _scl(scl),
      _delay(delay),
      _pullup(pullup),
      _us(0)
{
}

soft_i2c_master::~soft_i2c_master()
{
    if (!_init) return;
    _sda.gpioMode(GPIO::INPUT);
    _scl.gpioMode(GPIO::INPUT);
}

int16_t soft_i2c_master::i2cRead(uint16_t addr, uint8_t *rxbuf, uint16_t len,
                                 bool sendStop)
{
    if (!_init) init();
    if (!send_start()) return -1;
    addr <<= 1;
    addr |= 1;
    addr &= 0xff;
    if (!write_byte(addr)) {
        if (sendStop) send_stop();
        return -2;
    }
    for (uint16_t i = 0; i < len; ++i) {
        rxbuf[i] = read_byte(i==(len-1));
    }
    if (sendStop) send_stop();
    return len;
}

int16_t soft_i2c_master::i2cWrite(uint16_t addr, uint8_t *txbuf, uint16_t len,
                                  bool sendStop)
{
    if (!_init) init();
    if (!send_start()) return -1;
    addr <<= 1;
    addr &= 0xff;
    if (!write_byte(addr)) {
        if (sendStop) send_stop();
        return -2;
    }
    for (uint16_t i = 0; i < len; ++i) {
        if (!write_byte(txbuf[i])) {
            if (sendStop) send_stop();
            return i;
        }
    }
    if (sendStop) send_stop();
    return len;
}

void soft_i2c_master::setSpeed(uint32_t hz) {
    if (!_init) init();
    _us = 1000000 / hz;
    // There are 3 delays during sending/receiving
    // of a single bit (one SCL cycle). So we have
    // to divide the time by 3.
    _us /= 3;
}

void soft_i2c_master::init()
{
    uint16_t mode = GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH;
    if (_pullup)
        mode |= GPIO::PULLUP;
    // Initialize HW pins
    _sda.gpioMode(mode);
    _scl.gpioMode(mode);
    _init = true;
}

// private methods

uint8_t soft_i2c_master::read_byte(bool nack)
{
    uint8_t byte = 0;
    for (uint8_t bit = 0; bit < 8; ++bit) {
        byte = (byte << 1);
        byte |= read_bit();
    }
    write_bit(nack);
    return byte;
}

bool soft_i2c_master::write_byte(uint8_t byte)
{
    for (uint8_t bit = 0; bit < 8; ++bit) {
        write_bit(byte & 0x80);
        byte <<= 1;
    }
    return !read_bit(); // LOW means ACK
}

bool soft_i2c_master::read_bit()
{
    _scl.gpioWrite(LOW);
    _delay(_us);
    _sda.gpioWrite(HIGH);
    _delay(_us);
    _scl.gpioWrite(HIGH);
    // Clock stretching
    while (_scl.gpioRead() == LOW) _delay(_us);
    bool bit = _sda.gpioRead();
    _delay(_us);
    return bit;
}

bool soft_i2c_master::write_bit(bool bit)
{
    _scl.gpioWrite(LOW);
    _delay(_us);
    _sda.gpioWrite(bit);
    _delay(_us);
    _scl.gpioWrite(HIGH);
    // Clock stretching
    do _delay(_us); while (_scl.gpioRead() == LOW);
    return true;
}

bool soft_i2c_master::send_start()
{
    if (!check_bus_idle()) return false;
    _sda.gpioWrite(LOW);
    _delay(_us);
    return true;
}

void soft_i2c_master::send_stop()
{
    _scl.gpioWrite(LOW);
    _delay(_us);
    _sda.gpioWrite(LOW);
    _delay(_us);
    _scl.gpioWrite(HIGH);
    // Clock stretching
    do _delay(_us); while (_scl.gpioRead() == LOW);
    _sda.gpioWrite(HIGH);
    _delay(_us);
}

bool soft_i2c_master::check_bus_idle() {
    // Do not touch the I2C bus
    _scl.gpioWrite(HIGH);
    _sda.gpioWrite(HIGH);
    // Toggle SCL until bus is idle
    int i=0;
    while((_sda.gpioRead() == LOW) && (i < 20)) {
        _scl.gpioWrite(LOW);
        _delay(_us);
        _scl.gpioWrite(HIGH);
        _delay(_us);
        ++i;
    }
    return i != 20;
}
