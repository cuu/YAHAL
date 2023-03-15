/*
 * st7735s.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "st7735s_drv.h"
#include "pixel_stream_const.h"
#include "task.h"

// Hardware Configurations
//////////////////////////
st7735s_drv::config st7735s_drv::Crystalfontz_128x128(
        128, 128, 132, 132, 2, 1, st7735s_drv::BGR_COLOR_FILTER);

// ST7735s Commands
///////////////////

// Read Commands
////////////////
#define CMD_RDDID       0x04    // Read Display ID
#define CMD_RDDST       0x09    // Read Display Status
#define CMD_RDDPM       0x0A    // Read Display Power Mode
#define CMD_RDDMADCTL   0x0B    // Read Display MADCTL
#define CMD_RDDCOLMOD   0x0C    // Read Display Pixel Format (Color Mode)
#define CMD_RDDIM       0x0D    // Read Display Image Mode
#define CMD_RDDSM       0x0E    // Read Display Signal Mode
#define CMD_RDDSDR      0x0F    // Read Display Self-Diagnostic Result
#define CMD_RAMRD       0x2E    // Memory Read
#define CMD_RDID1       0xDA    // Read ID1 Value
#define CMD_RDID2       0xDB    // Read ID2 Value
#define CMD_RDID3       0xDC    // Read ID3 Value

// Write Commands
/////////////////
#define CMD_NOP         0x00    // Non operation
#define CMD_SWRESET     0x01    // Soft Reset
#define CMD_SLPIN       0x10    // Sleep On  (120ms)
#define CMD_SLPOUT      0x11    // Sleep Off (120ms)
#define CMD_PTLON       0x12    // Partial Display Mode On
#define CMD_NORON       0x13    // Normal Display Mode On
#define CMD_INVOFF      0x20    // Display Inversion Off
#define CMD_INVON       0x21    // Display Inversion On
#define CMD_GAMSET      0x26    // Gamma Set
#define CMD_DISPOFF     0x28    // Display Off
#define CMD_DISPON      0x29    // Display On
#define CMD_CASET       0x2A    // Column Address Set
#define CMD_RASET       0x2B    // Row Address Set
#define CMD_RAMWR       0x2C    // Memory Write
#define CMD_RGBSET      0x2D    // Color Setting for 4K, 65K, 262K
#define CMD_PTLAR       0x30    // Partial Area
#define CMD_SCRLAR      0x33    // Scroll Area Set
#define CMD_TEOFF       0x34    // Tearing Effect Line Off
#define CMD_TEON        0x35    // Tearing Effect Line On
#define CMD_MADCTL      0x36    // Memory Data Access Control
#define CMD_VSCSAD      0x37    // Vertical Scroll Start Address of RAM
#define CMD_IDMOFF      0x38    // Idle Mode Off
#define CMD_IDMON       0x39    // Idle Mode On
#define CMD_COLMOD      0x3A    // Interface Pixel Format

// Panel Function Command List
//////////////////////////////
#define CMD_FRMCTR1     0xB1    // Frame Rate Control (in normal mode/Full colors)
#define CMD_FRMCTR2     0xB2    // Frame Rate Control (in Idle mode/8-colors)
#define CMD_FRMCTR3     0xB3    // Frame Rate Control (in Partial mode/full colors)
#define CMD_INVCTR      0xB4    // Display Inversion Control
#define CMD_PWCTR1      0xC0    // Power Control 1
#define CMD_PWCTR2      0xC1    // Power Control 2
#define CMD_PWCTR3      0xC2    // Power Control 3 (in normal mode/Full colors)
#define CMD_PWCTR4      0xC3    // Power Control 4 (in Idle mode/8-colors)
#define CMD_PWCTR5      0xC4    // Power Control 5 (in Partial mode/full colors)
#define CMD_VMCTR1      0xC5    // VCOM Control 1
#define CMD_VMOFCTR     0xC7    // VCOM Offset Control
#define CMD_WRID2       0xD1    // Write ID2 Value
#define CMD_WRID3       0xD2    // Write ID3 Value
#define CMD_NVCTR1      0xD9    // NVM Control Status
#define CMD_NVCTR2      0xDE    // NVM Read Command
#define CMD_NVCTR3      0xDF    // NWM Write Command
#define CMD_GAMCTRP1    0xE0    // Gamma ('+' polarity) Correction Characteristics Setting
#define CMD_GAMCTRN1    0xE1    // Gamma ('-' polarity) Correction Characteristics Setting
#define CMD_GCV         0xFC    // Gate Pump Clock Frequency Variable

st7735s_drv::st7735s_drv(spi_interface & spi, gpio_pin & rst_pin,
                         gpio_pin & dc_pin, config & lcd,
                         mutex_interface * mutex)
    : _spi(spi), _rst_pin(rst_pin), _dc_pin(dc_pin), _lcd(lcd), _mutex(mutex)
{

    // Initialize Reset & D/C pins
    _rst_pin.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    _dc_pin. gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Make a HW-reset
    _rst_pin.gpioWrite(LOW);
    task::sleep(10);
    _rst_pin.gpioWrite(HIGH);
    task::sleep(300);

    //    if (_mutex) _mutex->lock();

    writeCommand(CMD_SLPOUT);	// Wake up ...
    task::sleep(150);

    writeCommand(CMD_GAMSET);
    writeData(0x03);

    writeCommand(CMD_COLMOD);
    writeData(0x05);

    writeCommand(CMD_SCRLAR);
    writeData(0);
    writeData(_lcd.offsetY);
    writeData(0);
    writeData(_lcd.sizeY);
    writeData(0);
    writeData(_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);

    setOrientation(UP);
    _first_row = 0;
    scroll(0);

    writeCommand(CMD_DISPON);

    //    if (_mutex) _mutex->unlock();
}

st7735s_drv::~st7735s_drv()
{
}

uint16_t st7735s_drv::getSizeX()
{
    if ((_orientation == UP) || (_orientation == DOWN))
        return _lcd.sizeX;
    else
        return _lcd.sizeY;
}

uint16_t st7735s_drv::getSizeY()
{
    if ((_orientation == UP) || (_orientation == DOWN))
        return _lcd.sizeY;
    else
        return _lcd.sizeX;
}

void st7735s_drv::setOrientation(Orientation o)
{
    _orientation = o;
    uint8_t madctl = (_lcd.flags & BGR_COLOR_FILTER) ? 0x8 : 0;
    if (_mutex)
        _mutex->lock();
    writeCommand(CMD_MADCTL);
    switch (o)
    {
    case UP:
        writeData(madctl | 0xC0);
        break;
    case DOWN:
        writeData(madctl);
        break;
    case LEFT:
        writeData(madctl | 0xA0);
        break;
    case RIGHT:
        writeData(madctl | 0x60);
        break;
    }
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::drawPixel(uint16_t x, uint16_t y, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    change(x, y);
    if (_mutex)
        _mutex->lock();
    setFrame(x, y, x, y);
    writeCommand(CMD_RAMWR);
    _tx_buffer[0] = color >> 8;
    _tx_buffer[1] = color & 0xff;
    writeDataBuffer(2);
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::drawHLine(uint16_t xs, uint16_t y, uint16_t xe, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    uint16_t dummy;
    change(xs, y);
    change(xe, dummy);
    if (_mutex)
        _mutex->lock();
    setFrame(xs, y, xe, y);
    writeCommand(CMD_RAMWR);
    int buf_index = 0;
    for (int i = xs; i <= xe; ++i)
    {
        _tx_buffer[buf_index++] = color >> 8;
        _tx_buffer[buf_index++] = color & 0xff;
    }
    writeDataBuffer(buf_index);
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::drawVLine(uint16_t x, uint16_t ys, uint16_t ye, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    uint16_t dummy;
    change(x, ys);
    change(dummy, ye);
    if (_mutex)
        _mutex->lock();
    setFrame(x, ys, x, ye);
    writeCommand(CMD_RAMWR);
    int buf_index = 0;
    for (int i = ys; i <= ye; ++i)
    {
        _tx_buffer[buf_index++] = color >> 8;
        _tx_buffer[buf_index++] = color & 0xff;
    }
    writeDataBuffer(buf_index);
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::drawArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           pixel_stream & ps)
{
    bool color_conversion = (ps.getColorType() != LCD::COLORTYPE_RGB565);
    ps.reset();
    change(xs, ys);
    change(xe, ye);
    if (_mutex)
        _mutex->lock();
    setFrame(xs, ys, xe, ye);
    int16_t pixels = (xe - xs + 1) * (ye - ys + 1);
    writeCommand(CMD_RAMWR);
    int index = 0;
    for (int i = 0; i < pixels; i++)
    {
        color_t color = ps.getNext();
        if (color_conversion)
        {
            color = convertColor(color, LCD::COLORTYPE_RGB565);
        }
        _tx_buffer[index++] = color >> 8;
        _tx_buffer[index++] = color & 0xff;
        if (index == BUF_LEN) {
            writeDataBuffer(index);
            index = 0;
        }
    }
    if (index) {
        writeDataBuffer(index);
    }
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::fillArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           color_t c)
{
    pixel_stream_const ps(convertColor(c, LCD::COLORTYPE_RGB565));
    drawArea(xs, ys, xe, ye, ps);
}

void st7735s_drv::scroll(int16_t rows)
{
    _first_row += rows;
    if (_first_row < 0)
        _first_row += _lcd.sizeY;
    else if (_first_row >= _lcd.sizeY)
        _first_row -= _lcd.sizeY;
    if (_mutex)
        _mutex->lock();
    writeCommand(CMD_VSCSAD);
    writeData(0);
    writeData(_lcd.offsetY + _first_row);
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::clearScreen(color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    scroll(-_first_row); // Reset scrolling
    if (_mutex)
        _mutex->lock();
    setFrame(0, 0, _lcd.sizeX - 1, _lcd.sizeY - 1);
    int16_t pixels = _lcd.sizeX * _lcd.sizeY;
    writeCommand(CMD_RAMWR);
    uint8_t msb = color >> 8;
    uint8_t lsb = color & 0xff;
    int index = 0;
    for (int i = 0; i <= pixels; i++) {
        _tx_buffer[index++] = msb;
        _tx_buffer[index++] = lsb;
        if (index == BUF_LEN) {
            writeDataBuffer(index);
            index = 0;
        }
    }
    if (index) {
        writeDataBuffer(index);
    }
    if (_mutex)
        _mutex->unlock();
}

void st7735s_drv::inverseColors(bool b)
{
    if (_mutex)
        _mutex->lock();
    if (b)
        writeCommand(CMD_INVON);
    else
        writeCommand(CMD_INVOFF);
    if (_mutex)
        _mutex->unlock();
}

// private methods.
///////////////////
void st7735s_drv::change(uint16_t & x, uint16_t & y)
{
    switch (_orientation)
    {
    case UP:
        y += _lcd.sizeY + _lcd.offsetY - _first_row - 1;
        break;
    case DOWN:
        y += _first_row;
        break;
    case LEFT:
        x += _lcd.sizeY + _lcd.offsetY - _first_row - 1;
        break;
    case RIGHT:
        x += _first_row;
        break;
    }
    if (y >= _lcd.sizeY)
        y -= _lcd.sizeY;
    if (x >= _lcd.sizeY)
        x -= _lcd.sizeY;
}

void st7735s_drv::setFrame(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    switch (_orientation)
    {
    case UP:
        xs += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
        ys += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
        xe += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
        ye += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
        break;
    case DOWN:
        xs += _lcd.offsetX;
        ys += _lcd.offsetY;
        xe += _lcd.offsetX;
        ye += _lcd.offsetY;
        break;
    case LEFT:
        xs += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
        ys += _lcd.offsetX;
        xe += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
        ye += _lcd.offsetX;
        break;
    case RIGHT:
        xs += _lcd.offsetY;
        ys += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
        xe += _lcd.offsetY;
        ye += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
        break;
    }
    writeCommand(CMD_CASET);
    _tx_buffer[0] = 0;
    _tx_buffer[1] = xs;
    _tx_buffer[2] = 0;
    _tx_buffer[3] = xe;
    writeDataBuffer(4);

    writeCommand(CMD_RASET);
    _tx_buffer[0] = 0;
    _tx_buffer[1] = ys;
    _tx_buffer[2] = 0;
    _tx_buffer[3] = ye;
    writeDataBuffer(4);
}

void st7735s_drv::writeData(uint8_t data)
{
    _spi.spiTx(&data, 1);
}

void st7735s_drv::writeDataBuffer(int len)
{
    _spi.spiTx(_tx_buffer, len);
}

void st7735s_drv::writeCommand(uint8_t cmd)
{
    _dc_pin.gpioWrite(LOW);
    uint8_t rcv_data;
    _spi.spiTxRx(&cmd, &rcv_data, 1);
    _dc_pin.gpioWrite(HIGH);
}

