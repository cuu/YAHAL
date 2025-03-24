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
//  Receiver/Transmitter) data communication.

#ifndef _UART_DATA_INTERFACE_H_
#define _UART_DATA_INTERFACE_H_

#include <functional>
using std::function;

class uart_data_interface {
public:
    // Check if a character is available for reading.
    virtual bool available() = 0;

    // get a character
    virtual char getc() = 0;

    // write/send a character
    virtual void putc(char c) = 0;

    // Interrupt handling
    virtual void uartAttachIrq (function<void(char)> f) = 0;
    virtual void uartDetachIrq () = 0;
    virtual void uartEnableIrq () = 0;
    virtual void uartDisableIrq() = 0;

protected:
    virtual ~uart_data_interface() = default;
};

#endif /* _UART_DATA_INTERFACE_H_ */
