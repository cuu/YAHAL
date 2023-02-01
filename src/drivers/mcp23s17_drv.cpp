/*
 * mcp23s17_drv.cpp
 *
 *  Created on: 28.02.2016
 *      Author: Andreas Terstegge
 */

#include "mcp23s17_drv.h"
#include "yahal_assert.h"

namespace MCP23S17 {
// Chip register addresses
// -----------------------
// IODIR_REG   : I/O direction:  0 = output, 1 = input
// IPOL_REG    : Input Polarity: 0 = normal, 1 = inverted
// GPINTEN_REG : interrupt enable: 0 = diabled, 1 = enabled
// DEFVAL_REG  : Default Value (for interrupt generation)
// INTCON_REG  : interrupt control: 0 = int on change, 1 = int on !default
// IOCON_REG   : I/O Expander configuration (see datasheet)
// GPPU_REG    : GPIO Pull-Up resistor: 0 = disabled, 1 = enabled
// INTF_REG    : interrupt flag: 0 = no interrupt pending, 1 = int pending
// INTCAP_REG  : interrupt captured value: State of port when int occured
// GPIO_REG    : GPIO Port: Read/Write value to port
// OLAT_REG    : Output latch: (possible) state of GPIO output pins
static const uint8_t IODIR_REG   = 0x00;
//  static const uint8_t IPOL_REG    = 0x02;
static const uint8_t GPINTEN_REG = 0x04;
static const uint8_t DEFVAL_REG  = 0x06;
static const uint8_t INTCON_REG  = 0x08;
static const uint8_t IOCON_REG   = 0x0A;
static const uint8_t GPPU_REG    = 0x0C;
static const uint8_t INTF_REG    = 0x0E;
static const uint8_t INTCAP_REG  = 0x10;
static const uint8_t GPIO_REG    = 0x12;
static const uint8_t OLAT_REG    = 0x14;
}

mcp23s17_drv::mcp23s17_drv(spi_interface & hw, uint8_t spi_addr)
: _spi(hw), _spi_addr(spi_addr) {
	// Read current register values for caching
	_iodir   = readRegister( MCP23S17::IODIR_REG );
	_gppu    = readRegister( MCP23S17::GPPU_REG  );
	_olat    = readRegister( MCP23S17::OLAT_REG  );
	_gpinten = readRegister( MCP23S17::GPINTEN_REG );
	_defval  = readRegister( MCP23S17::DEFVAL_REG );
	_intcon  = readRegister( MCP23S17::INTCON_REG );
	// bank = 0, int mirror, enable sequential operation,
	// enable HW addr lines, interrupt active high
	writeRegister(MCP23S17::IOCON_REG, 0x4a4a);
}

void mcp23s17_drv::gpioMode(uint16_t gpio, uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint16_t mask      = (1 << (port*8 + pin));
	uint16_t iodir_old = _iodir;
	uint16_t gppu_old  = _gppu;
	uint16_t olat_old  = _olat;

	switch(mode & ~GPIO::INIT_HIGH & ~GPIO::INIT_LOW) {
		case GPIO::INPUT: {
			_iodir |=  mask;
			_gppu  &= ~mask;
			break;
		}
		case GPIO::INPUT | GPIO::PULLUP: {
			_iodir |=  mask;
			_gppu  |= mask;
			break;
		}
		case GPIO::OUTPUT: {
			_iodir &= ~mask;
			break;
		}
		default: {
			yahal_assert(false);
		}
	}

	if (mode & GPIO::INIT_HIGH) _olat |= mask;
	if (mode & GPIO::INIT_LOW) 	_olat &= ~mask;

	// write back register values if necessary
	if (iodir_old != _iodir)
		writeRegister(MCP23S17::IODIR_REG, _iodir);
	if (gppu_old != _gppu)
		writeRegister(MCP23S17::GPPU_REG, _gppu);
	if (olat_old != _olat)
		writeRegister(MCP23S17::OLAT_REG, _olat);
}

bool mcp23s17_drv::gpioRead(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
    uint16_t mask = (1 << (port*8 + pin));
	return readRegister(MCP23S17::GPIO_REG) & mask ? true : false;
}

void mcp23s17_drv::gpioWrite(uint16_t gpio, bool value) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
    uint16_t mask = (1 << (port*8 + pin));
	uint16_t olat_old = _olat;
	if (value) {
		_olat |= mask;
	} else {
		_olat &= ~mask;
	}
	if (olat_old != _olat)
		writeRegister(MCP23S17::OLAT_REG, _olat);
}

void mcp23s17_drv::attachInterrupt(uint16_t gpio,
		void (*handler)(uint16_t gpio),
		uint16_t mode) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
    uint16_t mask      = (1 << (port*8 + pin));
	uint16_t defvalold = _defval;
	uint16_t intconold = _intcon;

	switch(mode) {
		case GPIO::RISING:
		case GPIO::FALLING:
		case GPIO::RISING | GPIO::FALLING: {
			_intcon &= ~mask;
			break;
		}
		case GPIO::LEVEL_HIGH: {
			_defval &= ~mask; // default value is 0
			_intcon |=  mask; // compare with defval
			break;
		}
		case GPIO::LEVEL_LOW: {
			_defval |= mask; // default value is 1
			_intcon |= mask; // compare with defval
			break;
		}
	}

	// store handler data
	intHandler[port][pin] = handler;
	intMode   [port][pin] = mode;
	// write back register values if necessary
	if (defvalold != _defval)
		writeRegister(MCP23S17::DEFVAL_REG, _defval);
	if (intconold != _intcon)
		writeRegister(MCP23S17::INTCON_REG, _intcon);
	// finally enable the interrupt
	enableInterrupt(gpio);
}

void mcp23s17_drv::detachInterrupt(uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	disableInterrupt(gpio);
	intHandler[port][pin] = 0;
	intMode   [port][pin] = 0;
}

void mcp23s17_drv::enableInterrupt (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
	uint16_t mask       = (1 << (port*8 + pin));
	uint16_t gpintenold = _gpinten;
	_gpinten |= mask;
	if (gpintenold != _gpinten)
		writeRegister(MCP23S17::GPINTEN_REG, _gpinten);
}

void mcp23s17_drv::disableInterrupt (uint16_t gpio) {
    uint8_t port = PORT(gpio);
    uint8_t pin  = PIN (gpio);
    uint16_t mask       = (1 << (port*8 + pin));
	uint16_t gpintenold = _gpinten;
	_gpinten &= ~mask;
	if (gpintenold != _gpinten)
		writeRegister(MCP23S17::GPINTEN_REG, _gpinten);
}

void mcp23s17_drv::handleInterrupt() {
	// read interrupt status and clear interrupt
	uint16_t intFlags = readRegister(MCP23S17::INTF_REG);
	uint16_t intValue = readRegister(MCP23S17::INTCAP_REG);
	uint16_t mask = 0x0001;
	for (uint8_t i=0; i < 16; i++) {
		if (intFlags & mask) {
			uint8_t port = i/8;
			uint8_t pin  = i%8;
			switch(intMode[port][pin]) {
			case GPIO::RISING:
				if ((intValue & mask) != 0)
					intHandler[port][pin](PORT_PIN(port, pin));
				break;
			case GPIO::FALLING:
				if ((intValue & mask) == 0)
					intHandler[port][pin](PORT_PIN(port, pin));
				break;
			default:
				intHandler[port][pin](PORT_PIN(port, pin));
			}
		}
		mask <<= 1;
	}
}


uint16_t mcp23s17_drv::digitalReadPort(uint16_t mask) {
	return readRegister(MCP23S17::GPIO_REG) & mask;
}

void mcp23s17_drv::digitalWritePort(uint16_t value, uint16_t mask) {
	uint16_t olat_old = _olat;
	_olat  &= ~mask;
	value  &=  mask;
	_olat  |=  value;
	if (olat_old != _olat)
		writeRegister(MCP23S17::OLAT_REG, _olat);
}

uint16_t mcp23s17_drv::readRegister(uint8_t reg) {
	unsigned char txbuf[4];
	unsigned char rxbuf[4];

	txbuf[0] = 0x41 | (_spi_addr << 1);
	txbuf[1] = reg;
	txbuf[2] = 0; // dummy
	txbuf[3] = 0; // dummy

	_spi.spiTxRx(txbuf, rxbuf, 4);
	return (rxbuf[3] << 8) | rxbuf[2];
}

void mcp23s17_drv::writeRegister(uint8_t reg, uint16_t value) {
	unsigned char txbuf[4];
	unsigned char rxbuf[4];

	txbuf[0] = 0x40 | (_spi_addr << 1);
	txbuf[1] = reg;
	txbuf[2] = value & 0xff;
	txbuf[3] = value >> 8;

	_spi.spiTxRx(txbuf, rxbuf, 4);
}

