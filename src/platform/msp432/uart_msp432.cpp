
#include "uart_msp432.h"
#include <string.h>
#include "msp432p401r.h"

uart_msp432::uart_msp432(EUSCI_A_Type * mod,
		   uint32_t    baud, UART_BITS bits,
		   UART_PARITY par,  UART_STOP stop)
: _config_complete(false), _EUSCI(mod) {

	// Configure hardware characteristics of the 4 UART modules
	///////////////////////////////////////////////////////////
	if      (mod==EUSCI_A0) { _rx.setGpio(PORT_PIN(1, 2)); _tx.setGpio(PORT_PIN(1, 3)); }
	else if (mod==EUSCI_A1) { _rx.setGpio(PORT_PIN(2, 2)); _tx.setGpio(PORT_PIN(2, 3)); }
	else if (mod==EUSCI_A2) { _rx.setGpio(PORT_PIN(3, 2)); _tx.setGpio(PORT_PIN(3, 3)); }
	else if (mod==EUSCI_A3) { _rx.setGpio(PORT_PIN(9, 6)); _tx.setGpio(PORT_PIN(9, 7)); }
	else return;

	// Reset CTLW0 register to default values
	// (EUSCI_A is in reset state)
	/////////////////////////////////////////
	_EUSCI->CTLW0 = EUSCI_A_CTLW0_SWRST;

	// Configure SMCLK as clock source
	//////////////////////////////////
	_EUSCI->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

	// Configure UART protocol (default 8N1)
	////////////////////////////////////////
	if (bits == _7_BITS) {
		_EUSCI->CTLW0 |= EUSCI_A_CTLW0_SEVENBIT;
	}
	if (par != _NO_PARITY) {
		_EUSCI->CTLW0 |= EUSCI_A_CTLW0_PEN;
		if (par == _EVEN_PARITY) {
			_EUSCI->CTLW0 |= EUSCI_A_CTLW0_PAR;
		}
	}
	if (stop == _2_STOPBITS) {
		_EUSCI->CTLW0 |= EUSCI_A_CTLW0_SPB;
	}

	// Set baud rate (assume SMCLK is 3MHz)
	///////////////////////////////////////
	_EUSCI->BRW = (uint16_t)(48000000 / baud);

	// Disable modulation stages
	////////////////////////////
	_EUSCI->MCTLW &= ~(EUSCI_A_MCTLW_BRS_MASK |
			     	   EUSCI_A_MCTLW_BRF_MASK |
					   EUSCI_A_MCTLW_OS16);

	// Disable interrupts
	/////////////////////
	_EUSCI->IE &= ~(EUSCI_A_IE_RXIE |
					EUSCI_A_IE_TXIE |
					EUSCI_A_IE_STTIE|
					EUSCI_A_IE_TXCPTIE);

	// Configure the digital RX/TX lines
	////////////////////////////////////
	_rx.setSEL(1);
	_tx.setSEL(1);
	_rx.setMode(GPIO::INPUT);
	_tx.setMode(GPIO::OUTPUT);

	// Finally enable EUSCI module
	//////////////////////////////
	_EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
	_config_complete = true;
}

uart_msp432::~uart_msp432() {
	_config_complete = false;
	// Wait for pending operations
	while (_EUSCI->STATW & EUSCI_A_STATW_BUSY);
	// Reset CTLW0 register to default values
	// (EUSCI_A is in reset state)
	/////////////////////////////////////////
	_EUSCI->CTLW0 = EUSCI_A_CTLW0_SWRST;
	// Configure the digital RX/TX lines
	////////////////////////////////////
	_rx.setSEL(0);
	_tx.setSEL(0);
	_rx.setMode(GPIO::INPUT);
	_tx.setMode(GPIO::INPUT);
}

void uart_msp432::putc(char c) {
	if (_config_complete) {
		// Wait until the TX Buffer is empty....
		while( (_EUSCI->IFG & EUSCI_A_IFG_TXIFG) == 0);
		// Transfer single char to TX buffer
		_EUSCI->TXBUF = (uint16_t)c;
	}
}

int uart_msp432::puts(const char *s) {
	unsigned int i, len;
	len = strlen(s);
	if (_config_complete) {
		for (i=0; i < len; i++) {
			// Wait until the TX Buffer is empty....
			while( (_EUSCI->IFG & EUSCI_A_IFG_TXIFG) == 0);
			// Transfer single char to TX buffer
			_EUSCI->TXBUF = (uint16_t)(s[i]);
		}
	}
	return len;
}

char uart_msp432::getc() {
	char c = 0;
	if (_config_complete) {
		// Wait until the RX Buffer is filled....
		while( (_EUSCI->IFG & EUSCI_A_IFG_RXIFG) == 0);
		// Transfer single char from RX buffer
		c = _EUSCI->RXBUF;
	}
	return c;
}

bool uart_msp432::available() {
	return _EUSCI->IFG & EUSCI_A_IFG_RXIFG;
}

