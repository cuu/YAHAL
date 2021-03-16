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
//  This file defines a generic and abstract C++
//  interface for a UART (Universal Asynchronous
//  Receiver/Transmitter).

#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

#include <cstdint>
#include <functional>
using std::function;

typedef uint16_t uart_mode_t;

namespace UART {
const uart_mode_t  BITS_7       = 0x0001;
const uart_mode_t  BITS_8       = 0x0002;
const uart_mode_t  NO_PARITY    = 0x0004;
const uart_mode_t  EVEN_PARITY  = 0x0008;
const uart_mode_t  ODD_PARITY   = 0x0010;
const uart_mode_t  STOPBITS_1   = 0x0020;
const uart_mode_t  STOPBITS_2   = 0x0040;
}

class uart_interface {
public:
    // Check if a character is available for reading.
    virtual bool available() = 0;

    // get a character
    virtual char getc() = 0;

    // write/send a character
    virtual void putc(char c) = 0;

    // set the uart mode
    virtual void uartMode(uart_mode_t mode) = 0;

    // set the baudrate in Hz
    virtual void setBaudrate(uint32_t) = 0;

    // Interrupt handling
    virtual void uartAttachIrq (function<void(char c)> f) = 0;
    virtual void uartDetachIrq () = 0;
    virtual void uartEnableIrq () = 0;
    virtual void uartDisableIrq() = 0;

protected:
    virtual ~uart_interface() = default;
};

#endif /* _UART_INTERFACE_H_ */
