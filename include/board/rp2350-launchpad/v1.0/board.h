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
// on the RP2350 Launchpad. Additionally it
// defines some macros for PSRAM usage.

#ifndef RP2350_LAUNCHPAD_BOARD_H
#define RP2350_LAUNCHPAD_BOARD_H

#define PSRAM_CS_GPIO   8

#define BC_UART_TX      26
#define BC_UART_RX      27

#define S1_GPIO         28
#define S2_GPIO         29

#define LED_RED_GPIO    38
#define LED_RGB_GPIO    39
#define LED_RGB_COUNT   8

#define BATT_ADC        7

// Use PSRAM without copying code/data or zeroing
#define PSRAM __attribute__((section(".ps_noload")))

// Use PSRAM and initialize with zeros
#define PSRAM_BSS __attribute__((section(".ps_bss")))

// Use PSRAM and copy code/data
#define PSRAM_LOAD __attribute__((section(".ps_data")))

#endif // RP2350_LAUNCHPAD_BOARD_H
