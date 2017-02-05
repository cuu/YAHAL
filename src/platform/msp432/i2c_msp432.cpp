/*
 * spi_msp432.cpp
 *
 *  Created on: 14.06.2016
 *      Author: Andreas Terstegge
 */

#include "i2c_msp432.h"
#include "yahal_assert.h"

i2c_msp432::i2c_msp432(EUSCI_B_Type *mod, uint16_t mode)
: _EUSCI(mod), _mode(mode)
{
	// Configure hardware characteristics
	/////////////////////////////////////
	if (mod==EUSCI_B0) {
		_sda.setGpio (PORT_PIN(1, 6));
		_scl.setGpio (PORT_PIN(1, 7));
	} else if (mod==EUSCI_B1) {
		_sda.setGpio (PORT_PIN(6, 4));
		_scl.setGpio (PORT_PIN(6, 5));
	} else if (mod==EUSCI_B2) {
		_sda.setGpio (PORT_PIN(3, 6));
		_scl.setGpio (PORT_PIN(3, 7));
	} else if (mod==EUSCI_B3) {
		_sda.setGpio (PORT_PIN(10, 2));
		_scl.setGpio (PORT_PIN(10, 3));
	}
	else yahal_assert(false);

	// Reset CTLW0 register to default values
	// (EUSCI is in reset state)
	/////////////////////////////////////////
	_EUSCI->CTLW0 = EUSCI_B_CTLW0_SWRST;

	// Configure I2C port
	/////////////////////
	_mode |= EUSCI_B_CTLW0_MODE_3 |
			 EUSCI_B_CTLW0_SYNC;

	_EUSCI->CTLW0 |= _mode;
	_EUSCI->CTLW1  = 0;

	// Set i2c clock
	////////////////
	_EUSCI->BRW = 48000000 / 100000; // 100 kHz

	// Disable interrupts
	/////////////////////
	_EUSCI->IE = 0;

	// Configure the digital RX/TX lines
	////////////////////////////////////
	_sda.setMode(GPIO::OUTPUT); _sda.setSEL(1);
	_scl.setMode(GPIO::OUTPUT); _scl.setSEL(1);

	// Finally enable EUSCI module
	//////////////////////////////
	_EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;
}


i2c_msp432::~i2c_msp432() {
	// Wait for pending operations
	//////////////////////////////
	while (_EUSCI->STATW & EUSCI_B_STATW_BUSY);

	// Reset CTLW0 register to default values
	// (EUSCI_B is in reset state)
	/////////////////////////////////////////
	_EUSCI->CTLW0 = EUSCI_B_CTLW0_SWRST;

	// De-configure the digital lines
	/////////////////////////////////
	_sda.setSEL(0); _sda.setMode(GPIO::INPUT);
	_scl.setSEL(0); _scl.setMode(GPIO::INPUT);
}


int16_t i2c_msp432::write(uint16_t addr, uint8_t *txbuf, uint8_t len) {
	// set the slave address
	_EUSCI->IFG   = 0;
	_EUSCI->I2CSA = addr;
	set_transmitter();
	send_START();
	int16_t i = 0;
	for (i=0; i < len;  ++i) {
		while(!(_EUSCI->IFG & EUSCI_B_IFG_TXIFG0));
		if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) {
			send_STOP();
			return i;
		}
		_EUSCI->TXBUF = txbuf[i];
	}
	while(!(_EUSCI->IFG & EUSCI_B_IFG_TXIFG0));
	send_STOP();
	return i;
}


int16_t i2c_msp432::read (uint16_t addr, uint8_t *rxbuf, uint8_t len) {
	// set the slave address
	_EUSCI->IFG   = 0;
	_EUSCI->I2CSA = addr;
	set_receiver();
	send_START();
	int16_t i = 0;
	for (i=0; i < len;  ++i) {
		if ((i+1) == len) {
			send_STOP();
		}
		while(!(_EUSCI->IFG & EUSCI_B_IFG_RXIFG0));
		rxbuf[i] = _EUSCI->RXBUF;
		if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) {
			send_STOP();
			return i;
		}
	}
//	send_STOP();
	return i;
}

void i2c_msp432::twice(uint16_t addr,
		               uint8_t *txbuf, uint8_t txlen,
                       uint8_t *rxbuf, uint8_t rxlen) {
	// set the slave address
	_EUSCI->I2CSA = addr;
	set_transmitter();
	send_START();
	int16_t i = 0;
	for (i=0; i < txlen;  ++i) {
		while(!(_EUSCI->IFG & EUSCI_B_IFG_TXIFG0));
		if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) {
			send_STOP();
			yahal_assert(false);
		}
		_EUSCI->TXBUF = txbuf[i];
	}
	while(!(_EUSCI->IFG & EUSCI_B_IFG_TXIFG0));

	set_receiver();
	send_START();
	for (i=0; i < rxlen;  ++i) {
		while(!(_EUSCI->IFG & EUSCI_B_IFG_RXIFG0));
		if (_EUSCI->IFG & EUSCI_B_IFG_NACKIFG) {
			send_STOP();
			yahal_assert(false);
		}
		rxbuf[i] = _EUSCI->RXBUF;
	}
	send_STOP();
	return;
}



void i2c_msp432::send_ADR_ACK() {
	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXACK;
}

void i2c_msp432::send_ADR_NACK() {
	_EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_TXACK;
}

void i2c_msp432::set_receiver() {
	_EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_TR;
}

void i2c_msp432::set_transmitter() {
	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TR;
}

void i2c_msp432::send_ACK() {
	_EUSCI->CTLW0 &= ~EUSCI_B_CTLW0_TXNACK;
}

void i2c_msp432::send_NACK() {
	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXNACK;
}

void i2c_msp432::send_STOP() {
	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
}

void i2c_msp432::send_START() {
	_EUSCI->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
}

