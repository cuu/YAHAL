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
//  Driver for ST7735S-based LCD displays

#ifndef _ST7735S_H_
#define _ST7735S_H_

#include "spi_interface.h"
#include "gpio_interface.h"
#include "lcd_interface.h"
#include "mutex_interface.h"

const int BUF_LEN = 256;

class st7735s_drv : public lcd_interface {
public:
    // Flags and struct to define the HW details
    // of the display
    ////////////////////////////////////////////
    static const uint8_t   RGB_COLOR_FILTER = 0x00;
    static const uint8_t   BGR_COLOR_FILTER = 0x01;

    struct config {
        config(uint16_t sX, uint16_t sY, uint16_t sRX, uint16_t sRY,
               uint8_t  oX, uint8_t  oY, uint8_t  f)
        : sizeX(sX),   sizeY(sY),   sizeRamX(sRX), sizeRamY(sRY),
          offsetX(oX), offsetY(oY), flags(f) { }
        uint16_t    sizeX;
        uint16_t    sizeY;
        uint16_t    sizeRamX;
        uint16_t    sizeRamY;
        uint8_t     offsetX;
        uint8_t     offsetY;
        uint8_t     flags;
    };

    // Display configurations
    static config Crystalfontz_128x128;

    enum Orientation { UP, DOWN, LEFT, RIGHT };

public:
    // User interface
    /////////////////
    st7735s_drv(spi_interface   & spi,
                gpio_pin        & rst_pin,
                gpio_pin        & dc_pin,
                config          & lcd,
                mutex_interface * mutex = nullptr);

    virtual ~st7735s_drv();

    uint16_t getSizeX() override;
    uint16_t getSizeY() override;

    // x and y range from 0 to getX/YSize() - 1
    void drawPixel(uint16_t x,  uint16_t y,  color_t color) override;
    void drawHLine(uint16_t xs, uint16_t ys, uint16_t xe, color_t c) override;
    void drawVLine(uint16_t xs, uint16_t ys, uint16_t ye, color_t c) override;

    void drawArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                   pixel_stream & ps) override;

    void fillArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                   color_t c) override;

    // Specific methods for ST7735s
    void scroll(int16_t lines);
    void clearScreen(color_t c);
    void inverseColors(bool b);
    void setOrientation(Orientation o);

private:

    void change  (uint16_t & x, uint16_t & y);
    void setFrame(uint16_t   xs, uint16_t  ys, uint16_t xe, uint16_t ye);

    void writeData(uint8_t data);
    void writeDataBuffer(int len);
    void writeCommand(uint8_t cmd);

    uint8_t          _tx_buffer[BUF_LEN];
    uint8_t          _rx_buffer[BUF_LEN];
    spi_interface  & _spi;
    gpio_pin       & _rst_pin;
    gpio_pin       & _dc_pin;
    config         & _lcd;

    Orientation _orientation;
    int8_t      _first_row; // Vertical scroll start address

    mutex_interface * _mutex;
};

#endif // _ST7735S_H_
