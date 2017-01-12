/*
 * stdio.cpp
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#include "std_io.h"
#include <string.h>

stdin_interface  * std_io::_std_in;
stdout_interface * std_io::_std_out;
char               std_io::_buffer[80];

bool std_io::redirect_stdin(stdin_interface & std_in, char * dev) {
	_std_in = &std_in;
	strcpy(_buffer, dev);
	strcat(_buffer, ":");
	if (add_device( dev,  _MSA, uart_open,	uart_close,	 uart_read,
					uart_write,	uart_lseek,	uart_unlink, uart_rename)) {
		return false;
	}
	if (!freopen(_buffer, "r", stdin)) {
		return false;
	}
	// Configure buffering for stdin
	setvbuf(stdin , _buffer, _IOFBF, 80);
	return true;
}

bool std_io::redirect_stdout(stdout_interface & std_out, char * dev) {
	_std_out= &std_out;
	strcpy(_buffer, dev);
	strcat(_buffer, ":");
	if (add_device( dev,  _MSA, uart_open,	uart_close,	 uart_read,
					uart_write,	uart_lseek,	uart_unlink, uart_rename)) {
		return false;
	}
	if (!freopen(_buffer, "w", stdout)) {
		return false;
	}
	// Configure buffering for stdout
	setvbuf(stdout, NULL, _IONBF,  0);
	return true;
}

int std_io::uart_open(const char *path, unsigned flags, int llv_fd) {
	return 0;
}

int std_io::uart_close(int dev_fd) {
	return 0;
}

int std_io::uart_read(int dev_fd, char *buf, unsigned count) {
	unsigned int i;
	int ret = 0; // count how many chars have been entered
	for (i=0; i < count; ++i) {
		char c = _std_in->getc();
		if (c=='\r') c='\n'; // <ENTER> is a '\n'
		buf[i] = c;
		ret++;
		// Console Echo
		if (_std_out) {
			_std_out->putc(c);
			if (c=='\n') {
				_std_out->putc('\r'); // add a CR
				break;
			}
		}
	}
	return ret;
}

int std_io::uart_write(int dev_fd, const char *buf, unsigned count){
	unsigned int i;
	for (i=0; i < count; ++i) {
		_std_out->putc(buf[i]);
		if (buf[i] == '\n') {
			_std_out->putc('\r'); // add a CR
		}
	}
	return count;
}

fpos_t std_io::uart_lseek(int dev_fd, off_t ioffset, int origin){
	return 0;
}

int std_io::uart_unlink(const char * path){
	return 0;
}

int std_io::uart_rename(const char *old_name, const char *new_name){
	return 0;
}
