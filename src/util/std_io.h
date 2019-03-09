/*
 * stdio.h
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _STD_IO_H_
#define _STD_IO_H_

#include "uart_interface.h"
#include <stddef.h>

// These methods in libc need to be overwritten
extern "C" {
int _write (int fd, const void *buf, size_t count);
int _read  (int fd,       void *buf, size_t count);
}

class std_io : public uart_interface {
public:
    static std_io inst;

    char getc() override;
    void putc(char c) override;

    bool available() override { return false; }
    void uartMode(uart_mode_t) override {}
    void setBaudrate(uint32_t) override {}

    // Interrupt handling
    void uartAttachIrq (void (*)(char, void *), void *) override {};
    void uartDetachIrq () override {};
    void uartEnableIrq () override {};
    void uartDisableIrq() override {};

    void redirect_stdin (uart_interface & uart_in , bool local_echo=true);
    void redirect_stdout(uart_interface & uart_out, bool add_CR=true);

private:
    std_io()
    : _uart_in(nullptr),  _uart_out(nullptr),
      _local_echo(false), _add_CR(false) { }

    uart_interface *  _uart_in;
    uart_interface *  _uart_out;
    bool              _local_echo;
    bool              _add_CR;
};

#endif // _STDIO_H_
