// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
#ifndef ELF2UF2_UF2_OFSTREAM_H
#define ELF2UF2_UF2_OFSTREAM_H

#include <fstream>
#include <cstring>
#include <array>
#include <string>
#include "uf2_structs.h"

using std::ofstream;
using std::array;
using std::ios;
using std::string;

#define PAGE_SIZE 256

class uf2_ofstream : public std::ofstream {
public:
    // CTOR
    explicit uf2_ofstream(string & filename)
    : ofstream(filename, ios::binary | ios::out) {
        // Initialize basic stuff in UF2 block
        _uf2_block.magicStart0 = UF2_MAGIC_START0;
        _uf2_block.magicStart1 = UF2_MAGIC_START1;
        _uf2_block.magicEnd    = UF2_MAGIC_END;
        _uf2_block.payloadSize = PAGE_SIZE;
        // Pointer to the next extension flag
        _extension_flags_ptr   = _uf2_block.data + PAGE_SIZE;
    };

    void set_flag(const uint32_t flag) {
        _uf2_block.flags = flag;
    }

    void set_target_addr(const uint32_t addr) {
        _uf2_block.targetAddr = addr;
    }

    void set_block_no(const uint32_t n) {
        _uf2_block.blockNo = n;
    }

    void set_num_blocks(const uint32_t n) {
        _uf2_block.numBlocks = n;
    }

    void set_filesize(const uint32_t s) {
        _uf2_block.filesize_family.filesize = s;
    }

    void set_family_id(const family_id_t id) {
        _uf2_block.filesize_family.family_id = id;
        // Set related flag
        _uf2_block.flags |= UF2_FLAG_FAMILY_ID_PRESENT;
    }

    void set_data(const array<char, PAGE_SIZE> & data) {
        memcpy(_uf2_block.data, data.data(), PAGE_SIZE);
    }

    bool add_extension_flag(const uint8_t  * data, uint8_t len) {
        // Check if the first by is the length
        if (data[0] != len)
            return false;
        // Check if new flag fits into memory
        if (_extension_flags_ptr-_uf2_block.data + len > sizeof(_uf2_block.data))
            return false;
        // copy the new flag
        memcpy(_extension_flags_ptr, data, len);
        // Increment the pointer
        _extension_flags_ptr += len;
        // Switch on the related flag
        _uf2_block.flags |= UF2_FLAG_EXTENSION_FLAGS_PRESENT;
        return true;
    }

    void clear_extension_flags() {
        // Switch off related flag
        _uf2_block.flags &= ~UF2_FLAG_EXTENSION_FLAGS_PRESENT;
        // Reset extension flag pointer
        _extension_flags_ptr = _uf2_block.data + PAGE_SIZE;
        // Set memory area in UF2 block to zero
        memset(_extension_flags_ptr, 0, sizeof(_uf2_block.data) -
                        (_extension_flags_ptr-_uf2_block.data));
    }

    void write_block(uint8_t * data) {
        memcpy(_uf2_block.data, data, PAGE_SIZE);
        write((char *)&_uf2_block, sizeof(UF2_Block));
    }

private:
    UF2_Block   _uf2_block {0};
    uint8_t *   _extension_flags_ptr;
};


#endif //ELF2UF2_UF2_OFSTREAM_H
