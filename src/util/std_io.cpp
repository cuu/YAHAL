/*
 * stdio.cpp
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#include <cstdio>
#include "std_io.h"

std_io std_io::inst;

extern "C" {
int _write (int fd, const void *buf, size_t count) {
    (void)(fd);
    for (size_t i=0; i < count; ++i)
        std_io::inst.putc(((const char *)buf)[i]);
    return count;
}

int _read  (int fd, void *buf, size_t count) {
    (void)(fd);
    size_t i=0;
    for (; i < count; ++i) {
        char c = std_io::inst.getc();
        ((char *)buf)[i] = c;
        if (c == '\r') { ++i; break; }
    }
    return i;
}
}

void std_io::redirect_stdin(uart_interface & uart_in, bool echo) {
    _uart_in    = &uart_in;
    _local_echo = echo;
}

void std_io::redirect_stdout(uart_interface & uart_out, bool translate) {
    _uart_out     = &uart_out;
    _translate_nl = translate;
}

void std_io::putc(char c) {
    if (_uart_out) {
        _uart_out->putc(c);
        if (_translate_nl && c=='\n') {
            _uart_out->putc('\r');
        }
    }
}

char std_io::getc() {
    if (_uart_in) {
        char c = _uart_in->getc();
        if (_local_echo) {
            putc(c);
            fflush(stdout);
        }
        return c;
    }
    else
        return 0;
}

