/*
 * bytebitstream.h
 *
 *  Created on: 12.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _BYTEBITSTREAM_H_
#define _BYTEBITSTREAM_H_

#include <stdint.h>
#include "bitstream_interface.h"

class byte_bitstream : public bitstream_interface {
  public:

	byte_bitstream(uint8_t bitsPerRequest,
				   const uint8_t * data,
				   uint8_t bitsPerByte);
	virtual ~byte_bitstream() { }

	uint16_t getNext(uint8_t bits=0);

  private:
	uint8_t		_bitsPerRequest;
	const uint8_t	*	_data;
	uint32_t	_byte_index;
	uint8_t		_start_mask;
	uint8_t		_mask;
};

#endif // _BYTEBITSTREAM_H_
