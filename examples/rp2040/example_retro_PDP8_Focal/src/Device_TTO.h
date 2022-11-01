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
// The Teletype output class.
//

#ifndef DEVICETTO_H_
#define DEVICETTO_H_
#include "Device_Base.h"
#include "uart_interface.h"


class Device_TTO : public Device_Base {
public:

    Device_TTO(uart_interface & uart) : FLAG(false), _uart(uart) { }
    unsigned short getDeviceNumber();
    void processPulse(unsigned int pulse, CPU & cpu);
    void cycle();
    void clearFlag();
    bool intRequest();

    virtual ~Device_TTO() { }

private:
    bool FLAG;
    uart_interface & _uart;
};

#endif /* DEVICETTO_H_ */
