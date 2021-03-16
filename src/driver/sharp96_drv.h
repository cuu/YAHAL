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
//  Driver for Sharp 96x96 b/w LCD displays
//  (display type LS013B4DN04)

#ifndef _SHARP96_H_
#define _SHARP96_H_

#include <cstdint>
#include "spi_interface.h"
#include "timer_interface.h"
#include "gpio_interface.h"
#include "lcd_interface.h"

class sharp96_drv : public lcd_interface {
public:
    // User interface
    /////////////////
    sharp96_drv(spi_interface   & spi,
                gpio_pin        & disp_on_pin,
                gpio_pin        & pwr_pin,
                timer_interface & timer);

    virtual ~sharp96_drv() { }

    inline uint16_t getSizeX() override { return 96; }
    inline uint16_t getSizeY() override { return 96; }

    // x and y range from 0 to getX/YSize() - 1
    void drawPixel(uint16_t x,  uint16_t y,  color_t color) override;
    void drawHLine(uint16_t xs, uint16_t ys, uint16_t xe, color_t c) override;
    void drawVLine(uint16_t xs, uint16_t ys, uint16_t ye, color_t c) override;

    void drawArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                   pixel_stream & ps) override;

    void fillArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                   color_t c) override;

private:
    void    flush();
    void    writeData(uint8_t data);
    uint8_t reverseByte(uint8_t data);

    spi_interface   & _spi;
    gpio_pin        & _disp_on_pin;
    gpio_pin        & _pwr_pin;
    timer_interface & _timer;
    bool              _dirty;
    bool              _setVCOM;

    // The internal buffer for the whole display.
    // [Y][X], and 8 Pixel/byte in X
    uint8_t _display_buffer[96][12];
};

#endif // _SHARP96_H_
