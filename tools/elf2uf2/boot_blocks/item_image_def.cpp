//
// Created by andreas on 05.03.25.
//

#include "item_image_def.h"

std::ostream & operator << (std::ostream & os, const image_type_t &it) {
    os << "image_type=";
    switch (it) {
        case image_type_t::INVALID:
            os << "INVALID"; break;
        case image_type_t::EXE:
            os << "EXE"; break;
        case image_type_t::DATA:
            os << "DATA"; break;
    }
    return os;
}

std::ostream & operator << (std::ostream & os, const security_t & s) {
    os << "security=";
    switch (s) {
        case security_t::UNSPECIFIED:
            os << "UNSPECIFIED"; break;
        case security_t::NS:
            os << "NS"; break;
        case security_t::S:
            os << "S"; break;
    }
    return os;
}

std::ostream & operator << (std::ostream & os, const cpu_t & cpu) {
    os << "cpu=";
    switch (cpu) {
        case cpu_t::ARM:
            os << "ARM"; break;
        case cpu_t::RISCV:
            os << "RISCV"; break;
    }
    return os;
}

std::ostream & operator << (std::ostream & os, const chip_t & chip) {
    os << "cpu=";
    switch (chip) {
        case chip_t::RP2040:
            os << "RP2040"; break;
        case chip_t::RP2350:
            os << "RP2350"; break;
    }
    return os;
}

std::ostream & operator << (std::ostream & os, const image_def_t &id) {
    os << id.item_type << ": ";
    os << id.image_type << ", ";
    os << id.security << ", ";
    os << id.cpu << ", ";
    os << id.chip << ", ";
    os << "tbyb=" << id.tbyb;
    return os;
}


item_image_def::item_image_def() : header(_header) {
    _header.item_type  = item_type_t::IMAGE_DEF;
    _header.block_size = 1;
}


void item_image_def::read(uint32_t* & ptr) {
    _header.value = *ptr++;
    if (_header.item_type != item_type_t::IMAGE_DEF) {
        throw "IMAGE item has wrong item type";
    }
    if (_header.block_size != 1) {
        throw "IMAGE item has wrong size";
    }
}

void item_image_def::write(uint32_t* & ptr) {
    *ptr++ = _header.value;
}

uint16_t item_image_def::size32() {
    return _header.block_size;
}

std::ostream & operator << (std::ostream & os, const item_image_def & id) {
    os << id._header;
    return os;
}
