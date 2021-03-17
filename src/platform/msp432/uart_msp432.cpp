
#include "uart_msp432.h"
#include "gpio_msp432.h"
#include "yahal_assert.h"
#include "irq_dispatcher.h"

#include <string.h>
#include "msp.h"

// If existing, use the global SubsystemMasterClock. If not, use our own
// copy of the SystemCoreClock, assuming that MCLK equals SMCLK ...
uint32_t UART_CLK = SystemCoreClock;
extern uint32_t SubsystemMasterClock __attribute__((weak,alias("UART_CLK")));


function<void(char)> uart_msp432::_intHandler[4] = {nullptr, nullptr, nullptr, nullptr};

uart_msp432::uart_msp432(EUSCI_A_Type * module, uint32_t baud,uart_mode_t mode)
: _init(false), _EUSCI(module), _baud(baud), _mode(mode),
  _port(0), _rx_pin(0), _tx_pin(0) {
    // make sure the irq_dispatcher gets linked in
    irq_dispatcher::link_in();
}

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

    // put EUSCI module in reset state
    //////////////////////////////////
    _EUSCI->CTLW0 = EUSCI_A_CTLW0_SWRST;

    // Configure SMCLK as clock source
    //////////////////////////////////
    _EUSCI->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

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

    // Configure UART protocol (default 8N1)
    ////////////////////////////////////////
    uartMode(_mode);

    // Set baud rate
    ////////////////
    setBaudrate(_baud);

    _init = true;
}

uart_msp432::~uart_msp432() {
    // Check if we need to de-configure
    if (!_init) return;
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

bool uart_msp432::available() {
    if (!_init) init();
    return _EUSCI->IFG & EUSCI_A_IFG_RXIFG;
}

char uart_msp432::getc() {
    if (!_init) init();
    // Wait until the RX Buffer is filled....
    while( (_EUSCI->IFG & EUSCI_A_IFG_RXIFG) == 0);
    // Transfer single char from RX buffer
    return _EUSCI->RXBUF;;
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
    for (i=0; i < len; i++) putc(s[i]);
    return len;
}

void uart_msp432::uartMode(uart_mode_t mode) {
    _mode = mode;

    // put module in reset state
    _EUSCI->CTLW0 |= EUSCI_A_CTLW0_SWRST;

    if (mode & UART::BITS_7) {
        _EUSCI->CTLW0 |= EUSCI_A_CTLW0_SEVENBIT;
    }
    if (mode & UART::BITS_8) {
        _EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_SEVENBIT;
    }
    if (mode & UART::NO_PARITY) {
        _EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_PEN;
    }
    if (mode & UART::EVEN_PARITY) {
        _EUSCI->CTLW0 |= EUSCI_A_CTLW0_PEN;
        _EUSCI->CTLW0 |= EUSCI_A_CTLW0_PAR;
    }
    if (mode & UART::ODD_PARITY) {
        _EUSCI->CTLW0 |=  EUSCI_A_CTLW0_PEN;
        _EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_PAR;
    }
    if (mode & UART::STOPBITS_1) {
        _EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_SPB;
    }
    if (mode & UART::STOPBITS_2) {
        _EUSCI->CTLW0 |= EUSCI_A_CTLW0_SPB;
    }

    // enable the UART module again
    _EUSCI->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
}

void uart_msp432::setBaudrate(uint32_t baud) {
    _baud = baud;
    _EUSCI->BRW = (uint16_t)(SubsystemMasterClock / baud);
}

void uart_msp432::uartAttachIrq(function<void(char)> f) {
    if (!_init) init();
    uint8_t index = (((uint32_t)_EUSCI) >> 10) & 0x3;
    _intHandler[index] = f;
    _EUSCI->IE = EUSCI_A_IE_RXIE;
    NVIC_EnableIRQ((IRQn_Type)(16 + index));
}

void uart_msp432::uartDetachIrq () {
    if (!_init) init();
    uint8_t index = (((uint32_t)_EUSCI) >> 10) & 0x3;
    _EUSCI->IE = 0;
    NVIC_DisableIRQ((IRQn_Type)(16 + index));
    _intHandler[index] = nullptr;
}

void uart_msp432::uartEnableIrq () {
    _EUSCI->IE = EUSCI_A_IE_RXIE;
}

void uart_msp432::uartDisableIrq() {
    _EUSCI->IE = 0;
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
void EUSCIA0_UART_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A0);
}
void EUSCIA1_UART_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A1);
}
void EUSCIA2_UART_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A2);
}
void EUSCIA3_UART_IRQHandler(void) {
    uart_msp432::handleIrq(EUSCI_A3);
}
} // extern "C"

