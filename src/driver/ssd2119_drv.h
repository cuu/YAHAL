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
//  Driver for SSD2119-based LCD displays

#ifndef _SSD2119_H_
#define _SSD2119_H_

#include "spi_interface.h"
#include "gpio_interface.h"
#include "lcd_interface.h"
#include "mutex_interface.h"

const int BUF_LEN = 650;

class ssd2119_drv : public lcd_interface {
public:
    // Structure to define the HW details of the display
    /////////////////////////////////////////////////////
    struct config {
        config(uint16_t sX, uint16_t sY) : sizeX(sX),   sizeY(sY) { }
        uint16_t    sizeX;
        uint16_t    sizeY;
    };
    // Display configurations
    static config Kentec_K350QVG;

public:
    // User interface
    /////////////////
    ssd2119_drv(spi_interface   & spi,
                gpio_pin        & rst_pin,
                gpio_pin        & dc_pin,
                config          & lcd,
                mutex_interface * mutex = nullptr);

    virtual ~ssd2119_drv();

    uint16_t getSizeX() override;
    uint16_t getSizeY() override;

    // x and y range from 0 to get[X/Y]Size() - 1
    void drawPixel(uint16_t x,  uint16_t y,  color_t color) override;
    void drawHLine(uint16_t xs, uint16_t ys, uint16_t xe, color_t c) override;
    void drawVLine(uint16_t xs, uint16_t ys, uint16_t ye, color_t c) override;

    void drawArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                   pixel_stream & ps) override;

    void fillArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                   color_t c) override;

    // Specific methods for SSD2119
    void clearScreen(color_t c);

private:
    void setCursorLtoR(uint16_t x, uint16_t y);
    void setCursorTtoB(uint16_t x, uint16_t y);
//    void setCursorFrame(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);

    void writeDataBuffer(int len);
    void writeCommand(uint8_t cmd);
    void writeCmdData(uint8_t cmd, uint16_t data);

    uint8_t             _tx_buffer[BUF_LEN];
    spi_interface   &   _spi;
    gpio_pin        &   _rst_pin;
    gpio_pin        &   _dc_pin;
    config          &   _lcd;
    mutex_interface *   _mutex;
};

#endif // _SSD2119_H_
