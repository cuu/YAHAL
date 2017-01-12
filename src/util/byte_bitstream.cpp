/*
 * bytebitstream.cpp
 *
 *  Created on: 12.03.2016
 *      Author: Andreas Terstegge
 */

#include "byte_bitstream.h"

byte_bitstream::byte_bitstream(uint8_t bitsPerRequest,
							   const uint8_t * data,
							   uint8_t bitsPerByte)
: _bitsPerRequest(bitsPerRequest), _data(data) {

	_start_mask = 1 << (bitsPerByte-1);
	_mask		= _start_mask;
	_byte_index = 0;
}

uint16_t byte_bitstream::getNext(uint8_t b) {
	uint16_t result = 0;
	uint8_t  bits = b ? b : _bitsPerRequest;
	for (int i=0; i < bits; ++i) {
		if (_mask == 0) {
			_mask = _start_mask;
			_byte_index++;
		}
		bool b = _data[_byte_index] & _mask;
		_mask  >>= 1;
		result <<= 1;
		result  |= b;
	}
	return result;
}
