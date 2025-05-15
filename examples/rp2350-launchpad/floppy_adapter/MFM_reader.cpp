//
// Created by andreas on 13.05.25.
//

#include "MFM_reader.h"

MFM_reader::MFM_reader(uint8_t * data_ptr)
      : _read_gap4a (*this, -10, 60, 800,                  &_read_sync1),
        _read_sync1 (*this, -20,                           &_read_iam),
        _read_iam   (*this, -30, {0xc2, 0xc2, 0xc2, 0xfc}, &_read_gap1),
        _read_gap1  (*this, -40, 30, 500,                  &_read_sync2),
        _read_sync2 (*this, -50,                           &_read_id_am),
        _read_id_am (*this, -60, {0xa1, 0xa1, 0xa1, 0xfe}, &_read_am),
        _read_am    (*this,      6,                        &_read_gap2),
        _read_gap2  (*this, -70, 18, 200,                  &_read_sync3),
        _read_sync3 (*this, -80,                           &_read_d_am),
        _read_d_am  (*this, -90, {0xa1, 0xa1, 0xa1, 0xfb}, &_read_data),
        _read_data  (*this,      514,                      &_read_gap3),
        _read_gap3  (*this, -100,60, 800,                  &_read_sync2),
        _data_ptr(data_ptr) {

    // Set initial state
    setState(&_read_gap4a);
}
