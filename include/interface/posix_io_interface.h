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
//  This file defines the low-level Posix system
//  calls for file I/O (also STDIN and STDOUT).

#ifndef _POSIX_IO_INTERFACE_H_
#define _POSIX_IO_INTERFACE_H_

#include "sys/stat.h"

class posix_io_interface {
public:

    // Read from file
    virtual int _read (int file, char *buf, int len) = 0;

    // Write to file
    virtual int _write (int file, const char *buf, int len) = 0;

    // Open a file
    virtual int _open (const char *name, int flags, int mode) = 0;

    // Close a file
    virtual int _close (int file) = 0;

    // Rename a file
    virtual int _link (char *old_name, char *new_name) = 0;

    // Delete a file
    virtual int _unlink (char *name) = 0;

    // Status of a file
    virtual int _stat (char *name, struct stat *st) = 0;

    // Status of open file
    virtual int _fstat (int file, struct stat *st) = 0;

    // Set file position
    virtual int _lseek (int file, int offset, int whence) = 0;

    // Check for terminal I/O
    virtual int _isatty (int file) = 0;

protected:
    virtual ~posix_io_interface() = default;
};

#endif // _POSIX_IO_INTERFACE_H_
