
#include "uart_rp2040.h"
#include "gpio_rp2040.h"
#include "yahal_assert.h"
#include <cstring>

using namespace _IO_BANK0_;
using namespace _RESETS_;

function<void(char)> uart_rp2040::_intHandler[2];

int8_t uart_rp2040::_uart_tx_pins[2][5] =
    { { 0, 12, 16, 28 }, { 4,  8, 20, 24 } };

uart_rp2040::uart_rp2040(uint8_t index,
                         gpio_pin_t  tx_pin, gpio_pin_t  rx_pin,
                         uint32_t    baud,   uart_mode_t mode)
: _init(false),    _index(index), _tx_pin(tx_pin),
  _rx_pin(rx_pin), _baud(baud),   _mode(mode) {

    yahal_assert(index < 2);
    _uart     = (index==0) ? &UART0     : &UART1;
    _uart_set = (index==0) ? &UART0_SET : &UART1_SET;
    _uart_clr = (index==0) ? &UART0_CLR : &UART1_CLR;
    bool tx_found = false;
    bool rx_found = false;
    for (int i = 0; i < 4; ++i) {
        if (tx_pin ==  _uart_tx_pins[index][i])    tx_found = true;
        if (rx_pin == (_uart_tx_pins[index][i]+1)) rx_found = true;
    }
    yahal_assert(tx_found && rx_found);
}

void uart_rp2040::init() {
    // Take UART out of reset state
    if (_index)  RESETS_CLR.RESET.uart1 = 1;
    else         RESETS_CLR.RESET.uart0 = 1;
    // Configure GPIO pins
    gpio_rp2040::inst.setSEL( _tx_pin, GPIO0_CTRL_FUNCSEL__uart0_tx);
    gpio_rp2040::inst.setSEL( _rx_pin, GPIO1_CTRL_FUNCSEL__uart0_rx);
    // Configure UART protocol (default 8N1)
    uartMode(_mode);
    // Set baud rate
    setBaudrate(_baud);
    // Enable UART & FIFOs
    _uart_set->UARTCR.UARTEN = 1;
    _uart_set->UARTLCR_H.FEN = 1;
    _init = true;
}

uart_rp2040::~uart_rp2040() {
    // Check if we need to de-configure
    if (!_init) return;
    // Wait for pending operations
    while( (_uart->UARTFR.TXFE) == 0) ;
    // Reset UART
    if (_index)  RESETS_SET.RESET.uart1 = 1;
    else         RESETS_SET.RESET.uart0 = 1;
    // De-configure the digital RX/TX lines
    gpio_rp2040::inst.setSEL(_rx_pin, GPIO0_CTRL_FUNCSEL__null);
    gpio_rp2040::inst.setSEL(_tx_pin, GPIO0_CTRL_FUNCSEL__null);
}

bool uart_rp2040::available() {
    if (!_init) init();
    return !_uart->UARTFR.RXFE;
}

char uart_rp2040::getc() {
    if (!_init) init();
    // Wait until the RX Buffer is filled....
    while( (_uart->UARTFR.RXFE) != 0) ;
    // Transfer single char from RX buffer
    return _uart->UARTDR.DATA;
}

void uart_rp2040::putc(char c) {
    if (!_init) init();
    // Wait until the TX FIFO is empty....
    while( (_uart->UARTFR.TXFE) == 0) ;
    // Transfer single char to TX buffer
    _uart->UARTDR.DATA = (uint16_t)c;
}

int uart_rp2040::puts(const char *s) {
    unsigned int len = 0;
    while(*s) {
        putc(*s++);
        len++;
    }
    return len;
}

void uart_rp2040::uartMode(uart_mode_t mode) {
    _mode = mode;

    if (mode & UART::BITS_7) {
        _uart->UARTLCR_H.WLEN = 2;
    }
    if (mode & UART::BITS_8) {
        _uart->UARTLCR_H.WLEN = 3;
    }
    if (mode & UART::NO_PARITY) {
        _uart->UARTLCR_H.PEN = 0;
    }
    if (mode & UART::EVEN_PARITY) {
        _uart->UARTLCR_H.PEN = 0;
        _uart->UARTLCR_H.EPS = 1;
    }
    if (mode & UART::ODD_PARITY) {
        _uart->UARTLCR_H.PEN = 0;
        _uart->UARTLCR_H.EPS = 0;
    }
    if (mode & UART::STOPBITS_1) {
        _uart->UARTLCR_H.STP2 = 0;
    }
    if (mode & UART::STOPBITS_2) {
        _uart->UARTLCR_H.STP2 = 1;
    }
}

void uart_rp2040::setBaudrate(uint32_t baud) {
    _baud = baud;
    uint32_t baud_div = (8*125000000) / _baud;
    _uart->UARTIBRD =  (baud_div >> 7);
    _uart->UARTFBRD = ((baud_div & 0x7f) + 1) / 2;
    // dummy write
    _uart_set->UARTLCR_H = 0;
}

void uart_rp2040::uartAttachIrq(function<void(char)> f) {
    if (!_init) init();
    _intHandler[_index] = f;
    // Enable RX interrupt
    _uart_set->UARTIMSC.RTIM = 1;
    // Enable NVIC interrupt
    NVIC_EnableIRQ((IRQn_Type)(UART0_IRQ_IRQn + _index));
}

void uart_rp2040::uartDetachIrq () {
    if (!_init) init();
    // Disable NVIC interrupt
    NVIC_DisableIRQ((IRQn_Type)(UART0_IRQ_IRQn + _index));
    // Disable RX interrupt
    _uart_clr->UARTIMSC.RTIM = 1;
    // Clear pending interrupts
    _uart_set->UARTICR.RXIC = 1;
    // Clear handler
    _intHandler[_index] = nullptr;
}

void uart_rp2040::uartEnableIrq () {
    _uart_set->UARTIMSC.RTIM = 1;
}

void uart_rp2040::uartDisableIrq() {
    _uart_clr->UARTIMSC.RTIM = 1;
}

// Interrupt handler for UART0/1
////////////////////////////////
extern "C" {

void UART0_IRQ_Handler(void) {
    uart_rp2040::_intHandler[0]( UART0.UARTDR.DATA );
}

void UART1_IRQ_Handler(void) {
    uart_rp2040::_intHandler[1]( UART1.UARTDR.DATA );
}

} // extern "C"

