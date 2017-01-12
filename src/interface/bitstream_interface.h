/*
 * bitstream_interface.h
 *
 *  Created on: 12.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _BITSTREAM_INTERFACE_H_
#define _BITSTREAM_INTERFACE_H_

class bitstream_interface {
  public:
	// Get the next n bits out of a bitstream.
	// If n is 0 (or not given), a default number
	// of bits is returned.
	virtual uint16_t getNext(uint8_t n = 0) = 0;
};

#endif // _BITSTREAM_INTERFACE_H_
