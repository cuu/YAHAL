/*
 * constbitstream.h
 *
 *  Created on: 12.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _ZERO_BITSTREAM_H_
#define _ZERO_BITSTREAM_H_

#include "bitstream_interface.h"

class zero_bitstream : public bitstream_interface {
public:
    virtual ~zero_bitstream() { }
	uint16_t getNext(uint8_t = 0) { return 0; }
};

#endif // _ZERO_BITSTREAM_H_ */
