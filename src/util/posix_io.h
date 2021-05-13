/*
 * stdio.h
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _POSIX_IO_H_
#define _POSIX_IO_H_

#include "posix_io_interface.h"
#include "uart_interface.h"

class posix_io {
public:
    // Posix IO is a singleton
    static posix_io inst;

    void register_stdin (uart_interface     & uart_in , bool local_echo=true);
    void register_stdout(uart_interface     & uart_out, bool add_CR=true);
    void register_stderr(uart_interface     & uart_out, bool add_CR=true);
    void register_fileio(posix_io_interface & file_io);

private:
    posix_io()
    : _uart_in(nullptr),  _uart_out(nullptr), _uart_err(nullptr),
      _file_io(nullptr),  _local_echo(false),
      _add_CR_out(false), _add_CR_err(false) {
    }

public:
    uart_interface *        _uart_in;
    uart_interface *        _uart_out;
    uart_interface *        _uart_err;
    posix_io_interface *    _file_io;
    bool                    _local_echo;
    bool                    _add_CR_out;
    bool                    _add_CR_err;
};

#endif // _POSIX_IO_H_
