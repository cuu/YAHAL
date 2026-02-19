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
// This file defines the hardware components
// on the wifiTick board, when used with a
// RP2350 Launchpad.
//
#ifndef _RP2350_LAUNCHPAD_WIFITICK_H_
#define _RP2350_LAUNCHPAD_WIFITICK_H_

// SPI interface
#define TICK_SPI_MOSI   3
#define TICK_SPI_MISO   4
#define TICK_SPI_CS     5
#define TICK_SPI_CLK    6

// Reset line
#define TICK_nRESET     7

// GPIOs also used for I2C
// (no HW support on ESP8266)
#define TICK_GPIO0      8
#define TICK_GPIO2      9
#define TICK_SDA        8
#define TICK_SCL        9

// LED controlled by RP2350
#define TICK_LED        17

// GPIO also used for ESP8266 wakeup
#define TICK_GPIO16     18

// UART interface (naming on ESP side!)
#define TICK_U0RXD      32
#define TICK_U0TXD      33

// Power Up control.
#define TICK_CHIP_PU    37

#endif // _RP2350_LAUNCHPAD_WIFITICK_H_
