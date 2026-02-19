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
#include "usb_uart_device.h"

std::function<void()> usb_uart_device::uart_tx_cb;
std::function<void()> usb_uart_device::uart_rx_cb;

usb_uart_device::usb_uart_device(usb_device_controller &ctrl,
                                 usb_configuration &conf,
                                 uart_interface &uart)
    : usb_cdc_acm_device(ctrl, conf), task("UART ACM task"), _uart(uart) {

    // Disable the UART FIFOs because we have strange problems with them:
    // Testing with a direct UART loopback, the RX interrupts will not be
    // generated when the UART has a full TX FIFO and is sending data all
    // the time. Even polling for received characters does not work.
    // Needs further investigation...
    _uart.enableFIFO(false);

    line_coding_handler = [&](const CDC::line_coding_t &lineCoding) {
        // Handle line code changes
        uart_mode_t mode = 0;
        switch ((int) lineCoding.bDataBits) {
            case 7:
                mode |= UART::BITS_7;
                break;
            case 8:
                mode |= UART::BITS_8;
                break;
            default:
                assert("Wrong number of bits!!" && false);
        }
        switch ((int) lineCoding.bParityType) {
            case (int) CDC::bParityType_t::PARITY_NONE:
                mode |= UART::NO_PARITY;
                break;
            case (int) CDC::bParityType_t::PARITY_EVEN:
                mode |= UART::EVEN_PARITY;
                break;
            case (int) CDC::bParityType_t::PARITY_ODD:
                mode |= UART::ODD_PARITY;
                break;
            default:
                assert("Wrong parity!" && false);
        }
        switch ((int) lineCoding.bCharFormat) {
            case (int) CDC::bCharFormat_t::STOP_BITS_1:
                mode |= UART::STOPBITS_1;
                break;
            case (int) CDC::bCharFormat_t::STOP_BITS_2:
                mode |= UART::STOPBITS_2;
                break;
            default:
                assert("Wrong stop bits!" && false);
        }
        _uart.uartMode(mode);
        _uart.setBaudrate(lineCoding.dwDTERate);
    };

    control_line_handler = ([&](bool dtr, bool rts) {
        // The DTR control line gives us a hint if there
        // is some application consuming the data on host side
        _dtr = dtr;
        // Set signals on hardware level
        _uart.setDTR(dtr);
        _uart.setRTS(rts);
    });

    break_handler = ([&](uint16_t millis) {
        _uart.sendBreak(millis);
    });

    received_handler = ([&]() {
        resume();
    });

    _uart.uartAttachIrq([&](char c) {
        // When DTR is low there might not be any consumer on
        // host side. So simply throw away data in this case.
        if (_tx_buffer.available_put() > 0 && _dtr) {
            _tx_buffer.put(c);
            resume();
        }
    });
}

void usb_uart_device::set_dcd_dtr(bool dcd, bool dsr) {
    CDC::bmUartState_t uart_state;
    uart_state.bRxCarrier_DCD = dcd;
    uart_state.bTxCarrier_DSR = dsr;
    notify_serial_state( uart_state );
}

void usb_uart_device::run() {
    while (true) {
        // Prevent this task from being suspended too early.
        // When a new characters arrive within 5 ms, the task
        // stays in the READY state, and we do not waste time
        // in other tasks.
        uint64_t until = millis() + 5;
        while (millis() < until) {
            if (available() || _tx_buffer.available_get()) break;
        }
        if (!available() && !_tx_buffer.available_get()) suspend();

        // Try to read data from USB host
        size_t len = read(_rx_buffer, UART_TARGET_BUFFER_SIZE);
        if (len) {
            if (uart_rx_cb) uart_rx_cb();
            for(size_t i=0; i < len; ++i) {
                _uart.putc(_rx_buffer[i]);
            }
        }
        // Try to read data from UART
        len = _tx_buffer.available_get();
        if (len && _dtr) {
            if (uart_tx_cb) uart_tx_cb();
            for(size_t i=0; i < len; ++i) {
                _tx_buffer.get(_rx_buffer[i]);
            }
            uint32_t written = 0;
            while (written != len) {
                written += write(_rx_buffer + written, len - written);
            }
        }
    }
}
