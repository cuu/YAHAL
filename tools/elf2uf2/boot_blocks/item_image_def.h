//
// Created by andreas on 05.03.25.
//

#ifndef ELF2UF2_ITEM_IMAGE_DEF_H
#define ELF2UF2_ITEM_IMAGE_DEF_H

#include <cstdint>
#include <iostream>
#include "item_base.h"

enum class image_type_t : uint8_t {
    INVALID = 0,
    EXE     = 1,
    DATA    = 2,
};

enum class security_t : uint8_t {
    UNSPECIFIED = 0,
    NS          = 1,
    S           = 2,
};

enum class cpu_t : uint8_t {
    ARM     = 0,
    RISCV   = 1
};

enum class chip_t : uint8_t {
    RP2040  = 0,
    RP2350  = 1
};

union __attribute__((packed)) image_def_t {
    struct __attribute__((packed)) {
        item_type_t item_type;
        uint8_t block_size;
        image_type_t image_type : 4;
        security_t security     : 2;
        uint16_t                : 2;
        cpu_t cpu               : 3;
        uint16_t                : 1;
        chip_t chip             : 3;
        uint16_t tbyb           : 1;
    };
    uint32_t value;
};
static_assert(sizeof(image_def_t) == 4);


std::ostream & operator << (std::ostream & os, const image_type_t &);
std::ostream & operator << (std::ostream & os, const security_t &);
std::ostream & operator << (std::ostream & os, const cpu_t &);
std::ostream & operator << (std::ostream & os, const chip_t &);
std::ostream & operator << (std::ostream & os, const image_def_t &);


class item_image_def : public item_base {
public:
    item_image_def();

    // Getter / Setter
    inline image_type_t get_image_type() const {
        return _header.image_type;
    }
    inline void set_image_type(image_type_t type) {
        _header.image_type = type;
    }
    inline security_t get_security() const {
        return _header.security;
    }
    inline void set_security(security_t sec) {
        _header.security = sec;
    }
    inline cpu_t get_cpu() const {
        return _header.cpu;
    }
    inline void set_cpu(cpu_t cpu) {
        _header.cpu = cpu;
    }
    inline chip_t get_chip() const {
        return _header.chip;
    }
    inline void set_chip(chip_t chip) {
        _header.chip = chip;
    }
    inline bool get_tbyb() const {
        return _header.tbyb;
    }
    inline void set_tbyb(bool v) {
        _header.tbyb = v;
    }

    void read (uint32_t* & ptr) override;
    void write(uint32_t* & ptr) override;
    uint16_t size32() override;

    inline item_type_t get_type() override {
        return _header.item_type;
    }

    friend std::ostream & operator << (std::ostream & os, const item_image_def &);

private:
    image_def_t _header {};
};

#endif //ELF2UF2_ITEM_IMAGE_DEF_H
