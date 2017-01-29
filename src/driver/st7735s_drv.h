/*
 * st7735s.h
 *
 *  Created on: 29.02.2016
 *      Author: Andreas Terstegge
 */

#ifndef _ST7735S_H_
#define _ST7735S_H_

//#include "st7735s_drv_config.h"
#include "spi_interface.h"
#include "gpio_interface.h"
#include "lcd_interface.h"

class st7735s_drv : public lcd_interface {

  public:
    // User interface
    /////////////////
    st7735s_drv(spi_interface  & spi,
    			gpio_pin       & rst_pin,
				gpio_pin       & dc_pin,
				lcd_config     & lcd);

    virtual ~st7735s_drv();

    uint16_t getSizeX();
	uint16_t getSizeY();

    void setOrientation(LCD::Orientation o);

	// Translate from 24bit RGB to color_t
    color_t rgb24toColor(uint32_t rgb24);

	// x and y range from 0 to getX/YSize() - 1
	void drawPixel(uint16_t x,  uint16_t y,  color_t color);
	void drawHLine(uint16_t xs, uint16_t y,  uint16_t xe, color_t c);
	void drawVLine(uint16_t x,  uint16_t ys, uint16_t ye, color_t c);

	void drawArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
				   bitstream_interface & bs, const color_t * colors);
	void fillArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
				   color_t c);

	void scroll(int16_t lines);
	void clearScreen(color_t c);
	void inverseColors(bool b);

  private:

    void change  (uint16_t & x, uint16_t & y);
    void setFrame(uint16_t   xs, uint16_t  ys, uint16_t xe, uint16_t ye);

    void writeData   (uint8_t data);
    void writeCommand(uint8_t cmd);

    spi_interface  & _spi;
    gpio_pin       & _rst_pin;
    gpio_pin       & _dc_pin;
    lcd_config	   & _lcd;

    LCD::Orientation _orientation;
    int8_t			 _first_row; // Vertical scroll start address
};

#endif // _ST7735S_H_
