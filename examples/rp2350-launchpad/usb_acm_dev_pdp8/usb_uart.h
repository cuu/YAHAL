//
// Created by andreas on 04.02.25.
//

#ifndef USB_ACM_DEV_PDP8_USB_UART_H
#define USB_ACM_DEV_PDP8_USB_UART_H

#include "uart_interface.h"
#include "usb_cdc_acm_device.h"

class usb_uart : public uart_interface {
public:
    usb_uart(usb_cdc_acm_device & acm_device);

    // No copy, no assignment
    usb_uart(const usb_uart &) = delete;
    usb_uart & operator= (const usb_uart &) = delete;

    // Check if a character is available for reading.
    bool available() override {
        return _acm_device.available();
    };

    // get a character
    char getc() override {
        _acm_device.read(&_c, 1);
        return _c;
    }

    // write/send a character
    void putc(char c) override {
        _acm_device.write((uint8_t *)&c, 1);
    };

    int puts(const char *s);

    // set the uart mode
    void uartMode(uart_mode_t) override { }

    // set the baudrate in Hz
    void setBaudrate(uint32_t) override { };

    // send a break condition for ms milliseconds.
    // A value of 0xffff means indefinitely 'on',
    // a value of 0 means immediate 'off'
    void sendBreak(uint16_t) override { };

    // set hw control lines
    void setDTR(bool) override { }
    void setRTS(bool) override { }

    // Interrupt handling
    void uartAttachIrq (function<void(char)>) override { }
    void uartDetachIrq () override { }
    void uartEnableIrq () override { }
    void uartDisableIrq() override { }

private:

    // USB CDC ACM device
    usb_cdc_acm_device & _acm_device;
    uint8_t _c {0};
};

#endif //USB_ACM_DEV_PDP8_USB_UART_H
