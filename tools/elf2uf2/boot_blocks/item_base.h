//
// Created by andreas on 05.03.25.
//

#ifndef ELF2UF2_ITEM_BASE_H
#define ELF2UF2_ITEM_BASE_H

#include <cstdint>
#include <iostream>

enum class item_type_t : uint8_t {
    NEXT_BLOCK_OFFSET =     0x41,
    IMAGE_DEF =             0x42,
    VECTOR_TABLE =          0x03,
    ENTRY_POINT =           0x44,
    ROLLING_WINDOW_DELTA =  0x05,
    LOAD_MAP =              0x06,
    HASH_DEF =              0x47,
    VERSION =               0x48,
    SIGNATURE =             0x09,
    PARTITION_TABLE =       0x0a,
    HASH_VALUE =            0x4b,
    SALT =                  0x0c,
    IGNORED =               0xfe,
    LAST =                  0xff
};

std::ostream & operator << (std::ostream & os, const item_type_t & it);

class item_base {
public:
    virtual void read (uint32_t* & ptr) = 0;
    virtual void write(uint32_t* & ptr) = 0;
    virtual uint16_t size32() = 0;
    virtual item_type_t get_type() = 0;
};


#endif //ELF2UF2_ITEM_BASE_H
