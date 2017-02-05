/*
 * lcd_interface.h
 *
 *  Created on: 05.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

#include <stdint.h>
#include <bitstream_interface.h>

typedef uint16_t color_t;

namespace LCD {
  enum Orientation { UP, DOWN, LEFT, RIGHT };

  const uint8_t	RGB_COLOR_FILTER = 0x00;
  const uint8_t BGR_COLOR_FILTER = 0x01;
}

struct lcd_config {
	uint16_t	sizeX;
	uint16_t	sizeY;
	uint16_t	sizeRamX;
	uint16_t	sizeRamY;
	uint8_t		offsetX;
	uint8_t		offsetY;
	uint8_t		flags;
};


class lcd_interface {
  public:
    virtual ~lcd_interface() { }

	virtual uint16_t getSizeX() = 0;
	virtual uint16_t getSizeY() = 0;

	virtual void setOrientation(LCD::Orientation o) = 0;

	// Translate from 24bit RGB to our color_t
	virtual color_t rgb24toColor(uint32_t rgb24) = 0;

	// x and y range from 0 to getX/YSize() - 1
	virtual void drawPixel(uint16_t x,  uint16_t y,  color_t color) = 0;
	virtual void drawHLine(uint16_t xs, uint16_t y,  uint16_t xe, color_t c) = 0;
	virtual void drawVLine(uint16_t x,  uint16_t ys, uint16_t ye, color_t c) = 0;

	virtual void drawArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
						   bitstream_interface & bs, const color_t * colors) = 0;
	virtual void fillArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
						   color_t c) = 0;

	// lines > 0 -> scroll up, lines < 0 -> scroll down
	virtual void scroll(int16_t lines)  = 0;
	virtual void clearScreen(color_t c) = 0;
};

#endif // _LCD_INTERFACE_H_
