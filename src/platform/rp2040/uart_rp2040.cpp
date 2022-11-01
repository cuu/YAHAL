
#include "uart_rp2040.h"
#include "gpio_rp2040.h"
#include "yahal_assert.h"
#include <cstring>

using namespace _IO_BANK0_;
using namespace _RESETS_;
using namespace _UART0_;
using namespace _UART1_;

function<void(char)> uart_rp2040::_intHandler[2];

uart_rp2040::uart_rp2040(uint8_t index,
                         gpio_pin_t  tx_pin, gpio_pin_t  rx_pin,
                         uint32_t    baud,   uart_mode_t mode)
: _init(false),    _index(index), _tx_pin(tx_pin),
  _rx_pin(rx_pin), _baud(baud),   _mode(mode) {

    yahal_assert(index < 2);
    bool tx_found = false;
    bool rx_found = false;
    for (int tx = 0; tx < 4; ++tx) {
        if (tx_pin == _uart_tx_pins[index][tx]) {
            tx_found = true;
            break;
        }
    }
    for (int rx = 0; rx < 4; ++rx) {
        if (rx_pin == (_uart_tx_pins[index][rx]+1)) {
            rx_found = true;
            break;
        }
    }
    yahal_assert(tx_found && rx_found);
}

void uart_rp2040::init() {
    // Take UART out of reset state
    if (_index)  RESETS.RESET.uart1 = 0;
    else         RESETS.RESET.uart0 = 0;
    // Configure GPIO pins
    gpio_rp2040::inst.setSEL( _tx_pin, GPIO0_CTRL_FUNCSEL__uart0_tx);
    gpio_rp2040::inst.setSEL( _rx_pin, GPIO0_CTRL_FUNCSEL__uart0_tx);
    // Configure UART protocol (default 8N1)
    uartMode(_mode);
    // Set baud rate
    setBaudrate(_baud);
    // Enable UART
    UART0_SET.UARTCR.UARTEN = 1;
    _init = true;
    // Enable FIFOs
    UART0_SET.UARTLCR_H.FEN = 1;
}

uart_rp2040::~uart_rp2040() {
//    // Check if we need to de-configure
//    if (!_init) return;
//    // Wait for pending operations
//    while (_EUSCI->STATW & EUSCI_A_STATW_BUSY);
//    // Reset CTLW0 register to default values
//    // (EUSCI_A is in reset state)
//    /////////////////////////////////////////
//    _EUSCI->CTLW0 = EUSCI_A_CTLW0_SWRST;
//    // De-configure the digital RX/TX lines
//    ///////////////////////////////////////
//    gpio_rp2040::inst.setSEL(PORT_PIN(_port,_rx_pin), 0);
//    gpio_rp2040::inst.setSEL(PORT_PIN(_port,_tx_pin), 0);
}

bool uart_rp2040::available() {
    if (!_init) init();
    return !UART0.UARTFR.RXFE;
}

char uart_rp2040::getc() {
    if (!_init) init();
    // Wait until the RX Buffer is filled....
    while( (UART0.UARTFR.RXFE) != 0) ;
    // Transfer single char from RX buffer
    return UART0.UARTDR.DATA;
}

void uart_rp2040::putc(char c) {
    if (!_init) init();
    // Wait until the TX FIFO is empty....
    while( (UART0.UARTFR.TXFE) == 0) ;
    // Transfer single char to TX buffer
    UART0.UARTDR.DATA = (uint16_t)c;
}

int uart_rp2040::puts(const char *s) {
    unsigned int i, len;
    len = strlen(s);
    for (i=0; i < len; i++) putc(s[i]);
    return len;
}

void uart_rp2040::uartMode(uart_mode_t mode) {
    _mode = mode;

    if (mode & UART::BITS_7) {
        UART0.UARTLCR_H.WLEN = 2;
    }
    if (mode & UART::BITS_8) {
        UART0.UARTLCR_H.WLEN = 3;
    }
    if (mode & UART::NO_PARITY) {
        UART0.UARTLCR_H.PEN = 0;
    }
    if (mode & UART::EVEN_PARITY) {
        UART0.UARTLCR_H.PEN = 0;
        UART0.UARTLCR_H.EPS = 1;
    }
    if (mode & UART::ODD_PARITY) {
        UART0.UARTLCR_H.PEN = 0;
        UART0.UARTLCR_H.EPS = 0;
    }
    if (mode & UART::STOPBITS_1) {
        UART0.UARTLCR_H.STP2 = 0;
    }
    if (mode & UART::STOPBITS_2) {
        UART0.UARTLCR_H.STP2 = 1;
    }
}

void uart_rp2040::setBaudrate(uint32_t baud) {
    _baud = baud;
    uint32_t baud_div = (8*125000000) / _baud;
    UART0.UARTIBRD = (baud_div >> 7);
    UART0.UARTFBRD = ((baud_div & 0x7f) + 1) / 2;
    // dummy write
    UART0_SET.UARTLCR_H = 0;
}

void uart_rp2040::uartAttachIrq(function<void(char)> f) {
//    if (!_init) init();
//    uint8_t index = (((uint32_t)_EUSCI) >> 10) & 0x3;
//    _intHandler[index] = f;
//    _EUSCI->IE = EUSCI_A_IE_RXIE;
//    NVIC_EnableIRQ((IRQn_Type)(16 + index));
}

void uart_rp2040::uartDetachIrq () {
//    if (!_init) init();
//    uint8_t index = (((uint32_t)_EUSCI) >> 10) & 0x3;
//    _EUSCI->IE = 0;
//    NVIC_DisableIRQ((IRQn_Type)(16 + index));
//    _intHandler[index] = nullptr;
}

void uart_rp2040::uartEnableIrq () {
//    _EUSCI->IE = EUSCI_A_IE_RXIE;
}

void uart_rp2040::uartDisableIrq() {
//    _EUSCI->IE = 0;
}

void uart_rp2040::handleIrq() {
//    char c = uart->RXBUF;
//    uint8_t index = (((uint32_t)uart) >> 10) & 0x3;
//    if (_intHandler[index])
//        _intHandler[index](c);
}


// Interrupt handler for EUSCIA0..4
///////////////////////////////////
extern "C" {
//void EUSCIA0_UART_IRQHandler(void) {
//    uart_rp2040::handleIrq(EUSCI_A0);
//}
//void EUSCIA1_UART_IRQHandler(void) {
//    uart_rp2040::handleIrq(EUSCI_A1);
//}
//void EUSCIA2_UART_IRQHandler(void) {
//    uart_rp2040::handleIrq(EUSCI_A2);
//}
//void EUSCIA3_UART_IRQHandler(void) {
//    uart_rp2040::handleIrq(EUSCI_A3);
//}
} // extern "C"

