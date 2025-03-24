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
//  Receiver/Transmitter) control.

#ifndef _UART_CTRL_INTERFACE_H_
#define _UART_CTRL_INTERFACE_H_

#include <cstdint>

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
class uart_ctrl_interface {
public:
    // set the uart mode
    virtual void uartMode(uart_mode_t mode) = 0;

    // set the baudrate in Hz
    virtual void setBaudrate(uint32_t) = 0;

    // send a break condition for ms milliseconds.
    // A value of 0xffff means indefinitely 'on',
    // a value of 0 means immediate 'off'
    virtual void sendBreak(uint16_t ms) = 0;

    // set hw control lines
    virtual void setDTR(bool dtr) = 0;
    virtual void setRTS(bool rts) = 0;

protected:
    virtual ~uart_ctrl_interface() = default;
};

#endif /* _UART_CTRL_INTERFACE_H_ */
