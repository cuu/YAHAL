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
// The MSP432 and the ESP826 communicate via 3 interfaces:
//
// The I2C interface is used to control the ESP8266, which is
// running as a I2C slave on the ESP8266 (software implementation).
// The MSP432 can configure the following items/functions via this
// interface:
//   - WLAN SSID
//   - WLAN Password
//   - The HTTP host (e.g. "wdr-wdr2-aachenundregion.icecast.wdr.de")
//   - The HTTP port (e.g. 80)
//   - The HTTP path (e.g. "/wdr/wdr2/aachenundregion/mp3/128/stream.mp3")
//   - Start the receiving process
//   - Triggering a data transfer by writing the amount of needed bytes
//   - Stop the receiving process
//
// The SPI interface is used to quickly write MP3 data from
// the ESP8266 to the MSP432. So the ESP8266 is master and the
// MSP432 is the SPI client. On MSP432 side, DMA can be used to
// quickly receive the data without using up CPU time.
//
// The GPIO4 pin, which is set by the ESP8266 to signal that
// at least 4KiB bytes are available for sending. This GPIO
// pin can be read by the MSP432 to know when to start a new
// data transfer.

#include "WEB_Radio.h"

WEB_Radio wr;

void setup ( void ) { wr.setup(); }
void loop  ( void ) { wr.loop();  }

