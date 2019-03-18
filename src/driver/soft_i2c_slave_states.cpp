/*
 * soft_i2c_slave_states.cpp
 *
 *  Created on: 16.03.2019
 *      Author: student
 */

#include "soft_i2c_slave_states.h"
#include "soft_i2c_slave.h"

namespace I2C {

////////////////
// STATE base //
////////////////
void STATE::start() {
    _context.setState(&_context._read_addr);
}
void STATE::stop() {
    _context.setState(&_context._idle);
    _context._stop(_context._user_ptr);
}

////////////////
// State IDLE //
////////////////
void IDLE::enter() {
    // Make sure we do not touch the bus...
    _context._sda.gpioWrite(HIGH);
    _context._scl.gpioWrite(HIGH);
}

/////////////////////
// State READ_ADDR //
/////////////////////
void READ_ADDR::enter() {
    _data     = 0;
    _bit_mask = 0x80;
    _context._byte_index = 0;
}
void READ_ADDR::high() {
    _data |= _bit_mask;
    _bit_mask >>= 1;
}
void READ_ADDR::low() {
    _bit_mask >>= 1;
}
void READ_ADDR::scl_falling() {
    if (!_bit_mask) {
        // process device address
        _context._send = _data & 0x01;
        _data >>= 1;
        _context._ack  = (_data == _context._i2c_address);
        // Write the ACK to master
        _context.setState(&_context._write_ack);
    }
}

/////////////////////
// State WRITE_ACK //
/////////////////////
void WRITE_ACK::enter() {
    _context._sda.gpioDisableIrq();
    _context._sda.gpioWrite(!_context._ack);
    _context._sda.gpioEnableIrq();
    return;
}
void WRITE_ACK::scl_falling() {
    // release SDA line (in case of ACK!)
    _context._sda.gpioWrite(HIGH);
    // Do not clear SDA interrupts here !
    if (_context._ack) {
        if (_context._send) {
            _context.setState(&_context._write_data );
        } else {
            _context.setState(&_context._read_data );
        }
    } else {
        _context.setState(&_context._idle);
    }
}

/////////////////////
// State READ_DATA //
/////////////////////
void READ_DATA::enter() {
    _data     = 0;
    _bit_mask = 0x80;
}
void READ_DATA::high() {
    _data |= _bit_mask;
    _bit_mask >>= 1;
}
void READ_DATA::low() {
    _bit_mask >>= 1;
}
void READ_DATA::scl_falling() {
    if (!_bit_mask) {
        _context._ack =  _context._receive(_context._byte_index++, _data,
                                           _context._user_ptr);
        _context.setState(&_context._write_ack);
    }
}

//////////////////////
// State WRITE_DATA //
//////////////////////
void WRITE_DATA::enter() {
    // We are controlling the SDA line now, so no interrupts
    _context._sda.gpioDisableIrq();
    // Read in the byte to send
    _data = _context._transmit(_context._byte_index++, _context._user_ptr);
    // send first bit
    _bit_mask = 0x80;
    _context._sda.gpioWrite(_data & _bit_mask);
    _bit_mask >>= 1;
}
void WRITE_DATA::scl_falling() {
    if (_bit_mask) {
        // send next bit
        _context._sda.gpioWrite(_data & _bit_mask);
        _bit_mask >>= 1;
    } else {
        // release SDA line
        _context._sda.gpioWrite(HIGH);
        _context._sda.gpioEnableIrq();
        _context.setState(&_context._read_ack);
    }
}

////////////////////
// State READ_ACK //
////////////////////
void READ_ACK::high() {
    _context._ack = false;
}
void READ_ACK::low() {
    _context._ack = true;
}
void READ_ACK::scl_falling() {
    if (_context._ack) {
        _context.setState(&_context._write_data);
    } else {
        _context.setState(&_context._idle);
    }
}

} // namespace
