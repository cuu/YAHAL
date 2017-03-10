/*
 * stdio.h
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _STD_IO_H_
#define _STD_IO_H_

#include "stdin_interface.h"
#include "stdout_interface.h"
#include <stddef.h>

// These methods in libc need to be overwritten
extern "C" {
int _write (int fd, const void *buf, size_t count);
int _read  (int fd,       void *buf, size_t count);
}

class std_io : public stdin_interface, public stdout_interface {
  public:
    static std_io inst;

    void putc(char c);
    char getc();

    void redirect_stdin (stdin_interface  & std_in , bool local_echo=true);
    void redirect_stdout(stdout_interface & std_out, bool translate_nl=true);

  private:
    std_io() : _std_in(nullptr), _std_out(nullptr) { }

    stdin_interface *  _std_in;
    stdout_interface * _std_out;
    bool               _local_echo;
    bool               _translate_nl;
};

#endif // _STDIO_H_
