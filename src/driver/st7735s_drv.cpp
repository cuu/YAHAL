/*
 * st7735s.cpp
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#include "st7735s_drv.h"
#include "zero_bitstream.h"

// ST7735s Commands
///////////////////

// Read Commands
////////////////
#define CMD_RDDID   	0x04	// Read Display ID
#define CMD_RDDST   	0x09	// Read Display Status
#define CMD_RDDPM		0x0A	// Read Display Power Mode
#define CMD_RDDMADCTL	0x0B	// Read Display MADCTL
#define CMD_RDDCOLMOD	0x0C	// Read Display Pixel Format (Color Mode)
#define CMD_RDDIM		0x0D	// Read Display Image Mode
#define CMD_RDDSM		0x0E	// Read Display Signal Mode
#define CMD_RDDSDR		0x0F	// Read Display Self-Diagnostic Result
#define CMD_RAMRD   	0x2E	// Memory Read
#define CMD_RDID1   	0xDA	// Read ID1 Value
#define CMD_RDID2   	0xDB	// Read ID2 Value
#define CMD_RDID3   	0xDC	// Read ID3 Value

// Write Commands
/////////////////
#define CMD_NOP 	    0x00	// Non operation
#define CMD_SWRESET 	0x01	// Soft Reset
#define CMD_SLPIN   	0x10	// Sleep On  (120ms)
#define CMD_SLPOUT  	0x11	// Sleep Off (120ms)
#define CMD_PTLON   	0x12	// Partial Display Mode On
#define CMD_NORON   	0x13	// Normal Display Mode On
#define CMD_INVOFF  	0x20	// Display Inversion Off
#define CMD_INVON   	0x21	// Display Inversion On
#define CMD_GAMSET		0x26	// Gamma Set
#define CMD_DISPOFF 	0x28	// Display Off
#define CMD_DISPON  	0x29	// Display On
#define CMD_CASET   	0x2A	// Column Address Set
#define CMD_RASET   	0x2B	// Row Address Set
#define CMD_RAMWR   	0x2C	// Memory Write
#define CMD_RGBSET		0x2D	// Color Setting for 4K, 65K, 262K
#define CMD_PTLAR		0x30	// Partial Area
#define CMD_SCRLAR		0x33	// Scroll Area Set
#define CMD_TEOFF		0x34	// Tearing Effect Line Off
#define CMD_TEON		0x35	// Tearing Effect Line On
#define CMD_MADCTL  	0x36	// Memory Data Access Control
#define CMD_VSCSAD		0x37	// Vertical Scroll Start Address of RAM
#define CMD_IDMOFF  	0x38	// Idle Mode Off
#define CMD_IDMON	  	0x39	// Idle Mode On
#define CMD_COLMOD  	0x3A	// Interface Pixel Format

// Panel Function Command List
//////////////////////////////
#define CMD_FRMCTR1     0xB1	// Frame Rate Control (in normal mode/Full colors)
#define CMD_FRMCTR2 	0xB2	// Frame Rate Control (in Idle mode/8-colors)
#define CMD_FRMCTR3 	0xB3	// Frame Rate Control (in Partial mode/full colors)
#define CMD_INVCTR		0xB4	// Display Inversion Control
#define CMD_PWCTR1  	0xC0	// Power Control 1
#define CMD_PWCTR2  	0xC1	// Power Control 2
#define CMD_PWCTR3  	0xC2	// Power Control 3 (in normal mode/Full colors)
#define CMD_PWCTR4  	0xC3	// Power Control 4 (in Idle mode/8-colors)
#define CMD_PWCTR5  	0xC4	// Power Control 5 (in Partial mode/full colors)
#define CMD_VMCTR1  	0xC5	// VCOM Control 1
#define CMD_VMOFCTR		0xC7	// VCOM Offset Control
#define CMD_WRID2		0xD1	// Write ID2 Value
#define CMD_WRID3		0xD2	// Write ID3 Value
#define CMD_NVCTR1		0xD9	// NVM Control Status
#define CMD_NVCTR2		0xDE	// NVM Read Command
#define CMD_NVCTR3		0xDF	// NWM Write Command
#define CMD_GAMCTRP1	0xE0	// Gamma ('+' polarity) Correction Characteristics Setting
#define CMD_GAMCTRN1	0xE1	// Gamma ('-' polarity) Correction Characteristics Setting
#define CMD_GCV			0xFC	// Gate Pump Clock Frequency Variable

void delay(int t) {
	int j=0;
	for (int i=0; i < t*1000; ++i) j++;
}

st7735s_drv::st7735s_drv(spi_interface  & spi,
						 gpio_pin   & rst_pin,
						 gpio_pin   & dc_pin,
						 lcd_config & lcd)
: _spi(spi), _rst_pin(rst_pin), _dc_pin (dc_pin), _lcd(lcd) {

	// Initialize Reset & D/C pins
	_rst_pin.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
	_dc_pin. gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

	// Make a HW-reset
	_rst_pin.gpioWrite(LOW);
	delay(200);
	_rst_pin.gpioWrite(HIGH);
	delay(200);

    writeCommand(CMD_SLPOUT);	// Wake up ...
    delay(200);

    writeCommand(CMD_GAMSET);
    writeData(0x03);

    writeCommand(CMD_COLMOD);
    writeData(0x05);

	writeCommand(CMD_SCRLAR);
	writeData(0); writeData(_lcd.offsetY);
	writeData(0); writeData(_lcd.sizeY);
	writeData(0); writeData(_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);

    setOrientation(LCD::UP);
	_first_row = 0;
	scroll(0);

    writeCommand(CMD_DISPON);
}

uint16_t st7735s_drv::getSizeX() {
	if ((_orientation == LCD::UP) ||
		(_orientation == LCD::DOWN))
		return _lcd.sizeX;
	else
		return _lcd.sizeY;
}

uint16_t st7735s_drv::getSizeY() {
	if ((_orientation == LCD::UP) ||
		(_orientation == LCD::DOWN))
		return _lcd.sizeY;
	else
		return _lcd.sizeX;
}

void st7735s_drv::setOrientation(LCD::Orientation o)
{
    _orientation = o;
    uint8_t madctl = (_lcd.flags & LCD::BGR_COLOR_FILTER) ? 0x8 : 0;
    writeCommand(CMD_MADCTL);
    switch (o) {
        case LCD::UP:
            writeData(madctl | 0xC0);
            break;
        case LCD::DOWN:
            writeData(madctl);
            break;
        case LCD::LEFT:
            writeData(madctl | 0xA0);
            break;
        case LCD::RIGHT:
            writeData(madctl | 0x60);
            break;
    }
}

color_t st7735s_drv::rgb24toColor(uint32_t rgb24)
{
    // Translate from a 24-bit RGB color to a 5-6-5 RGB color.
    return(((((rgb24) & 0x00f80000) >> 8) |
            (((rgb24) & 0x0000fc00) >> 5) |
            (((rgb24) & 0x000000f8) >> 3)));
}

void st7735s_drv::drawPixel(uint16_t x, uint16_t y, uint16_t color) {
	change(x, y);
	setFrame(x, y, x, y);
    writeCommand(CMD_RAMWR);
    writeData(color  >>  8);
    writeData(color & 0xff);
}

void st7735s_drv::drawHLine(uint16_t xs, uint16_t y,
						    uint16_t xe, color_t color) {
	uint16_t dummy;
	change(xs, y);
	change(xe, dummy);

	if (xs <= xe) {
		setFrame(xs, y, xe, y);
		writeCommand(CMD_RAMWR);
		for (int i = xs; i <= xe; ++i) {
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
	} else {
		setFrame(xs, y, _lcd.sizeX-1, y);
		writeCommand(CMD_RAMWR);
		for (int i = xs; i < _lcd.sizeX; ++i) {
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
		setFrame(0, y, xe, y);
		writeCommand(CMD_RAMWR);
		for (int i = 0; i <= xe; ++i) {
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
	}
}


void st7735s_drv::drawVLine(uint16_t x,  uint16_t ys,
		                    uint16_t ye, color_t color) {
	uint16_t dummy;
	change(x, ys);
	change(dummy, ye);

	if (ys <= ye) {
		setFrame(x, ys, x, ye);
		writeCommand(CMD_RAMWR);
		for (int i = ys; i <= ye; ++i) {
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
	} else {
		setFrame(x, ys, x, _lcd.sizeY-1);
		writeCommand(CMD_RAMWR);
		for (int i = ys; i < _lcd.sizeY; ++i) {
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
		setFrame(x, 0, x, ye);
		writeCommand(CMD_RAMWR);
		for (int i = 0; i <= ye; ++i) {
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
	}
}

void st7735s_drv::drawArea(uint16_t xs, uint16_t ys,
						   uint16_t xe, uint16_t ye,
						   bitstream_interface & bs,
						   const color_t * colors) {

	change(xs,ys);
	change(xe,ye);

	if ((xs <= xe) && (ys <= ye)) {
		setFrame(xs, ys, xe, ye);
		int16_t pixels = (xe - xs + 1) * (ye - ys + 1);
		writeCommand(CMD_RAMWR);
		for (int i = 0; i < pixels; i++) {
			color_t   color = colors[bs.getNext()];
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
	} else if (ys > ye) {
		setFrame(xs, ys, xe, _lcd.sizeY-1);
		int16_t pixels = (xe - xs + 1) * (_lcd.sizeY - ys);
		writeCommand(CMD_RAMWR);
		for (int i = 0; i < pixels; i++) {
			color_t  color = colors[bs.getNext()];
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
		setFrame(xs, 0, xe, ye);
		pixels = (xe - xs + 1) * (ye + 1);
		writeCommand(CMD_RAMWR);
		for (int i = 0; i < pixels; i++) {
			color_t   color = colors[bs.getNext()];
			writeData(color  >>  8);
			writeData(color & 0xff);
		}
	} else {
		for (uint16_t y=ys; y <= ye; ++y) {
			setFrame(xs, y, _lcd.sizeX-1, y);
			writeCommand(CMD_RAMWR);
			for (int i=xs; i < _lcd.sizeX; ++i) {
				color_t   color = colors[bs.getNext()];
				writeData(color  >>  8);
				writeData(color & 0xff);
			}
			setFrame(0, y, xe, y);
			writeCommand(CMD_RAMWR);
			for (int i=0; i <= xe; ++i) {
				color_t   color = colors[bs.getNext()];
				writeData(color  >>  8);
				writeData(color & 0xff);
			}
		}
	}
}

void st7735s_drv::fillArea(uint16_t xs, uint16_t ys,
						   uint16_t xe, uint16_t ye, color_t color) {
	zero_bitstream zbs;
	drawArea(xs,ys,xe,ye,zbs, &color);
}


void st7735s_drv::scroll(int16_t rows) {
	_first_row += rows;
	if (_first_row < 0)
		_first_row += _lcd.sizeY;
	else if (_first_row >= _lcd.sizeY)
		_first_row -= _lcd.sizeY;

	writeCommand(CMD_VSCSAD);
	writeData(0);
	writeData(_lcd.offsetY + _first_row);
}

void st7735s_drv::clearScreen(color_t c) {
	scroll(-_first_row); // Reset scrolling
	setFrame(0, 0, _lcd.sizeX-1, _lcd.sizeY-1);
	int16_t pixels =   _lcd.sizeX * _lcd.sizeY;
	writeCommand(CMD_RAMWR);
	uint8_t msb = c >> 8;
	uint8_t lsb = c & 0xff;
	for (int i = 0; i <= pixels; i++) {
		writeData(msb);
		writeData(lsb);
	}
}

void st7735s_drv::inverseColors(bool b) {
	if (b) writeCommand(CMD_INVON);
	else   writeCommand(CMD_INVOFF);
}

void st7735s_drv::change(uint16_t & x, uint16_t & y) {
    switch (_orientation) {
        case LCD::UP:
            y += _lcd.sizeY + _lcd.offsetY - _first_row - 1;
            break;
        case LCD::DOWN:
            y += _first_row;
            break;
        case LCD::LEFT:
        	x += _lcd.sizeY + _lcd.offsetY - _first_row - 1;
        	break;
        case LCD::RIGHT:
        	x += _first_row;
        	break;
    }
    if (y >= _lcd.sizeY) y -= _lcd.sizeY;
    if (x >= _lcd.sizeY) x -= _lcd.sizeY;
}


void st7735s_drv::setFrame(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    switch (_orientation) {
        case LCD::UP:
            xs += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
            ys += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
            xe += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetX);
            ye += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
            break;
        case LCD::DOWN:
            xs += _lcd.offsetX;
            ys += _lcd.offsetY;
            xe += _lcd.offsetX;
            ye += _lcd.offsetY;
            break;
        case LCD::LEFT:
            xs += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
            ys += _lcd.offsetX;
            xe += (_lcd.sizeRamY - _lcd.sizeY - _lcd.offsetY);
            ye += _lcd.offsetX;
            break;
        case LCD::RIGHT:
            xs += _lcd.offsetY;
            ys += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetY);
            xe += _lcd.offsetY;
            ye += (_lcd.sizeRamX - _lcd.sizeX - _lcd.offsetY);
            break;
    }
    writeCommand(CMD_CASET);
    writeData(0); writeData(xs);
    writeData(0); writeData(xe);

    writeCommand(CMD_RASET);
    writeData(0); writeData(ys);
    writeData(0); writeData(ye);
}

void st7735s_drv::writeData(uint8_t data) {
	uint8_t rcv_data;
	_spi.transfer(&data, &rcv_data, 1);
}

void st7735s_drv::writeCommand(uint8_t cmd) {
	_dc_pin.gpioWrite(LOW);
	uint8_t rcv_data;
	_spi.transfer(&cmd, &rcv_data, 1);
	_dc_pin.gpioWrite(HIGH);
}

