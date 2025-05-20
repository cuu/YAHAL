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
#include "floppy_logger.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cstdlib>

namespace FLOPPY {

    log log::inst;

    void log::print(const char *file, int line, log_level l, const char *fmt, ...) {
        char *buffer = _buffer;
        const char *p;
        // Check the level
        if (l > log::_level) return;
        // Add level string
        strcpy(buffer, _level_str[l]);
        buffer += strlen(buffer);
        // Add user message
        va_list args;
        va_start(args, fmt);
        for (p = fmt; *p; ++p) {
            if (*p != '%') {
                strncat(buffer, p, 1);
            } else {
                switch (*++p) {
                    /* string */
                    case 's': {
                        strcpy(buffer, "\"");
                        strcat(buffer, va_arg(args, char *));
                        strcat(buffer, "\"");
                        break;
                    }
                        // integer base 10
                    case 'd': {
                        itoa(va_arg(args, int), buffer, 10);
                        break;
                    }
                        // integer base 16
                    case 'x': {
                        itoa(va_arg(args, int), buffer, 16);
                        break;
                    }
                        // boolean
                    case 'b': {
                        if (va_arg(args, int)) {
                            strcpy(buffer, "true");
                        } else {
                            strcpy(buffer, "false");
                        }
                        break;
                    }
                    default:
                        strncat(buffer, p, 1);
                }
            }
            buffer += strlen(buffer);
        }
        va_end  (args);
        // Add line and filename
        strcat(buffer, " (");
        strcat(buffer, file);
        strcat(buffer, ":");
        buffer += strlen(buffer);
        itoa(line, buffer, 10);
        strcat(buffer, ")");
        // Finally print message
        puts(_buffer);
    }

}