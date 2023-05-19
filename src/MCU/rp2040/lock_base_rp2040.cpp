/*
 * lock_base_rp2040.h
 *
 * A basic lock implementation for rp2040
 *
 *  Created on: 05.11.2022
 *      Author: Andreas Terstegge
 */

#include "lock_base_rp2040.h"
#include <cassert>

uint32_t lock_base_rp2040::_index = 0;

lock_base_rp2040::lock_base_rp2040() {
    assert(_index < 32);
    _lock = SIO.SPINLOCK + _index;
    _mask = 1 << _index;
    _index++;
}

lock_base_rp2040::~lock_base_rp2040() {
    unlock();
    _index--;
}
