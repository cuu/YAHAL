// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
// UART driver for RP2350.
//
#ifndef _UART_RP2350_H_
#define _UART_RP2350_H_

#include <cstdint>
#include "gpio_interface.h"
#include "uart_interface.h"
#include "RP2350.h"

using namespace _UART0_;
using namespace _UART1_;

extern "C" {
void UART0_IRQ_Handler(void);
void UART1_IRQ_Handler(void);
}

class uart_rp2350 : public uart_interface {
public:
    uart_rp2350(uint8_t     index  = 1, // default: back channel UART
                gpio_pin_t  tx_pin = 26,
                gpio_pin_t  rx_pin = 27,
                uint32_t    baud = 115200,
                uart_mode_t mode = UART::BITS_8   |
                                   UART::NO_PARITY |
                                   UART::STOPBITS_1);
    virtual ~uart_rp2350();

    // Basic read/write operations on a UART
    bool available() override;
    char getc() override;
    void putc(char c) override;
    int  puts(const char *s);

    void uartMode(uart_mode_t mode) override;

    void setBaudrate(uint32_t) override;

    // Interrupt handling
    void uartAttachIrq (function<void(char)> f) override;
    void uartDetachIrq () override;
    void uartEnableIrq () override;
    void uartDisableIrq() override;

    // The IRQ handlers are our friends :)
    friend void UART0_IRQ_Handler(void);
    friend void UART1_IRQ_Handler(void);

private:
    bool _init;
    void init();

    static int8_t _uart_tx_pins[2][6];

    static function<void(char)> _intHandler[2];

    UART0_t *       _uart;
    UART0_t *       _uart_set;
    UART0_t *       _uart_clr;
    int             _index;
    uint8_t         _tx_pin;
    uint8_t         _rx_pin;
    uint32_t        _baud;
    uart_mode_t     _mode;
};

#endif // _UART_RP2350_H_
