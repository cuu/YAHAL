#ifndef _UART_MSP432_H_
#define _UART_MSP432_H_

#include <stdint.h>
#include "uart_interface.h"
#include "msp.h"

extern "C" {
void EUSCIA0_UART_IRQHandler(void);
void EUSCIA1_UART_IRQHandler(void);
void EUSCIA2_UART_IRQHandler(void);
void EUSCIA3_UART_IRQHandler(void);
}

class uart_msp432 : public uart_interface {
public:
    uart_msp432(EUSCI_A_Type * mod  = EUSCI_A0, // default: backport UART
                uint32_t       baud = 115200,
                uart_mode_t    mode = UART::BITS_8   |
                                      UART::NO_PARITY |
                                      UART::STOPBITS_1);
    virtual ~uart_msp432();

    // Basic read/write operations on a UART
    bool available() override;
    char getc() override;
    void putc(char c) override;
    int  puts(const char *s);

    void uartMode(uart_mode_t mode) override;

    void setBaudrate(uint32_t) override;

    // Interrupt handling
    void uartAttachIrq (void (*)(char, void*), void *ptr = nullptr) override;
    void uartDetachIrq () override;
    void uartEnableIrq () override;
    void uartDisableIrq() override;

    // The IRQ handlers are our friends :)
    friend void EUSCIA0_UART_IRQHandler(void);
    friend void EUSCIA1_UART_IRQHandler(void);
    friend void EUSCIA2_UART_IRQHandler(void);
    friend void EUSCIA3_UART_IRQHandler(void);

private:
    bool _init;
    void init();

    static void handleIrq(EUSCI_A_Type *);
    static void (*_intHandler[4])(char, void*);
    static void  *_intData[4];

    EUSCI_A_Type  * _EUSCI;
    uint32_t        _baud;
    uart_mode_t     _mode;
    uint8_t         _port;
    uint8_t         _rx_pin;
    uint8_t         _tx_pin;
};

#endif // _UART_MSP432_H_
