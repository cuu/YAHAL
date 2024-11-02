#include <ili9488_drv.h>
#include "pixel_stream_const.h"
#include "task.h"

// Hardware Configurations
//////////////////////////
ili9488_drv::config ili9488_drv::PICO320(320, 320,320,480,0,0,BGR_COLOR_FILTER);

ili9488_drv::ili9488_drv(spi_interface & spi, gpio_pin & rst_pin,
                         gpio_pin & dc_pin, config & lcd,
                         mutex_interface * mutex)
        : _spi(spi), _rst_pin(rst_pin), _dc_pin(dc_pin), _lcd(lcd), _mutex(mutex) {

    _spi.setSpeed(24000000);
    // Initialize Reset & D/C pins
    _rst_pin.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    _dc_pin. gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Make a HW-reset
    _rst_pin.gpioWrite(HIGH);  task::sleep_ms(1);
    _rst_pin.gpioWrite(LOW);   task::sleep_ms(10);
    _rst_pin.gpioWrite(HIGH);  task::sleep_ms(10);

    writeCommand(0xF0);
    writeData(0xc3);
    writeCommand(0xF0);
    writeData(0x96);
    writeCommand(TFT_MADCTL);
    writeData(0x48);
    writeCommand(0x3A);
    writeData(0x06);
    writeCommand(0xB4);
    writeData(0x00);
    writeCommand(0xB7);
    writeData(0xC6);
    writeCommand(0xB9);
    writeData(0x02);
    writeData(0xE0);
    writeCommand(0xC0);
    writeData(0x80);
    writeData(0x06);
    writeCommand(0xC1);
    writeData(0x15);
    writeCommand(0xC2);
    writeData(0xA7);
    writeCommand(0XC5);
    writeData(0x04);
    writeCommand(0xE8);
    writeData(0x40);
    writeData(0x8A);
    writeData(0x00);
    writeData(0x00);
    writeData(0x29);
    writeData(0x19);
    writeData(0xAA);
    writeData(0x33);
    writeCommand(0xE0);
    writeData(0xF0);
    writeData(0x06);
    writeData(0x0F);
    writeData(0x05);
    writeData(0x04);
    writeData(0x20);
    writeData(0x37);
    writeData(0x33);
    writeData(0x4C);
    writeData(0x37);
    writeData(0x13);
    writeData(0x14);
    writeData(0x2B);
    writeData(0x31);
    writeCommand(0xE1);
    writeData(0xF0);
    writeData(0x11);
    writeData(0x1B);
    writeData(0x11);
    writeData(0x0F);
    writeData(0x0A);
    writeData(0x37);
    writeData(0x43);
    writeData(0x4C);
    writeData(0x37);
    writeData(0x13);
    writeData(0x13);
    writeData(0x2C);
    writeData(0x32);
    writeCommand(0xF0);
    writeData(0x3C);
    writeCommand(0xF0);
    writeData(0x69);
    writeCommand(0x35);
    writeData(0x00);
    writeCommand(TFT_SLPOUT);
    task::sleep_ms(1);
    writeCommand(TFT_DISPON);
    task::sleep_ms(1);
    writeCommand(TFT_INVON);
    writeCommand(TFT_CASET);
    writeData(0x00);
    writeData(0x00);
    writeData(0x01);
    writeData(0x3F);
    writeCommand(TFT_RASET);
    writeData(0x00);
    writeData(0x00);
    writeData(0x01);
    writeData(0x3F);
    writeCommand(TFT_RAMWR);

    writeCommand(0x33);//HW scroll
    writeData(_lcd.offsetY>>8);
    writeData(_lcd.offsetY & 0xff);
    writeData(_lcd.sizeRamY >> 8);
    writeData(_lcd.sizeRamY & 0xFF);
    writeData(0);
    writeData(_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);

    _first_row = 0;
    scroll(0);

}

ili9488_drv::~ili9488_drv()
{
}

uint16_t ili9488_drv::getSizeX()
{
    return _lcd.sizeX;
}

uint16_t ili9488_drv::getSizeY()
{
    return _lcd.sizeY;
}


void ili9488_drv::scroll(int16_t rows)
{
    _first_row += rows;
    if (_first_row < 0)
        _first_row += _lcd.sizeY;
    else if (_first_row >= _lcd.sizeY)
        _first_row -= _lcd.sizeY;
    if (_mutex)
        _mutex->lock();
    writeCommand(0x37);
    writeData((_lcd.offsetY + _first_row)>>8);
    writeData((_lcd.offsetY + _first_row)&0xff);
    if (_mutex)
        _mutex->unlock();
}

void ili9488_drv::drawPixel(uint16_t x, uint16_t y, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    change(x, y);
    if (_mutex)
        _mutex->lock();
    setFrame(x, y, x, y);
    writeCommand(TFT_RAMWR);
    _tx_buffer[0] = color >> 8;
    _tx_buffer[1] = color & 0xff;
    writeDataBuffer(2);
    if (_mutex)
        _mutex->unlock();
}

void ili9488_drv::drawHLine(uint16_t xs, uint16_t y, uint16_t xe, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    uint16_t dummy;
    change(xs, y);
    change(xe, dummy);
    if (_mutex)
        _mutex->lock();
    setFrame(xs, y, xe, y);
    writeCommand(TFT_RAMWR);
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

void ili9488_drv::drawVLine(uint16_t x, uint16_t ys, uint16_t ye, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    uint16_t dummy;
    change(x, ys);
    change(dummy, ye);
    if (_mutex)
        _mutex->lock();
    setFrame(x, ys, x, ye);
    writeCommand(TFT_RAMWR);
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

void ili9488_drv::drawArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           pixel_stream & ps)
{
    bool color_conversion = (ps.getColorType() != LCD::COLORTYPE_RGB565);
    ps.reset();
    change(xs, ys);
    change(xe, ye);
    if (_mutex)
        _mutex->lock();
    setFrame(xs, ys, xe, ye);
    int pixels = (xe - xs + 1) * (ye - ys + 1);
    writeCommand(TFT_RAMWR);
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

void ili9488_drv::fillArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           color_t c)
{
    pixel_stream_const ps(convertColor(c, LCD::COLORTYPE_RGB565));
    drawArea(xs, ys, xe, ye, ps);
}

void ili9488_drv::clearScreen(color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    scroll(-_first_row); // Reset scrolling
    if (_mutex)
        _mutex->lock();
    setFrame(0, 0, _lcd.sizeX - 1, _lcd.sizeY - 1);
    int pixels = _lcd.sizeX * _lcd.sizeY;
    writeCommand(TFT_RAMWR);
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

///////////////////////////////////////////////////////// private method //////////////////////////////////
///////////////////////////////////////////////////////// private method //////////////////////////////////
///////////////////////////////////////////////////////// private method //////////////////////////////////
///////////////////////////////////////////////////////// private method //////////////////////////////////
///////////////////////////////////////////////////////// private method //////////////////////////////////
///////////////////////////////////////////////////////// private method //////////////////////////////////
void ili9488_drv::change(uint16_t & x, uint16_t & y)
{
    y += _lcd.sizeY + _lcd.offsetY - _first_row - 1;

    if (y >= _lcd.sizeY)
        y -= _lcd.sizeY;
    if (x >= _lcd.sizeY)
        x -= _lcd.sizeY;
}

//xs xstart ys ystart xe xend ye yend
void ili9488_drv::setFrame(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{

    xs += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
    ys += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
    xe += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
    ye += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);

    writeCommand(TFT_CASET);
    _tx_buffer[0] = 0;
    _tx_buffer[1] = xs;
    _tx_buffer[2] = 0;
    _tx_buffer[3] = xe;
    writeDataBuffer(4);

    writeCommand(TFT_RASET);
    _tx_buffer[0] = 0;
    _tx_buffer[1] = ys;
    _tx_buffer[2] = 0;
    _tx_buffer[3] = ye;
    writeDataBuffer(4);
}

void ili9488_drv::writeData(uint8_t data)
{
    _spi.spiTx(&data, 1);
}

void ili9488_drv::writeDataBuffer(int len)//HW1SendSPI
{
    _spi.spiTx(_tx_buffer, len);
}

void ili9488_drv::writeCommand(uint8_t cmd)
{
    _dc_pin.gpioWrite(LOW);
    uint8_t rcv_data;
    _spi.spiTxRx(&cmd, &rcv_data, 1);
    _dc_pin.gpioWrite(HIGH);
}