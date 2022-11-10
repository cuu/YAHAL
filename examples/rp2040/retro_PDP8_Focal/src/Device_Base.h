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
// The base class for all devices.
//

#ifndef DEVICEBASE_H_
#define DEVICEBASE_H_
class CPU;

class Device_Base {

public:
    // get the 6-bit wide device number
    virtual unsigned short getDeviceNumber() = 0;
    // process a pulse
    virtual void processPulse(unsigned int pulse, CPU & cpu) = 0;
    // Trigger the device-internal state machine
    virtual void cycle() = 0;
    // Clear the I/O flag
    virtual void clearFlag() = 0;
    // return interrupt request state
    virtual bool intRequest() = 0;
    virtual ~Device_Base() { }
};

#endif /* DEVICEBASE_H_ */
