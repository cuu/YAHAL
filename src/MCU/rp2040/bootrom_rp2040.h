//
// Created by andreas on 01.01.26.
//

#ifndef _BOOTROM_RP2040_H
#define _BOOTROM_RP2040_H

#include <array>
#include <cstdint>
#include <functional>
#include "board.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

class bootrom_rp2040 {
public:

    static uint32_t popcount(uint32_t val) {
        using T = uint32_t (*) (uint32_t);
        return ((T) find_function(rom_code('P', '3')))(val);
    }

    static uint32_t reverse(uint32_t val) {
        using T = uint32_t (*) (uint32_t);
        return ((T) find_function(rom_code('R', '3')))(val);
    }

    // Flash access functions
    /////////////////////////
    // These functions are typically called from methods in RAM,
    // because the code to handle e.g. flash programming must not
    // be located in the FLASH. This is why these methods are all
    // forced to be inline!

    static void FORCE_INLINE connect_internal_flash() {
        using T = void (*) ();
        return ((T) find_function(rom_code('I', 'F')))();
    }

    static void FORCE_INLINE flash_exit_xip() {
        using T = void (*) ();
        return ((T) find_function(rom_code('E', 'X')))();
    }

    static void FORCE_INLINE flash_range_erase(uint32_t addr,
                                               size_t   count,
                                               uint32_t block_size,
                                               uint8_t  block_cmd) {
        using T = void (*) (uint32_t, size_t, uint32_t, uint8_t);
        return ((T) find_function(rom_code('R', 'E')))(addr, count, block_size, block_cmd);
    }

    static void FORCE_INLINE flash_range_program(uint32_t   addr,
                                                 uint8_t *  data,
                                                 size_t     count) {
        using T = void (*) (uint32_t, uint8_t *, size_t);
        return ((T) find_function(rom_code('R', 'P')))(addr, data, count);
    }

    static void FORCE_INLINE flash_flush_cache() {
        using T = void (*) ();
        return ((T) find_function(rom_code('F','C')))();
    }

    static void FORCE_INLINE flash_enter_cmd_xip() {
        using T = void (*) ();
        return ((T) find_function(rom_code('C','X')))();
    }

    static std::array<uint8_t, 8> read_unique_id();
    static std::array<char,   17> read_unique_id_string();

private:

    static constexpr uint32_t rom_code(char c1, char c2) {
        return (c2 << 8) | c1;
    }

    static inline void * find_function(uint32_t code) {
        using T = void * (*)(uint16_t * table, uint32_t code);
        auto func  = (T)(_rom_header->lookup_function);
        auto table = (uint16_t *)(_rom_header->function_table);
        return func(table, code);
    }

    // RP2040 ROM layout for the first 26 bytes
    static struct __attribute__((__packed__)) rom_header_t {
        uint32_t *  intial_sp;
        void        (*reset_handler)();
        void        (*nmi_handler)();
        void        (*hard_fault_handler)();
        uint8_t     magic[3];
        uint8_t     version;
        uint16_t    function_table;
        uint16_t    data_table;
        uint16_t    lookup_function;
    } * _rom_header;
    static_assert(sizeof(rom_header_t) == 26);

    static uint8_t _tx_buffer[13];
    static uint8_t _rx_buffer[13];
};

#pragma GCC diagnostic push

#endif // _BOOTROM_RP2040_H
