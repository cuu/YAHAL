/*
 * stdio.h
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _STD_IO_H_
#define _STD_IO_H_

#include <stdio.h>
#include <file.h>

#include "stdin_interface.h"
#include "stdout_interface.h"

class std_io {
  public:

	static bool redirect_stdin (stdin_interface  & std_in,  char * devName);
	static bool redirect_stdout(stdout_interface & std_out, char * devName);

  private:
	std_io() {
		_std_in = 0;
		_std_out = 0;
	}
	static stdin_interface *  _std_in;
	static stdout_interface * _std_out;
	static char _buffer[80];

	static int		uart_open  (const char *path, unsigned flags, int llv_fd);
	static int		uart_close (int dev_fd);
	static int		uart_read  (int dev_fd, char *buf, unsigned count);
	static int		uart_write (int dev_fd, const char *buf, unsigned count);
	static fpos_t	uart_lseek (int dev_fd, off_t ioffset, int origin);
	static int		uart_unlink(const char *path);
	static int		uart_rename(const char *old_name, const char *new_name);
};

#endif // _STDIO_H_
