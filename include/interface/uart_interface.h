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
//  Receiver/Transmitter) data communication and
//  UART control.

#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

#include "uart_data_interface.h"
#include "uart_ctrl_interface.h"

class uart_interface : public uart_data_interface,
                       public uart_ctrl_interface {
protected:
    ~uart_interface() override = default;
};

#endif /* _UART_INTERFACE_H_ */
