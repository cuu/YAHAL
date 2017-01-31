/*
 * softi2cmaster.cpp
 *
 *  Created on: 31.01.2017
 *      Author: aterstegge
 */

#include "soft_i2c_master.h"

soft_i2c_master::soft_i2c_master(gpio_pin & sda, gpio_pin & scl, void (*delay)())
: _sda(sda), _scl(scl), _delay(delay) {
	// Initialize HW pins
	_sda.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH);
	_scl.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH);
}

soft_i2c_master::~soft_i2c_master() {
	_sda.gpioMode(GPIO::INPUT);
	_scl.gpioMode(GPIO::INPUT);
}

int16_t soft_i2c_master::write(uint8_t addr, uint8_t *txbuf, uint8_t len) {
	return write(addr, txbuf, len, true);
}

int16_t soft_i2c_master::read (uint8_t addr, uint8_t *rxbuf, uint8_t len) {
	return read(addr, rxbuf, len, true);
}

void soft_i2c_master::twice(uint8_t addr,
           I2C::i2c_mode m1, uint8_t *buf1, uint8_t len1,
           I2C::i2c_mode m2, uint8_t *buf2, uint8_t len2) {
	switch(m1) {
	case I2C::READ:	 read (addr, buf1, len1, false);
	case I2C::WRITE: write(addr, buf1, len1, false);
	}
	switch(m2) {
	case I2C::READ:	 read (addr, buf2, len2, true);
	case I2C::WRITE: write(addr, buf2, len2, true);
	}
}

bool soft_i2c_master::i2c_start() {
	_scl.gpioWrite(HIGH);
	_sda.gpioWrite(HIGH);
	// Is SDA still occupied?
	if (_sda.gpioRead() == LOW) return false;
	_delay();
	_sda.gpioWrite(LOW);
	_delay();
	return true;
}

bool soft_i2c_master::i2c_stop () {
	_scl.gpioWrite(LOW);
	_sda.gpioWrite(LOW);
	_delay();
	_scl.gpioWrite(HIGH);
	// Clock stretching
	do _delay(); while (_scl.gpioRead() == LOW);
	_sda.gpioWrite(HIGH);
	_delay();
	return true;
}

bool soft_i2c_master::i2c_write_bit(bool bit) {
	_scl.gpioWrite(LOW);
	_sda.gpioWrite(bit);
	_delay();
	_scl.gpioWrite(HIGH);
	// Clock stretching
	do _delay(); while (_scl.gpioRead() == LOW);
	return true;
}

bool soft_i2c_master::i2c_read_bit() {
	_scl.gpioWrite(LOW);
	_sda.gpioWrite(HIGH);
	_delay();
	_scl.gpioWrite(HIGH);
	// Clock stretching
	while (_scl.gpioRead() == LOW) _delay();
	bool bit = _sda.gpioRead();
	_delay();
	return bit;
}

bool soft_i2c_master::i2c_write_byte(uint8_t byte) {
	for (uint8_t bit=0; bit < 8; ++bit) {
		i2c_write_bit(byte & 0x80);
		byte <<= 1;
	}
	return !i2c_read_bit(); // LOW means ACK
}

int8_t soft_i2c_master::i2c_read_byte(bool nack) {
	uint8_t byte = 0;
	for (uint8_t bit = 0; bit < 8; ++bit) {
		byte  = (byte << 1);
		byte |= i2c_read_bit();
	}
	i2c_write_bit(nack);
	return byte;
}

int16_t soft_i2c_master::write(uint8_t addr, uint8_t *txbuf, uint8_t len, bool sendStop) {
	if (!i2c_start()) return -1;
	addr <<= 1;
	addr  &= 0xff;
	if (!i2c_write_byte(addr)) {
		 if (sendStop) i2c_stop();
		 return -2;
	}
	for (uint8_t i=0; i < len; ++i) {
		if (!i2c_write_byte(txbuf[i])) {
			if (sendStop) i2c_stop();
			return -3;
		}
	}
	if (sendStop) i2c_stop();
	for (uint8_t i=0; (_sda.gpioRead()==LOW) && (i < 10); ++i) {
		_scl.gpioWrite(LOW);  _delay();
		_scl.gpioWrite(HIGH); _delay();
	}
	return len;
}

int16_t soft_i2c_master::read (uint8_t addr, uint8_t *rxbuf, uint8_t len, bool sendStop) {
	if (!i2c_start()) return -1;
	addr <<= 1;
	addr  |= 1;
	addr  &= 0xff;
	if (!i2c_write_byte(addr)) {
		 if (sendStop) i2c_stop();
		 return -2;
	}
	for (uint8_t i=0; i < (len-1); ++i) {
		rxbuf[i] = i2c_read_byte(false);
	}
	rxbuf[len-1] = i2c_read_byte(true);
	if (sendStop) i2c_stop();
	for (uint8_t i=0; (_sda.gpioRead()==LOW) && (i < 10); ++i) {
		_scl.gpioWrite(LOW);  _delay();
		_scl.gpioWrite(HIGH); _delay();
	}
	return len;
}
