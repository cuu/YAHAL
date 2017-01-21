/*
 * spi_msp432.cpp
 *
 *  Created on: 28.02.2016
 *      Author: Andreas Terstegge
 */

#include "spi_msp432.h"
#include "assert.h"

spi_msp432::spi_msp432(EUSCI_A_SPI_Type *mod, gpio_pin & cs,
					   uint16_t mode)
:	_EUSCI_CTLW0(mod->CTLW0), _EUSCI_BRW(mod->BRW),
	_EUSCI_STATW(mod->STATW), _EUSCI_RXBUF(mod->RXBUF),
	_EUSCI_TXBUF(mod->TXBUF), _EUSCI_IE(mod->IE),
    _EUSCI_IFG(mod->IFG),     _EUSCI_IV(mod->IV),
	_mode(mode), _cs(cs) {
	// Configure hardware characteristics of the 4 A-type modules
	/////////////////////////////////////////////////////////////
	if (mod==EUSCI_A0_SPI) {
		_ste.setGpio (PORT_PIN(1, 0));
		_clk.setGpio (PORT_PIN(1, 1));
		_miso.setGpio(PORT_PIN(1, 2));
		_mosi.setGpio(PORT_PIN(1, 3));
	} else if (mod==EUSCI_A1_SPI) {
		_ste.setGpio (PORT_PIN(2, 0));
		_clk.setGpio (PORT_PIN(2, 1));
		_miso.setGpio(PORT_PIN(2, 2));
		_mosi.setGpio(PORT_PIN(2, 3));
	} else if (mod==EUSCI_A2_SPI) {
		_ste.setGpio (PORT_PIN(3, 0));
		_clk.setGpio (PORT_PIN(3, 1));
		_miso.setGpio(PORT_PIN(3, 2));
		_mosi.setGpio(PORT_PIN(3, 3));
	} else if (mod==EUSCI_A3_SPI) {
		_ste.setGpio (PORT_PIN(9, 4));
		_clk.setGpio (PORT_PIN(9, 5));
		_miso.setGpio(PORT_PIN(9, 6));
		_mosi.setGpio(PORT_PIN(9, 7));
	}
	else assert(false);
    spi_init();
}

spi_msp432::spi_msp432(EUSCI_B_SPI_Type *mod, gpio_pin & cs,
					   uint16_t mode)
:	_EUSCI_CTLW0(mod->CTLW0), _EUSCI_BRW(mod->BRW),
	_EUSCI_STATW(mod->STATW), _EUSCI_RXBUF(mod->RXBUF),
	_EUSCI_TXBUF(mod->TXBUF), _EUSCI_IE(mod->IE),
    _EUSCI_IFG(mod->IFG),     _EUSCI_IV(mod->IV),
	_mode(mode), _cs(cs) {
	// Configure hardware characteristics of the 4 B-type modules
	/////////////////////////////////////////////////////////////
	if (mod==EUSCI_B0_SPI) {
		_ste.setGpio (PORT_PIN(1, 4));
		_clk.setGpio (PORT_PIN(1, 5));
		_miso.setGpio(PORT_PIN(1, 7));
		_mosi.setGpio(PORT_PIN(1, 6));
	} else if (mod==EUSCI_B1_SPI) {
		_ste.setGpio (PORT_PIN(6, 2));
		_clk.setGpio (PORT_PIN(6, 3));
		_miso.setGpio(PORT_PIN(6, 5));
		_mosi.setGpio(PORT_PIN(6, 4));
	} else if (mod==EUSCI_B2_SPI) {
		_ste.setGpio (PORT_PIN(3, 4));
		_clk.setGpio (PORT_PIN(3, 5));
		_miso.setGpio(PORT_PIN(3, 7));
		_mosi.setGpio(PORT_PIN(3, 6));
	} else if (mod==EUSCI_B3_SPI) {
		_ste.setGpio (PORT_PIN(10, 0));
		_clk.setGpio (PORT_PIN(10, 1));
		_miso.setGpio(PORT_PIN(10, 3));
		_mosi.setGpio(PORT_PIN(10, 2));
	}
	else assert(false);
    spi_init();
}

spi_msp432::~spi_msp432() {
	// Wait for pending operations
	//////////////////////////////
	while (_EUSCI_STATW & EUSCI_A_STATW_BUSY);

	// Reset CTLW0 register to default values
	// (EUSCI_A is in reset state)
	/////////////////////////////////////////
	_EUSCI_CTLW0 = EUSCI_A_CTLW0_SWRST;

	// De-configure the digital lines
	/////////////////////////////////
	_ste.setSEL(0);  _ste.setMode(GPIO::INPUT);
	_clk.setSEL(0);  _clk.setMode(GPIO::INPUT);
	_miso.setSEL(0); _miso.setMode(GPIO::INPUT);
	_mosi.setSEL(0); _mosi.setMode(GPIO::INPUT);
}

void spi_msp432::spi_init() {

	// Reset CTLW0 register to default values
	// (EUSCI is in reset state)
	/////////////////////////////////////////
	_EUSCI_CTLW0 = EUSCI_A_CTLW0_SWRST;

	// Configure SPI port
	/////////////////////
	_mode |= EUSCI_A_CTLW0_MST  |  // always SPI master mode
			 EUSCI_A_CTLW0_SYNC |  // always synchronous mode
			 EUSCI_A_CTLW0_STEM;   // always STE as CS-line
								   // always 3 wire mode!
	_EUSCI_CTLW0 |= _mode;

	// Disable interrupts
	/////////////////////
	_EUSCI_IE &= ~(EUSCI_A_IE_RXIE |
				   EUSCI_A_IE_TXIE |
				   EUSCI_A_IE_STTIE);

	// Configure the digital RX/TX lines
	////////////////////////////////////
	_clk. setSEL(1); _clk. setMode(GPIO::OUTPUT);
	_miso.setSEL(1); _miso.setMode(GPIO::INPUT);
	_mosi.setSEL(1); _mosi.setMode(GPIO::OUTPUT);

	// Activate CS line
	///////////////////
	_cs.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

	// Finally enable EUSCI module
	//////////////////////////////
	_EUSCI_CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
}


int16_t spi_msp432::transfer(uint8_t *txbuf, uint8_t *rxbuf, uint16_t len) {
	// Activate CS line
	_cs.gpioWrite(LOW);
	for (int i=0; i < len; ++i) {
		// Transfer single char to TX buffer
		while( !(_EUSCI_IFG & EUSCI_A_IFG_TXIFG));
		_EUSCI_TXBUF = (uint16_t)(txbuf[i]);
		// Receive single char from RX buffer
		while( !(_EUSCI_IFG & EUSCI_A_IFG_RXIFG));
		rxbuf[i] = (uint8_t)(_EUSCI_RXBUF);
	}
	// De-activate CS line
	_cs.gpioWrite(HIGH);
	return len;
}

