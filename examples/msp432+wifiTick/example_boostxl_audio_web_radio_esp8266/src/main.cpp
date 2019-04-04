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
// This program is the ESP8266 part of the web radio example.
// The MSP432 and the ESP826 communicate via 2 interfaces:
//
// The I2C interface is used to control the ESP8266, which is
// running as a I2C slave on the ESP8266 (software implementation).
// The MSP432 can control the ESP8266 using this interface
// (see i2c_commands.h and i2c_device.h/cpp for details).
//
// The SPI interface is used to quickly write MP3 data from
// the ESP8266 to the MSP432. So the ESP8266 is slave and the
// MSP432 is the SPI master.
//

#include "WEB_Radio.h"

WEB_Radio wr;

void setup ( void ) { wr.setup(); }
void loop  ( void ) { wr.loop();  }

