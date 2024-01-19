/*
 * ssd2119.cpp
 *
 *  Created on: 24.05.2020
 *      Author: Andreas Terstegge
 */

#include <ssd2119_drv.h>
#include "pixel_stream_const.h"
#include "task.h"

// Hardware Configurations
//////////////////////////
ssd2119_drv::config ssd2119_drv::Kentec_K350QVG(320, 240);

//*****************************************************************************
//
// This driver operates in four different screen orientations.  They are:
//
// * Portrait - The screen is taller than it is wide, and the flex connector is
//              on the left of the display.  This is selected by defining
//              PORTRAIT.
//
// * Landscape - The screen is wider than it is tall, and the flex connector is
//               on the bottom of the display.  This is selected by defining
//               LANDSCAPE.
//
// * Portrait flip - The screen is taller than it is wide, and the flex
//                   connector is on the right of the display.  This is
//                   selected by defining PORTRAIT_FLIP.
//
// * Landscape flip - The screen is wider than it is tall, and the flex
//                    connector is on the top of the display.  This is
//                    selected by defining LANDSCAPE_FLIP.
//
// These can also be imagined in terms of screen rotation; if portrait mode is
// 0 degrees of screen rotation, landscape is 90 degrees of counter-clockwise
// rotation, portrait flip is 180 degrees of rotation, and landscape flip is
// 270 degress of counter-clockwise rotation.
//
// If no screen orientation is selected, "landscape flip" mode will be used.
//
//*****************************************************************************
#define LANDSCAPE

#if !defined(PORTRAIT)  && !defined(PORTRAIT_FLIP) && \
    !defined(LANDSCAPE) && !defined(LANDSCAPE_FLIP)
#define LANDSCAPE_FLIP
#endif

//*****************************************************************************
//
// Various definitions controlling coordinate space mapping and drawing
// direction in the four supported orientations.
//
//*****************************************************************************
#ifdef PORTRAIT
#define HORIZ_DIRECTION 0x28
#define VERT_DIRECTION 0x20
#define MAPPED_X(x, y) (319 - (y))
#define MAPPED_Y(x, y) (x)
#endif
#ifdef LANDSCAPE
#define HORIZ_DIRECTION 0x00
#define VERT_DIRECTION  0x08
#define MAPPED_X(x, y)  (319 - (x))
#define MAPPED_Y(x, y)  (239 - (y))
#endif
#ifdef PORTRAIT_FLIP
#define HORIZ_DIRECTION 0x18
#define VERT_DIRECTION  0x10
#define MAPPED_X(x, y)  (y)
#define MAPPED_Y(x, y)  (239 - (x))
#endif
#ifdef LANDSCAPE_FLIP
#define HORIZ_DIRECTION 0x30
#define VERT_DIRECTION  0x38
#define MAPPED_X(x, y) (x)
#define MAPPED_Y(x, y) (y)
#endif

////////////////////////////
// SD2119 registers numbers
////////////////////////////
namespace SSD2119 {
    const uint8_t DEVICE_CODE_READ_REG  = 0x00;
    const uint8_t OSC_START_REG         = 0x00;
    const uint8_t DRV_OUTPUT_CTRL_REG   = 0x01;
    const uint8_t LCD_DRIVE_AC_CTRL_REG = 0x02;
    const uint8_t PWR_CTRL_1_REG        = 0x03;
    const uint8_t DISPLAY_CTRL_REG      = 0x07;
    const uint8_t FRAME_CYCLE_CTRL_REG  = 0x0B;
    const uint8_t PWR_CTRL_2_REG        = 0x0C;
    const uint8_t PWR_CTRL_3_REG        = 0x0D;
    const uint8_t PWR_CTRL_4_REG        = 0x0E;
    const uint8_t GATE_SCAN_START_REG   = 0x0F;
    const uint8_t SLEEP_MODE_1_REG      = 0x10;
    const uint8_t ENTRY_MODE_REG        = 0x11;
    const uint8_t SLEEP_MODE_2_REG      = 0x12;
    const uint8_t GEN_IF_CTRL_REG       = 0x15;
    const uint8_t HORZ_PORCH_REG        = 0x16;
    const uint8_t VERT_PORCH_REG        = 0x17;
    const uint8_t PWR_CTRL_5_REG        = 0x1E;
    const uint8_t UNIFORMITY_REG        = 0x20;
    const uint8_t RAM_DATA_REG          = 0x22;
    const uint8_t FRAME_FREQ_REG        = 0x25;
    const uint8_t ANALOG_SET_REG        = 0x26;
    const uint8_t VCOM_OTP_1_REG        = 0x28;
    const uint8_t VCOM_OTP_2_REG        = 0x29;
    const uint8_t GAMMA_CTRL_1_REG      = 0x30;
    const uint8_t GAMMA_CTRL_2_REG      = 0x31;
    const uint8_t GAMMA_CTRL_3_REG      = 0x32;
    const uint8_t GAMMA_CTRL_4_REG      = 0x33;
    const uint8_t GAMMA_CTRL_5_REG      = 0x34;
    const uint8_t GAMMA_CTRL_6_REG      = 0x35;
    const uint8_t GAMMA_CTRL_7_REG      = 0x36;
    const uint8_t GAMMA_CTRL_8_REG      = 0x37;
    const uint8_t GAMMA_CTRL_9_REG      = 0x3A;
    const uint8_t GAMMA_CTRL_10_REG     = 0x3B;
    const uint8_t VERT_SCRL_CTRL_1_REG  = 0x41;
    const uint8_t VERT_SCRL_CTRL_2_REG  = 0x42;
    const uint8_t V_RAM_POS_REG         = 0x44;
    const uint8_t H_RAM_START_REG       = 0x45;
    const uint8_t H_RAM_END_REG         = 0x46;
    const uint8_t FIRST_WIN_START_REG   = 0x48;
    const uint8_t FIRST_WIN_END_REG     = 0x49;
    const uint8_t SECOND_WIN_START_REG  = 0x4A;
    const uint8_t SECOND_WIN_END_REG    = 0x4B;
    const uint8_t X_RAM_ADDR_REG        = 0x4E;
    const uint8_t Y_RAM_ADDR_REG        = 0x4F;
}

#define ENTRY_MODE_DEFAULT 0x6830
#define MAKE_ENTRY_MODE(x) ((ENTRY_MODE_DEFAULT & 0xFF00) | (x))

ssd2119_drv::ssd2119_drv(spi_interface & spi, gpio_pin & rst_pin,
                         gpio_pin & dc_pin, config & lcd,
                         mutex_interface * mutex)
    : _spi(spi), _rst_pin(rst_pin), _dc_pin(dc_pin), _lcd(lcd), _mutex(mutex)
{
    // Initialize the SPI interface. Do not
    // generate CS signal for every SPI transfer
    // (this speeds up the display operation)
    spi.generateCS(false);

    // Initialize Reset & D/C pins
    _rst_pin.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    _dc_pin. gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Make a HW-reset
    _rst_pin.gpioWrite(LOW);    task::sleep(100);
    _rst_pin.gpioWrite(HIGH);   task::sleep(100);

    // Activate CS
    spi.setCS(LOW);

    // Enter sleep mode
    writeCmdData(SSD2119::SLEEP_MODE_1_REG,     0x0001);

    // Set power control registers
    writeCmdData(SSD2119::PWR_CTRL_2_REG,       0x0005);
    writeCmdData(SSD2119::PWR_CTRL_3_REG,       0x000A);
    writeCmdData(SSD2119::PWR_CTRL_4_REG,       0x2E00);
    writeCmdData(SSD2119::PWR_CTRL_5_REG,       0x00B2);

    writeCmdData(SSD2119::VCOM_OTP_1_REG,       0x0006);
    writeCmdData(SSD2119::OSC_START_REG,        0x0001);
    writeCmdData(SSD2119::DRV_OUTPUT_CTRL_REG,  0x30EF);
    writeCmdData(SSD2119::LCD_DRIVE_AC_CTRL_REG,0x0600);

    // Wake up from sleep mode
    writeCmdData(SSD2119::SLEEP_MODE_1_REG,     0x0000);
    task::sleep(200);

    writeCmdData(SSD2119::ENTRY_MODE_REG,       ENTRY_MODE_DEFAULT);
    writeCmdData(SSD2119::SLEEP_MODE_2_REG,     0x0999);
    writeCmdData(SSD2119::ANALOG_SET_REG,       0x3800);
    writeCmdData(SSD2119::DISPLAY_CTRL_REG,     0x0033);

    // Set gamma control registers
    writeCmdData(SSD2119::GAMMA_CTRL_1_REG,     0x0000);
    writeCmdData(SSD2119::GAMMA_CTRL_2_REG,     0x0303);
    writeCmdData(SSD2119::GAMMA_CTRL_3_REG,     0x0407);
    writeCmdData(SSD2119::GAMMA_CTRL_4_REG,     0x0301);
    writeCmdData(SSD2119::GAMMA_CTRL_5_REG,     0x0301);
    writeCmdData(SSD2119::GAMMA_CTRL_6_REG,     0x0403);
    writeCmdData(SSD2119::GAMMA_CTRL_7_REG,     0x0707);
    writeCmdData(SSD2119::GAMMA_CTRL_8_REG,     0x0400);
    writeCmdData(SSD2119::GAMMA_CTRL_9_REG,     0x0a00);
    writeCmdData(SSD2119::GAMMA_CTRL_10_REG,    0x1000);
    spi.setCS(HIGH);
}

ssd2119_drv::~ssd2119_drv()
{
}

uint16_t ssd2119_drv::getSizeX()
{
#if defined(LANDSCAPE) || defined(LANDSCAPE_FLIP)
    return _lcd.sizeX;
#else
    return _lcd.sizeY;
#endif
}

uint16_t ssd2119_drv::getSizeY()
{
#if defined(LANDSCAPE) || defined(LANDSCAPE_FLIP)
    return _lcd.sizeY;
#else
    return _lcd.sizeX;
#endif
}

void ssd2119_drv::drawPixel(uint16_t x, uint16_t y, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    if (_mutex) _mutex->lock();
    _spi.setCS(LOW);
    writeCmdData(SSD2119::X_RAM_ADDR_REG,   MAPPED_X(x, y));
    writeCmdData(SSD2119::Y_RAM_ADDR_REG,   MAPPED_Y(x, y));
    writeCmdData(SSD2119::RAM_DATA_REG,     color);
    _spi.setCS(HIGH);
    if (_mutex) _mutex->unlock();
}

void ssd2119_drv::drawHLine(uint16_t xs, uint16_t y, uint16_t xe, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    if (_mutex) _mutex->lock();
    _spi.setCS(LOW);
    setCursorLtoR(xs, y);
    int index = 0;
    while(xs++ <= xe) {
        _tx_buffer[index++] = color >> 8;
        _tx_buffer[index++] = color & 0xff;
    }
    writeDataBuffer(index);
    _spi.setCS(HIGH);
    if (_mutex) _mutex->unlock();
}

void ssd2119_drv::drawVLine(uint16_t x, uint16_t ys, uint16_t ye, color_t c)
{
    color_t color = convertColor(c, LCD::COLORTYPE_RGB565);
    if (_mutex) _mutex->lock();
    _spi.setCS(LOW);
    setCursorTtoB(x, ys);
    int index = 0;
    while(ys++ <= ye) {
        _tx_buffer[index++] = color >> 8;
        _tx_buffer[index++] = color & 0xff;
    }
    writeDataBuffer(index);
    _spi.setCS(HIGH);
    if (_mutex) _mutex->unlock();
}

void ssd2119_drv::drawArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           pixel_stream & ps)
{
    bool color_conversion = (ps.getColorType() != LCD::COLORTYPE_RGB565);
    if (_mutex) _mutex->lock();
    _spi.setCS(LOW);
    for (int y = ys; y <= ye; y++) {
        setCursorLtoR(xs, y);
        int index = 0;
        for (int x = xs; x <= xe; x++) {
            color_t color = ps.getNext();
            if (color_conversion) {
                color = convertColor(color, LCD::COLORTYPE_RGB565);
            }
            _tx_buffer[index++] = color >> 8;
            _tx_buffer[index++] = color & 0xff;
        }
        writeDataBuffer(index);
    }
    _spi.setCS(HIGH);
    if (_mutex) _mutex->unlock();
}

void ssd2119_drv::fillArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           color_t c)
{
    pixel_stream_const ps(convertColor(c, LCD::COLORTYPE_RGB565));
    drawArea(xs, ys, xe, ye, ps);
}


void ssd2119_drv::clearScreen(color_t c)
{
    fillArea(0, 0, getSizeX(), getSizeY(), c);
}

void ssd2119_drv::setCursorLtoR(uint16_t x, uint16_t y)
{
    writeCmdData(SSD2119::ENTRY_MODE_REG,   MAKE_ENTRY_MODE(HORIZ_DIRECTION));
    writeCmdData(SSD2119::X_RAM_ADDR_REG,   MAPPED_X(x, y));
    writeCmdData(SSD2119::Y_RAM_ADDR_REG,   MAPPED_Y(x, y));
    writeCommand(SSD2119::RAM_DATA_REG);
}

void ssd2119_drv::setCursorTtoB(uint16_t x, uint16_t y)
{
    writeCmdData(SSD2119::ENTRY_MODE_REG,   MAKE_ENTRY_MODE(VERT_DIRECTION));
    writeCmdData(SSD2119::X_RAM_ADDR_REG,   MAPPED_X(x, y));
    writeCmdData(SSD2119::Y_RAM_ADDR_REG,   MAPPED_Y(x, y));
    writeCommand(SSD2119::RAM_DATA_REG);
}

//void ssd2119_drv::setCursorFrame(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
//{
//    writeCmdData(SSD2119::ENTRY_MODE_REG,   MAKE_ENTRY_MODE(HORIZ_DIRECTION));
//    writeCmdData(SSD2119::V_RAM_POS_REG,    (ye << 8) | ys);
//    writeCmdData(SSD2119::H_RAM_START_REG,  xs);
//    writeCmdData(SSD2119::H_RAM_END_REG,    xe);
//    writeCmdData(SSD2119::X_RAM_ADDR_REG,   xs);
//    writeCmdData(SSD2119::Y_RAM_ADDR_REG,   ys);
//    writeCommand(SSD2119::RAM_DATA_REG);
//    //    writeCmdData(SSD2119::V_RAM_POS_REG,        (uint16_t)(240 - 1) << 8);
//    //    writeCmdData(SSD2119::H_RAM_START_REG,      0x0000);
//    //    writeCmdData(SSD2119::H_RAM_END_REG,        320 - 1);
//    //    writeCmdData(SSD2119::X_RAM_ADDR_REG,       0x0000);
//    //    writeCmdData(SSD2119::Y_RAM_ADDR_REG,       0x0000);
//    //    writeCommand(SSD2119::RAM_DATA_REG);
//    //    for(int ulCount = 0; ulCount < 76800; ulCount++)
//    //    {
//    //        writeData(0x0);    // Black
//    //    }
//
//}

void ssd2119_drv::writeDataBuffer(int len)
{
    _spi.spiTx(_tx_buffer, len);
}

void ssd2119_drv::writeCommand(uint8_t cmd)
{
    // Write command byte
    _dc_pin.gpioWrite(LOW);
    _spi.spiTx(&cmd, 1);
    _dc_pin.gpioWrite(HIGH);
}

void ssd2119_drv::writeCmdData(uint8_t cmd, uint16_t data)
{
    // Write command byte
    _dc_pin.gpioWrite(LOW);
    _spi.spiTx(&cmd, 1);
    _dc_pin.gpioWrite(HIGH);
    // Write 2 data bytes (MSB first)
    data = __builtin_bswap16(data);
    _spi.spiTx((uint8_t *)&data, 2);
}

