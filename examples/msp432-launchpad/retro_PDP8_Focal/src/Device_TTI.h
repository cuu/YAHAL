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
// The Teletype input class.
//

#ifndef DEVICETTI_H_
#define DEVICETTI_H_
#include "Device_Base.h"
#include "uart_interface.h"

class Device_TTI : public Device_Base {
public:

    Device_TTI(uart_interface & uart) : FLAG(false), c(0), _uart(uart) { };
    unsigned short getDeviceNumber();
    void processPulse(unsigned int pulse, CPU & cpu);
    void cycle();
    void clearFlag();
    bool intRequest();

    virtual ~Device_TTI() { }

private:
    char toUpper(char c);
    bool FLAG;
    int  c;
    uart_interface & _uart;
};

#endif /* DEVICETTI_H_ */
