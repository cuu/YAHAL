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
// on K350 QVGA Booterpack MKII from TI,
// when used with a RP2350 Launchpad.
//
#ifndef BOOSTXL_K350QVG_BOOSTXL_K350QVGA_H
#define BOOSTXL_K350QVG_BOOSTXL_K350QVGA_H

// Touch signals
#define K350_TOUCHXP_GPIO   42
#define K350_TOUCHYP_GPIO   41
#define K350_TOUCHXN_GPIO   2
#define K350_TOUCHYN_GPIO   1

// LED backlight
#define K350_BACK_LED       25

// SPI signals
#define K350_LCD_MISO_GPIO  12
#define K350_LCD_MOSI_GPIO  11
#define K350_LCD_SCL_GPIO   30
#define K350_LCD_CS_GPIO    13
#define K350_LCD_RST_GPIO   10
#define K350_LCD_DC_GPIO    36

#endif //BOOSTXL_K350QVG_BOOSTXL_K350QVGA_H
