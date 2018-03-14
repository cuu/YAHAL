/*
 * pixel_stream_rgb565.h
 *
 *  Created on: 13.03.2018
 *      Author: student
 */

#ifndef _PIXEL_STREAM_RGB565_H_
#define _PIXEL_STREAM_RGB565_H_

#include "lcd_interface.h"
#include <cstdlib>

class pixel_stream_rgb565 : public pixel_stream
{
public:

    pixel_stream_rgb565(const uint16_t *data, size_t size)
    : _data(data), _size(size), _index(0) { }

    virtual ~pixel_stream_rgb565() { }

    inline color_t getColorType() override {
        return LCD::COLORTYPE_RGB565;
    }

    inline color_t getNext() override {
        return _data[_index++] | LCD::COLORTYPE_RGB565;
    }

    inline void reset() { _index = 0; }

private:

    const uint16_t * _data;
    size_t           _size;
    size_t           _index;
};

#endif /* _PIXEL_STREAM_RGB565_H_ */
