//
// Created by andreas on 05.03.25.
//

#ifndef ELF2UF2_ITEM_VERSION_H
#define ELF2UF2_ITEM_VERSION_H

#include <vector>
#include "item_base.h"

union __attribute__((packed)) version_t {
    struct __attribute__((packed)) {
        item_type_t item_type;
        uint8_t block_size;
        uint8_t nil;
        uint8_t num_otp_row_enties;
    };
    uint32_t value;
};
static_assert(sizeof(version_t) == 4);

class item_version : public item_base {
public:

    inline uint16_t get_minor_version() const {
        return _minor_version;
    }
    inline void set_minor_version(uint16_t v) {
        _minor_version = v;
    }
    inline uint16_t get_major_version() const {
        return _major_version;
    }
    inline void set_major_version(uint16_t v) {
        _major_version = v;
    }
    inline void add_opt_row_entry(uint16_t e) {
        _otp_row_entries.push_back(e);
        _header.block_size = 2 + _otp_row_entries.size()/2;
    }

    void read (uint32_t* & ptr) override;
    void write(uint32_t* & ptr) override;
    uint16_t size32() override;

    inline item_type_t get_type() override {
        return _header.item_type;
    }

    friend std::ostream & operator << (std::ostream & os, const item_version &);

private:

    version_t               _header;
    uint16_t                _minor_version;
    uint16_t                _major_version;
    uint16_t                _rollback_version;
    std::vector<uint16_t>   _otp_row_entries;
};

#endif //ELF2UF2_ITEM_VERSION_H
