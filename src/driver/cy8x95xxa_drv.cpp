/*
 * cy8x95xxa_drv.cpp
 *
 *  Created on: 28.02.2016
 *      Author: Andreas Terstegge
 */

#include "cy8c95xxa_drv.h"
#include "assert.h"

#include <iostream>
using namespace std;

namespace CY8C95XXA {
// Chip register addresses
static const uint8_t INPUT_REG   = 0x00;
static const uint8_t OUTPUT_REG  = 0x08;
static const uint8_t INT_STATUS  = 0x10;
static const uint8_t PRT_SEL_REG = 0x18;
static const uint8_t INT_MSK_REG = 0x19;
static const uint8_t SEL_PWM_REG = 0x1a;
//  static const uint8_t INVERSE_REG = 0x1b;
static const uint8_t PIN_DIR_REG = 0x1c;
static const uint8_t PULLUP_REG  = 0x1d;
static const uint8_t PULLDN_REG  = 0x1e;
static const uint8_t OD_HIGH_REG = 0x1f;
static const uint8_t OD_LOW_REG  = 0x20;
static const uint8_t STRONG_REG  = 0x21;
static const uint8_t SLOWST_REG  = 0x22;
static const uint8_t HIGHZ_REG   = 0x23;
static const uint8_t PWM_SEL_REG = 0x28;
static const uint8_t DIVIDER_REG = 0x2c;
static const uint8_t ENABLE_REG  = 0x2d;
static const uint8_t DEV_ID_REG  = 0x2e;
static const uint8_t COMMAND_REG = 0x30;

int8_t gpio_to_pwm[8][8] = {  7,  5,  3,  1,  7,  5,  3,  1,
		6,  4,  2,  0,  6,  4,  2,  0,
		14, 12,  8, 11, -1, -1, -1, -1,
		7,  5,  3,  1, 15, 13, 11,  9,
		6,  4,  2,  0, 14, 12, 10,  8,
		10,  8, 11,  9, 12, 14, 13, 15,
		0,  1,  2,  3,  4,  5,  6,  7,
		8,  9, 10, 11, 12, 13, 14, 15 };
};

cy8c95xxa_drv::cy8c95xxa_drv(i2c_interface & hw, uint8_t addr)
: _i2c(hw), _i2c_addr(addr) {
	// Detect the device
	uint8_t val = readRegister(CY8C95XXA::DEV_ID_REG);
	switch(val & 0xf0) {
	case 0x20: _pwm_mask = 0x03; break;
	case 0x40: _pwm_mask = 0x07; break;
	case 0x60: _pwm_mask = 0x0f; break;
	default: assert(false);
	}
	// read current output values
	for (uint8_t port = 0; port < 8; ++port) {
		_output[port] = readRegister( CY8C95XXA::OUTPUT_REG + port );
	}
}

void cy8c95xxa_drv::pinMode(uint16_t gpio, uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint8_t mask = (1 << pin);
	writeRegister(CY8C95XXA::PRT_SEL_REG, port);

	switch (mode & ~GPIO::INIT_HIGH & ~GPIO::INIT_LOW) {
		case GPIO::INPUT: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0xff, mask);
			writeRegister(CY8C95XXA::HIGHZ_REG,   0xff, mask);
			break;
		}
		case GPIO::INPUT | GPIO::PULLUP: {
			digitalWrite(gpio, true);
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0xff, mask);
			writeRegister(CY8C95XXA::PULLUP_REG,  0xff, mask);
			break;
		}
		case GPIO::INPUT | GPIO::PULLDOWN: {
			digitalWrite(gpio, false);
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0xff, mask);
			writeRegister(CY8C95XXA::PULLDN_REG,  0xff, mask);
			break;
		}
		case GPIO::OUTPUT: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0x00, mask);
			writeRegister(CY8C95XXA::STRONG_REG,  0xff, mask);
			break;
		}
		case GPIO::OUTPUT | GPIO::SLOW: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0x00, mask);
			writeRegister(CY8C95XXA::SLOWST_REG,  0xff, mask);
			break;
		}
		case GPIO::OUTPUT_OPEN_DRAIN: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0x00, mask);
			writeRegister(CY8C95XXA::OD_LOW_REG,  0xff, mask);
			break;
		}
		case GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0x00, mask);
			writeRegister(CY8C95XXA::PULLUP_REG,  0xff, mask);
			break;
		}
		case GPIO::OUTPUT_OPEN_SOURCE: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0x00, mask);
			writeRegister(CY8C95XXA::OD_HIGH_REG, 0xff, mask);
			break;
		}
		case GPIO::OUTPUT_OPEN_SOURCE | GPIO::PULLDOWN: {
			writeRegister(CY8C95XXA::PIN_DIR_REG, 0x00, mask);
			writeRegister(CY8C95XXA::PULLDN_REG,  0xff, mask);
			break;
		}
		default: {
			assert(false);
		}
	}
	if (mode & GPIO::INIT_HIGH) digitalWrite(gpio, true);
	if (mode & GPIO::INIT_LOW)  digitalWrite(gpio, false);
}

bool cy8c95xxa_drv::digitalRead(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint8_t mask = (1 << pin);
	return (readRegister(CY8C95XXA::INPUT_REG + port) & mask);
}

void cy8c95xxa_drv::digitalWrite(uint16_t gpio, bool value) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint8_t mask = (1 << pin);
	uint8_t old = _output[port];
	if (value) _output[port] |= mask;
	else       _output[port] &= ~mask;
	if (_output[port] != old) {
		writeRegister(CY8C95XXA::OUTPUT_REG + port, _output[port]);
	}
}

// Interrupt handling
/////////////////////
void cy8c95xxa_drv::attachInterrupt (uint16_t gpio,
                                     void (*handler)(uint16_t gpio),
                                     uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	assert(!(mode & ~GPIO::RISING & ~GPIO::FALLING));
	intHandler[port][pin] = handler;
	intMode   [port][pin] = mode;
	enableInterrupt(gpio);
}

void cy8c95xxa_drv::detachInterrupt (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	disableInterrupt(gpio);
	intHandler[port][pin] = 0;
	intMode   [port][pin] = 0;
}

void cy8c95xxa_drv::enableInterrupt (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint8_t mask = (1 << pin);
	writeRegister(CY8C95XXA::PRT_SEL_REG, port);
	writeRegister(CY8C95XXA::INT_MSK_REG, 0x00, mask);
}

void cy8c95xxa_drv::disableInterrupt(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint8_t mask = (1 << pin);
	writeRegister(CY8C95XXA::PRT_SEL_REG, port);
	writeRegister(CY8C95XXA::INT_MSK_REG, 0xff, mask);
}

void cy8c95xxa_drv::handleInterrupt() {
	// Read out irq status
	uint8_t txbuf[1];
	uint8_t irqStatus[8];
	uint8_t irqValue [8];
	txbuf[0] = CY8C95XXA::INT_STATUS;
	_i2c.twice(_i2c_addr, I2C::WRITE, txbuf, 1, I2C::READ, irqStatus, 8);
	txbuf[0] = CY8C95XXA::INPUT_REG;
	_i2c.twice(_i2c_addr, I2C::WRITE, txbuf, 1, I2C::READ, irqValue, 8);
	// Loop over all gpios
	for (uint8_t i=0; i < 64; ++i) {
		uint8_t port = i >> 3;
		uint8_t pin  = i % 8;
		uint8_t mask = (1 << pin);
		// active IRQ?
		if (irqStatus[port] & mask) {
			switch(intMode[port][pin]) {
			case GPIO::RISING:
				if (irqValue[port] & mask) {
					intHandler[port][pin](PORT_PIN(port, pin));
				}
				break;
			case GPIO::FALLING:
				if (!(irqValue[port] & mask)) {
					intHandler[port][pin](PORT_PIN(port, pin));
				}
				break;
			case GPIO::RISING | GPIO::FALLING:
			intHandler[port][pin](PORT_PIN(port, pin));
			break;
			default:
				// Do nothing for all other triggers
				break;
			}
		}
	}
}

// PWM and config stuff
///////////////////////

bool cy8c95xxa_drv::configPWM (uint8_t port, uint8_t pin,
		CY8C95XXA::pwm_clk clk,
		uint8_t period, uint8_t width) {
	uint8_t buf[5];
	int8_t pwm = CY8C95XXA::gpio_to_pwm[port][pin];
	assert(pwm != -1);
	buf[0] = CY8C95XXA::PWM_SEL_REG;
	buf[1] = pwm & _pwm_mask;
	buf[2] = clk;
	buf[3] = period;
	buf[4] = width;
	return _i2c.write(_i2c_addr, buf, 5);
}

void cy8c95xxa_drv::setDivider(uint8_t div) {
	writeRegister(CY8C95XXA::DIVIDER_REG, div);
}

void cy8c95xxa_drv::enablePWM (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	gpioWrite(gpio, true); // PWM is only generated when output is HIGH
	uint8_t mask = (1 << pin);
	writeRegister(CY8C95XXA::PRT_SEL_REG, port);
	writeRegister(CY8C95XXA::SEL_PWM_REG, mask, mask);
}

void cy8c95xxa_drv::disablePWM(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	gpioWrite (gpio, false);
	uint8_t mask = (1 << pin);
	writeRegister(CY8C95XXA::PRT_SEL_REG, port);
	writeRegister(CY8C95XXA::SEL_PWM_REG, 0, mask);
}

void cy8c95xxa_drv::sendCommand(CY8C95XXA::gpio_cmd cmd) {
	uint8_t txbuf[2];
	txbuf[0] = CY8C95XXA::COMMAND_REG;
	txbuf[1] = cmd;
	_i2c.write(_i2c_addr, txbuf, 2);
}

void cy8c95xxa_drv::setEnableReg(CY8C95XXA::gpio_en en) {
	uint8_t txbuf[5];
	txbuf[0] = CY8C95XXA::ENABLE_REG;
	txbuf[1] = 'C';
	txbuf[2] = 'M';
	txbuf[3] = 'S';
	txbuf[4] = en;
	_i2c.write(_i2c_addr, txbuf, 5);
}

// private methods
//////////////////

uint8_t cy8c95xxa_drv::readRegister(uint8_t reg) {
	unsigned char txbuf[1];
	unsigned char rxbuf[1];
	txbuf[0] = reg;
	_i2c.twice(_i2c_addr, I2C::WRITE, txbuf, 1, I2C::READ, rxbuf, 1);
	return rxbuf[0];
}

bool cy8c95xxa_drv::writeRegister(uint8_t reg, uint8_t value, uint8_t mask) {
	unsigned char txbuf[2];
	txbuf[0] = reg;

	if (mask != 0xff) {
		_i2c.twice(_i2c_addr, I2C::WRITE, txbuf, 1, I2C::READ, txbuf+1, 1);
		txbuf[1] &= ~mask; // Reset mask bits
		txbuf[1] |=  value & mask;
	} else {
		txbuf[1] = value;
	}
	return _i2c.write(_i2c_addr, txbuf, 2);
}

