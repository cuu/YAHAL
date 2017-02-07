
#include "uart_msp432.h"
#include "gpio_msp432.h"
#include "yahal_assert.h"

#include <string.h>
#include "msp.h"

extern uint32_t SystemCoreClock;

void (*uart_msp432::_intHandler[4])(char) = {nullptr, nullptr, nullptr, nullptr};

uart_msp432::uart_msp432(EUSCI_A_Type * mod,
		   uint32_t    baud, UART_BITS bits,
		   UART_PARITY par,  UART_STOP stop)
: _init(false), _EUSCI(mod), _baud(baud), _bits(bits),
  _par(par), _stop(stop), _port(0), _rx_pin(0), _tx_pin(0) { }


void uart_msp432::init() {
	// Configure hardware characteristics of the 4 UART modules
	///////////////////////////////////////////////////////////
	if      (_EUSCI==EUSCI_A0) { _port = 1; _rx_pin = 2; _tx_pin = 3; }
	else if (_EUSCI==EUSCI_A1) { _port = 2; _rx_pin = 2; _tx_pin = 3; }
	else if (_EUSCI==EUSCI_A2) { _port = 3; _rx_pin = 2; _tx_pin = 3; }
	else if (_EUSCI==EUSCI_A3) { _port = 9; _rx_pin = 6; _tx_pin = 7; }
	else yahal_assert(false);
    gpio_msp432::inst.setSEL(PORT_PIN(_port,_rx_pin), 1);
    gpio_msp432::inst.setSEL(PORT_PIN(_port,_tx_pin), 1);

	// Reset CTLW0 register to default values
	// (EUSCI_A is in reset state)
	/////////////////////////////////////////
	_EUSCI->CTLW0 = EUSCI_A_CTLW0_SWRST;

	// Configure SMCLK as clock source
	//////////////////////////////////
	_EUSCI->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

	// Configure UART protocol (default 8N1)
	////////////////////////////////////////
	if (_bits == _7_BITS) {
		_EUSCI->CTLW0 |= EUSCI_A_CTLW0_SEVENBIT;
	}
	if (_par != _NO_PARITY) {
		_EUSCI->CTLW0 |= EUSCI_A_CTLW0_PEN;
		if (_par == _EVEN_PARITY) {
			_EUSCI->CTLW0 |= EUSCI_A_CTLW0_PAR;
		}
	}
	if (_stop == _2_STOPBITS) {
		_EUSCI->CTLW0 |= EUSCI_A_CTLW0_SPB;
	}

	// Set baud rate (assume SMCLK is 3MHz)
	///////////////////////////////////////
	_EUSCI->BRW = (uint16_t)(SystemCoreClock / _baud);

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

	// Finally enable EUSCI module
	//////////////////////////////
	_EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
	_init = true;
}

uart_msp432::~uart_msp432() {
	// Wait for pending operations
	while (_EUSCI->STATW & EUSCI_A_STATW_BUSY);
	// Reset CTLW0 register to default values
	// (EUSCI_A is in reset state)
	/////////////////////////////////////////
	_EUSCI->CTLW0 = EUSCI_A_CTLW0_SWRST;
	// De-configure the digital RX/TX lines
	///////////////////////////////////////
    gpio_msp432::inst.setSEL(PORT_PIN(_port,_rx_pin), 0);
    gpio_msp432::inst.setSEL(PORT_PIN(_port,_tx_pin), 0);
}

void uart_msp432::putc(char c) {
    if (!_init) init();
    // Wait until the TX Buffer is empty....
    while( (_EUSCI->IFG & EUSCI_A_IFG_TXIFG) == 0);
    // Transfer single char to TX buffer
    _EUSCI->TXBUF = (uint16_t)c;
}

int uart_msp432::puts(const char *s) {
    unsigned int i, len;
    len = strlen(s);
    if (!_init) init();
    for (i=0; i < len; i++) {
        // Wait until the TX Buffer is empty....
        while( (_EUSCI->IFG & EUSCI_A_IFG_TXIFG) == 0);
        // Transfer single char to TX buffer
        _EUSCI->TXBUF = (uint16_t)(s[i]);
    }
    return len;
}

char uart_msp432::getc() {
    char c = 0;
    if (!_init) init();
    // Wait until the RX Buffer is filled....
    while( (_EUSCI->IFG & EUSCI_A_IFG_RXIFG) == 0);
    // Transfer single char from RX buffer
    c = _EUSCI->RXBUF;
    return c;
}

bool uart_msp432::available() {
    if (!_init) init();
	return _EUSCI->IFG & EUSCI_A_IFG_RXIFG;
}

void uart_msp432::setBaudrate(uint32_t baud) {
    _baud = baud;
//    init();
//    // put uart in reset state to write
//    // baud rate register
//    _EUSCI->CTLW0 |=  EUSCI_A_CTLW0_SWRST;
    _EUSCI->BRW = (uint16_t)(SystemCoreClock / baud);
//    _EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
}

void uart_msp432::attachRxIrq( void (*handler)(char) ) {
    if (!_init) init();
    uint8_t index = (((uint32_t)_EUSCI) >> 10) & 0x3;
    _intHandler[index] = handler;
    _EUSCI->IE = EUSCI_A_IE_RXIE;
    NVIC_EnableIRQ((IRQn_Type)(16 + index));
}

void uart_msp432::handleIrq(EUSCI_A_Type * uart) {
    char c = uart->RXBUF;
    uint8_t index = (((uint32_t)uart) >> 10) & 0x3;
    if (_intHandler[index])
        _intHandler[index](c);
}


// Interrupt handler for EUSCIA0..4
///////////////////////////////////
extern "C" {
void EUSCIA0_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A0);
}
void EUSCIA1_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A1);
}
void EUSCIA2_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A2);
}
void EUSCIA3_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A3);
}
} // extern "C"

