//
// Created by andreas on 05.03.25.
//

#include "item_version.h"

void item_version::read(uint32_t* & ptr) {
    _header.value = *ptr++;
    if (_header.item_type != item_type_t::VERSION) {
        throw "VERSION item has wrong item type";
    }
    uint16_t * ptr16 = (uint16_t *)ptr;
    _minor_version = *ptr16++;
    _major_version = *ptr16++;
    if (_header.num_otp_row_enties) {
        _rollback_version = *ptr16++;
        for(int i=0; i < _header.num_otp_row_enties; ++i) {
            uint16_t entry = *ptr16++;
            _otp_row_entries.push_back(entry);
        }
    }
    if ((uint64_t)ptr16 & 0x3) ptr16++;
    ptr = (uint32_t *)ptr16;
}

void item_version::write(uint32_t* & ptr) {
    *ptr++ = _header.value;
    uint16_t * ptr16 = (uint16_t *)ptr;
    *ptr16++ = _minor_version;
    *ptr16++ = _major_version;
    if (_header.num_otp_row_enties) {
        *ptr16++ = _rollback_version;
        for (auto e : _otp_row_entries) {
            *ptr16++ = e;
        }
    }
    if ((uint64_t)ptr16 & 0x3) ptr16++;
    ptr = (uint32_t *)ptr16;
}

uint16_t item_version::size32() {
    return _header.block_size;
}

std::ostream & operator << (std::ostream & os, const item_version & iv) {
    os << iv._header.item_type << ": ";
    os << "minor_version=" << iv._minor_version << ", ";
    os << "major_version=" << iv._major_version;
    if (iv._header.num_otp_row_enties) {
        os << ", otp_row_entries=";
        for (auto e : iv._otp_row_entries) {
            os << e << " ";
        }
    }
    return os;
}
