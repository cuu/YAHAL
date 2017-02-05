/*
 * stdio.cpp
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

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

void std_io::redirect_stdin(stdin_interface & std_in) {
	_std_in = &std_in;
}

void std_io::redirect_stdout(stdout_interface & std_out) {
	_std_out= &std_out;
}

void std_io::putc(char c) {
    if (_std_out) _std_out->putc(c);
}

char std_io::getc() {
    return _std_in ? _std_in->getc() : 0;
}

