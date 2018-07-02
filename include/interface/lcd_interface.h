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
//  This file defines a generic interface for
//  LCD drivers.

#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

#include <stdint.h>
#include "yahal_assert.h"

// Colors use a 32-bit integer. The upper 8 bits
// define the concrete color type.
typedef uint32_t color_t;
#define COLOR_TYPE(c) (c & 0xff000000)
#define COLOR_RGB(c)  (c & 0x00ffffff)

namespace LCD {
const uint32_t COLORTYPE_RGB888 = 0x00000000;
const uint32_t COLORTYPE_RGB565 = 0x01000000;
const uint32_t COLORTYPE_RGB555 = 0x02000000;
}

// Small interface for a pixel data stream
class pixel_stream {
public:
    virtual color_t  getColorType() = 0;
    virtual color_t  getNext() = 0;
    virtual void     reset() = 0;

protected:
    ~pixel_stream() = default;
};


class lcd_interface {
public:

    // Getters for screen dimensions
    virtual uint16_t getSizeX() = 0;
    virtual uint16_t getSizeY() = 0;

    // Basic graphic methods
    // x and y range from 0 to getX/YSize() - 1
    // It is assumed that xs < xe and ys < ye !!
    virtual void drawPixel(uint16_t xs, uint16_t ys, color_t color) = 0;
    virtual void drawHLine(uint16_t xs, uint16_t ys, uint16_t xe, color_t c) = 0;
    virtual void drawVLine(uint16_t xs, uint16_t ys, uint16_t ye, color_t c) = 0;

    // Fill rectangle with data coming from a pixel stream
    virtual void drawArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           pixel_stream & ps) = 0;

    // Fill rectangle with a specific color
    virtual void fillArea (uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
                           color_t c) = 0;

    // Translate from one color_t to another
    color_t convertColor(color_t c, color_t return_type ) {
        color_t in_type = COLOR_TYPE(c);

        // Do nothing if color types match
        if (in_type == return_type) return c;

        // RGB888 -> RGB565
        if (in_type     == LCD::COLORTYPE_RGB888 &&
            return_type == LCD::COLORTYPE_RGB565) {
            return( ((c & 0x00f80000) >> 8) |
                    ((c & 0x0000fc00) >> 5) |
                    ((c & 0x000000f8) >> 3) |
                    LCD::COLORTYPE_RGB565 );
        }
        yahal_assert(0);
        return 0;
    }

protected:
    virtual ~lcd_interface() = default;
};

#endif // _LCD_INTERFACE_H_
