//
// Created by andreas on 04.02.25.
//

#include "usb_uart.h"

usb_uart::usb_uart(usb_cdc_acm_device & acm_device)
: _acm_device(acm_device) {
}

int usb_uart::puts(const char *s) {
    int len = 0;
    while(*s) {
        putc(*s++);
        len++;
    }
    return len;
}
