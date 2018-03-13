/*
 * pixelstreamconst.h
 *
 *  Created on: 13.03.2018
 *      Author: student
 */

#ifndef _PIXELSTREAMCONST_H_
#define _PIXELSTREAMCONST_H_

#include "lcd_interface.h"

class pixel_stream_const : public pixel_stream
{
public:
    pixel_stream_const(color_t c) : color(c) { }
    virtual ~pixel_stream_const() = default;

    inline color_t getColorType() override {
        return COLOR_TYPE(color);
    }
    inline color_t getNext() override {
        return color;
    }
    inline void reset() { }

private:
    color_t color;
};

#endif /* _PIXELSTREAMCONST_H_ */
