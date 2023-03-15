/*
 * sharp96_drv.cpp
 *
 *  Created on: 29.06.2018
 *      Author: Andreas Terstegge
 */

#include "sharp96_drv.h"
#include "pixel_stream_const.h"

sharp96_drv::sharp96_drv(spi_interface   & spi,
                         gpio_pin        & disp,
                         gpio_pin        & pwr,
                         timer_interface & timer)
    : _spi(spi), _disp_on_pin(disp), _pwr_pin(pwr),
      _timer(timer), _dirty(true), _setVCOM(false) {

    // Clear the display buffer
    for(int y=0; y < getSizeY(); y++) {
        for(unsigned int x=0; x < sizeof(_display_buffer[0]); x++) {
            _display_buffer[y][x] = 0xff;
        }
    }

    // Initialize disp and pwr pins
    _disp_on_pin.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    _pwr_pin.gpioMode    (GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Initialize SPI interface
    _spi.setSpeed(1000000);
    _spi.generateCS(false);
    _spi.setCS(HIGH);

    // Initialize timer
    _timer.setPeriod(50000, TIMER::PERIODIC);
    _timer.setCallback([this]() {
        flush();
    });
    _timer.start();
}

void sharp96_drv::drawPixel(uint16_t x, uint16_t y, color_t c)
{
    if(COLOR_RGB(c) == 0)
        _display_buffer[y][x>>3] &= ~(0x80 >> (x & 0x7));
    else
        _display_buffer[y][x>>3] |=  (0x80 >> (x & 0x7));
    _dirty = true;
}

void sharp96_drv::drawHLine(uint16_t xs, uint16_t y, uint16_t xe, color_t c)
{
    for (int x=xs; x <= xe; ++x)
        drawPixel(x, y, c);
}

void sharp96_drv::drawVLine(uint16_t x, uint16_t ys, uint16_t ye, color_t c)
{
    for (int y=ys; y <= ye; ++y)
        drawPixel(x, y, c);
}

void sharp96_drv::drawArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           pixel_stream & ps)
{
    for (int y=ys; y <= ye; ++y)
        for (int x=xs; x <= xe; ++x)
            drawPixel(x, y, ps.getNext());
}

void sharp96_drv::fillArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           color_t c)
{
    for (int y=ys; y <= ye; ++y)
        for (int x=xs; x <= xe; ++x)
            drawPixel(x, y, c);
}

void sharp96_drv::flush()
{
    // Handle VCOM bit
    uint8_t cmd = 0;
    if (_setVCOM) cmd |= 0x40;
    _setVCOM ^= true;

    // Start SPI transfer by setting CS high
    _spi.setCS(HIGH);

    if (_dirty) {
        uint8_t * data_ptr = _display_buffer[0];
        cmd |= 0x80; // Update data
        writeData(cmd);
        for (int y=0; y < getSizeY(); ++y) {
            writeData(reverseByte(y+1));
            _spi.spiTx(data_ptr, sizeof(_display_buffer[0]));
            data_ptr += sizeof(_display_buffer[0]);
            writeData(0x00); // dummy
        }
    } else {
        // Only toggle VCOM, display memory not changed
        writeData(cmd);
    }
    writeData(0x00); // dummy

    // Short delay and set CS low
    for (int i=0; i < 5; ++i) ;
    _spi.setCS(LOW);

    // Reset the dirty flag
    _dirty = false;
}

void sharp96_drv::writeData(uint8_t data)
{
    _spi.spiTx(&data, 1);
}

// Bit reversal helper
uint8_t sharp96_drv::reverseByte(uint8_t data)
{
#ifdef __MSP432P401R__
    uint32_t input = data;
    uint32_t output;
    __asm__("rbit %0, %1\n" : "=r"(output) : "r"(input));
    return output >> 24;
#else
    uint8_t y = 0, i = 0;
    for (i=0; i < 8; i++) {
        y    = y << 1;
        y   |= (data & 1);
        data =  data >> 1;
    }
    return y;
#endif
}
