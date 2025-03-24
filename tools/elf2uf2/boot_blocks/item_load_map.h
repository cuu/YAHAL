//
// Created by andreas on 12.03.25.
//

#ifndef ELF2UF2_ITEM_LOAD_MAP_H
#define ELF2UF2_ITEM_LOAD_MAP_H

#include "item_base.h"
#include <vector>

union __attribute__((packed)) load_map_t {
    struct __attribute__((packed)) {
        item_type_t item_type;
        uint16_t    block_size;
        uint8_t     num_entries : 7;
        uint8_t     is_absolute : 1;
    };
    uint32_t value;
};
static_assert(sizeof(load_map_t) == 4);

std::ostream & operator << (std::ostream & os, const load_map_t &);

struct __attribute__((packed)) load_map_entry_t {
    union {
        uint32_t storage_start_addr;
        uint32_t storage_start_addr_rel;
    };
    uint32_t runtime_start_addr;
    union {
        uint32_t storage_end_addr;
        uint32_t size;
    };
};
static_assert(sizeof(load_map_entry_t) == 12);


class item_load_map : public item_base {
public:
    item_load_map();

    // Getter / Setter
    inline const uint32_t get_num_entries() const {
        return _header.num_entries;
    }
    inline void set_absolute(bool is_absolute) {
        _header.is_absolute = is_absolute;
    }
    inline bool get_absolute() const {
        return _header.is_absolute;
    }
    inline void add_load_map_item(const load_map_entry_t & entry) {
        _load_map_entries.push_back(entry);
        _header.num_entries += 1;
        _header.block_size  += 3;
    }

    void read (uint32_t* & ptr) override;
    void write(uint32_t* & ptr) override;
    uint16_t size32() const override;

    inline item_type_t get_type() const override {
        return _header.item_type;
    }

    friend std::ostream & operator << (std::ostream & os, const item_load_map &);

private:
    load_map_t _header {};
    std::vector<load_map_entry_t> _load_map_entries;
};

#endif // ELF2UF2_ITEM_LOAD_MAP_H
