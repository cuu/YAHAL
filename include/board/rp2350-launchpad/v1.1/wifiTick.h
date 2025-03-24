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

// ESP8266 /reset
#define TICK_nRESET     7

// ESP8266 chip PU
#define TICK_CHIP_PU    37

// LED on wifiTick
#define TICK_LED        17

// ESP8266 GPIO16
#define TICK_GPIO16     18

// UART interface
#define TICK_UART_TX    32
#define TICK_UART_RX    33

// I2C interface
#define TICK_I2C_SDA    8
#define TICK_I2C_SCL    9

// SPI interface
#define TICK_SPI_CS     5
#define TICK_SPI_MOSI   3
#define TICK_SPI_MISO   4
#define TICK_SPI_CLK    6

#endif // _RP2350_LAUNCHPAD_WIFITICK_H_
