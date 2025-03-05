//
// Created by andreas on 05.03.25.
//

#ifndef ELF2UF2_BLOCK_H
#define ELF2UF2_BLOCK_H

#include <cstdint>
#include <vector>
#include "item_base.h"

const uint32_t BLOCK_HEADER = 0xffffded3;
const uint32_t BLOCK_FOOTER = 0xAB123579;

class block {
public:

    uint32_t * read (uint32_t* & ptr);
    void write(uint32_t* & ptr);

    std::vector<item_base *> _items;

private:

    uint32_t * _start_pointer;
};

#endif //ELF2UF2_BLOCK_H
