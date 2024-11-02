#ifndef _ILI9488_DRV_H
#define _ILI9488_DRV_H

#include "spi_interface.h"
#include "gpio_interface.h"
#include "lcd_interface.h"
#include "mutex_interface.h"

#define TFT_MADCTL 0x36
#define TFT_SLPOUT 0x11
#define TFT_DISPON 0x29
#define TFT_INVON 0x21
#define TFT_CASET 0x2A
#define TFT_RASET 0x2B
#define TFT_RAMWR 0x2C

const int BUF_LEN = 650;

class ili9488_drv:public lcd_interface{
public:
    // Flags and struct to define the HW details
    // of the display
    ////////////////////////////////////////////
    static const uint8_t   RGB_COLOR_FILTER = 0x00;
    static const uint8_t   BGR_COLOR_FILTER = 0x01;

    // Structure to define the HW details of the display
    /////////////////////////////////////////////////////
    struct config {
        config(uint16_t sX, uint16_t sY, uint16_t sRX, uint16_t sRY,
               uint8_t  oX, uint8_t  oY, uint8_t  f)
                : sizeX(sX),   sizeY(sY),   sizeRamX(sRX), sizeRamY(sRY),
                  offsetX(oX), offsetY(oY), flags(f) { }
        uint16_t    sizeX;
        uint16_t    sizeY;
        uint16_t    sizeRamX;
        uint16_t    sizeRamY;
        uint16_t     offsetX;
        uint16_t     offsetY;
        uint8_t     flags;
    };
    // Display configurations
    static config PICO320;//
public:
    ili9488_drv(spi_interface   & spi,//spi1_tx,spi1_rx,spi1_cs,spi1_sck
                gpio_pin        & rst_pin,
                gpio_pin        & dc_pin,
                config          & lcd,
                mutex_interface * mutex = nullptr);

    virtual ~ili9488_drv();
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

    void clearScreen(color_t c);

    void scroll(int16_t lines);

private:
    void change  (uint16_t & x, uint16_t & y);
    void setFrame(uint16_t   xs, uint16_t  ys, uint16_t xe, uint16_t ye);//== DefineRegion
//    void setCursorFrame(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);

    void writeData(uint8_t data); //spi_write_data
    void writeDataBuffer(int len); //
    void writeCommand(uint8_t cmd);//spi_write_command

    uint8_t             _tx_buffer[BUF_LEN];
    spi_interface   &   _spi;
    gpio_pin        &   _rst_pin;
    gpio_pin        &   _dc_pin;
    config          &   _lcd;
    mutex_interface *   _mutex;
    int16_t      _first_row; // Vertical scroll start address
};

#endif