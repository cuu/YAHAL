/*
 * stdio.cpp
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include "posix_io.h"

posix_io posix_io::inst;

// These following low-level Posix methods
// in libc need to be overwritten
extern "C" {

int _read (int file, char *buf, int len) __attribute__ ((used)); 
int _read (int file, char *buf, int len) {
    int count=0;
    char c;
    if (file == STDIN_FILENO) {
        // Handle STDIN
        for (; count < len; ++count) {
             if (posix_io::inst._uart_in) {
                 c = posix_io::inst._uart_in->getc();
                 // Handle local echo
                 if (posix_io::inst._local_echo &&
                     posix_io::inst._uart_out)
                 {
                     posix_io::inst._uart_out->putc(c);
                     fflush(stdout);
                 }
             } else {
                 c = 0;
             }
             // Store character in buffer
             ((char *)buf)[count] = c;
             if (c == '\r') {
                 ++count;
                 break;
             }
         }
    } else {
        // Handle File IO
        if (posix_io::inst._file_io) {
            count = posix_io::inst._file_io->_read(file, buf, len);
        }
    }
    return count;
}

int _write (int file, const char *buf, int len) __attribute__ ((used)); 
int _write (int file, const char *buf, int len) {
    int count = 0;
    if (file == STDOUT_FILENO) {
        // Handle STDOUT
        for (int i=0; i < len; ++i) {
            if (posix_io::inst._uart_out) {
                posix_io::inst._uart_out->putc(buf[i]);
                // Handle CR mode
                if (posix_io::inst._add_CR_out && buf[i]=='\n') {
                    posix_io::inst._uart_out->putc('\r');
                }
            }
        }
        count = len;
    } else if (file == STDERR_FILENO) {
        // Handle STDERR
        // Set color to red (CT100 code)
        if (posix_io::inst._uart_err) {
            // Set red color (VT100 code)
            const char red[]   = "\e[31m";
            const char reset[] = "\e[0m";
            const char * p = red;
            while (*p) posix_io::inst._uart_err->putc(*p++);

            for (int i=0; i < len; ++i) {
                if (posix_io::inst._uart_err) {
                    posix_io::inst._uart_err->putc(buf[i]);
                    // Handle CR mode
                    if (posix_io::inst._add_CR_err && buf[i]=='\n') {
                        posix_io::inst._uart_err->putc('\r');
                    }
                }
            }
            p = reset;
            while (*p) posix_io::inst._uart_err->putc(*p++);
        }
        count = len;
    } else {
        // Handle File IO
        if (posix_io::inst._file_io) {
            count = posix_io::inst._file_io->_write(file, buf, len);
        }
    }
    return count;
}

int _open (const char *name, int flags, int mode) __attribute__ ((used)); 
int _open (const char *name, int flags, int mode) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_open(name, flags, mode);
    } else {
        errno = ENOSYS;
        ret   = -1;
    }
    return ret;
}

int _close (int file) __attribute__ ((used));
int _close (int file) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_close(file);
    } else {
        errno = EBADF;
        ret   = -1;
    }
    return ret;
}

int _link (char *old_name, char *new_name) __attribute__ ((used));
int _link (char *old_name, char *new_name) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_link(old_name, new_name);
    } else {
        errno = EMLINK;
        ret   = -1;
    }
    return ret;
}

int _unlink (char *name) __attribute__ ((used));
int _unlink (char *name) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_unlink(name);
    } else {
        errno = ENOENT;
        ret   = -1;
    }
    return ret;
}

int _stat (char *name, struct stat *st) __attribute__ ((used));
int _stat (char *name, struct stat *st) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_stat(name, st);
    } else {
        st->st_mode = S_IFCHR;
        ret = 0;
    }
    return ret;
}

int _fstat (int file, struct stat *st) __attribute__ ((used));
int _fstat (int file, struct stat *st) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_fstat(file, st);
    } else {
        st->st_mode = S_IFCHR;
        ret = 0;
    }
    return ret;
}

int _lseek (int file, int offset, int whence) __attribute__ ((used));
int _lseek (int file, int offset, int whence) {
    int ret;
    if (posix_io::inst._file_io) {
        ret = posix_io::inst._file_io->_lseek(file, offset, whence);
    } else {
        ret = 0;
    }
    return ret;
}

int _isatty (int file) __attribute__ ((used));
int _isatty (int file) {
    int ret;
    if ((file == STDIN_FILENO ) ||
        (file == STDOUT_FILENO) ||
        (file == STDERR_FILENO)) {
        ret = 1;
    } else {
        if (posix_io::inst._file_io) {
            ret = posix_io::inst._file_io->_isatty(file);
        } else {
            errno = EBADF;
            ret   = -1;
        }
    }
    return ret;
}

int _kill(int pid, int sig) __attribute__ ((used));
int _kill(int pid, int sig) {
    (void)(pid);
    (void)(sig);
    errno = EINVAL;
    return -1;
}

int _getpid(void) __attribute__ ((used));
int _getpid(void) {
    return -1;
}

}

void posix_io::register_stdin(uart_interface & uart_in, bool echo) {
    _uart_in    = &uart_in;
    _local_echo = echo;
    // line-buffering with 100 chars
    setvbuf(stdin, NULL, _IOLBF, 100);
}

void posix_io::register_stdout(uart_interface & uart_out, bool add_CR) {
    _uart_out   = &uart_out;
    _add_CR_out = add_CR;
    // line-buffering with 100 chars
    setvbuf(stdout, NULL, _IOLBF, 100);
}

void posix_io::register_stderr(uart_interface & uart_out, bool add_CR) {
    _uart_err   = &uart_out;
    _add_CR_err = add_CR;
    // line-buffering with 100 chars
    setvbuf(stderr, NULL, _IOLBF, 100);
}

void posix_io::register_fileio(posix_io_interface & file_io) {
    _file_io = & file_io;
}

