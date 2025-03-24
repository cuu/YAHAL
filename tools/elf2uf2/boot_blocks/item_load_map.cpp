//
// Created by andreas on 12.03.25.
//

#include "item_load_map.h"

#include <iomanip>
#define HEX_FORMAT(width) "0x" << \
    std::setw( width ) << std::setfill( '0' ) << std::hex << std::right

std::ostream & operator << (std::ostream & os, const load_map_t &lm) {
    os << lm.item_type   << ": ";
    os << "absolute="    << (bool)lm.is_absolute << ", ";
    os << "num_entries=" << (int)lm.num_entries;
    return os;
}

item_load_map::item_load_map() {
    _header.item_type   = item_type_t::LOAD_MAP;
    _header.block_size  = 1;
    _header.num_entries = 0;
}

void item_load_map::read(uint32_t* & ptr) {
    auto * id_ptr = (load_map_t *)ptr;
    if (id_ptr->item_type != item_type_t::LOAD_MAP) {
        throw "LOAD_MAP item has wrong item type";
    }
    if (id_ptr->block_size < 1 || ((id_ptr->block_size-1)%3 != 0)) {
        throw "LOAD_MAP item has wrong size";
    }
    if (id_ptr->block_size != (1+3*id_ptr->num_entries)) {
        throw "LOAD_MAP blocksize not fitting to num_entries";
    }
    _header.value = *ptr++;
    for(int i=0; i < id_ptr->num_entries; ++i) {
        load_map_entry_t e;
        e.storage_start_addr = *ptr++;
        e.runtime_start_addr = *ptr++;
        e.storage_end_addr   = *ptr++;
        _load_map_entries.push_back(e);
    }
}

void item_load_map::write(uint32_t* & ptr) {
    *ptr++ = _header.value;
    for (auto & e : _load_map_entries) {
        *ptr++ = e.storage_start_addr;
        *ptr++ = e.runtime_start_addr;
        *ptr++ = e.storage_end_addr;
    }
}

uint16_t item_load_map::size32() const {
    return _header.block_size;
}

std::ostream & operator << (std::ostream & os, const item_load_map & lm) {
    os << lm._header;
    int entry_no = 0;
    for(auto & e : lm._load_map_entries) {
        os << std::endl;
        os << "  [" << entry_no++ << "]:";
        if (lm.get_absolute()) {
            os << "storage_start=" << HEX_FORMAT(8) << e.storage_start_addr << ", ";
        } else {
            os << "storage_start_rel=" << HEX_FORMAT(8) << e.storage_start_addr_rel << ", ";
        }
        os << "runtime_start=" << HEX_FORMAT(8) << e.runtime_start_addr << ", ";
        if (lm.get_absolute()) {
            os << "storage_end=" << HEX_FORMAT(8) << e.storage_end_addr << ", ";
        } else {
            os << "size=" << HEX_FORMAT(8) << e.size;
        }
    }
    return os;
}
