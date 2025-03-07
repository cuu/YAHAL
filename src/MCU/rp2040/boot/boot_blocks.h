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
#ifndef _BOOT_BLOCKS_H_
#define _BOOT_BLOCKS_H_

#include <cstdint>
#include <array>

// These definitions might interfere with the following enums...
#undef RP2040
#undef RP2350

namespace BLOCKS {

    template<std::size_t Size>
    using blocks = std::array<uint32_t, Size>;

    constexpr auto copy(const uint32_t *start, const uint32_t *end, uint32_t *dst) {
        while (start < end) {
            *dst++ = *start++;
        }
    }

    template<std::size_t N>
    constexpr auto append(const blocks<N> &arr, const uint32_t val) {
        blocks<N + 1> res{};
        copy(arr.begin(), arr.end(), res.begin());
        res[N] = val;
        return res;
    }

    // Specific block methods and enums

    template<std::size_t N>
    constexpr auto HEADER(const blocks<N> &arr) {
        return append(arr, 0xffffded3);
    }

    template<std::size_t N>
    constexpr auto FOOTER(const blocks<N> &arr) {
        return append(arr, 0xab123579);
    }

    template<std::size_t N>
    constexpr auto LAST_ITEM(const blocks<N> &arr, uint16_t other_items_size) {
        return append(arr, 0x000000ff + (other_items_size << 8));
    }

    template<std::size_t N>
    constexpr auto LINK(const blocks<N> &arr, int offset) {
        return append(arr, offset);
    }


    template<std::size_t N>
    constexpr auto VERSION(const blocks<N> &arr, uint16_t major, uint16_t minor) {
        auto tmp = append(arr, 0x00000248);
        return append(tmp, ((major << 16) | minor));
    }


    enum class image_type : uint32_t {
        INVALID = 0 << 16,
        TYPE_EXE = 1 << 16,
        TYPE_DATA = 2 << 16
    };

    enum class exe_security : uint32_t {
        UNSPECIFIED = 0u << 20,
        SEC_NS = 1u << 20,
        SEC_S = 2u << 20
    };

    enum class exe_cpu : uint32_t {
        CPU_ARM = 0u << 24,
        CPU_RISCV = 1u << 24
    };

    enum class exe_chip : uint32_t {
        CHIP_RP2040 = 0u << 28,
        CHIP_RP2350 = 1u << 28
    };

    enum class exe_tbyb : uint32_t {
        FALSE = 0u << 31,
        TRUE = 1u << 31
    };

    template<std::size_t N>
    constexpr auto IMAGE_DEF(const blocks<N> &arr, const image_type type,
                             const exe_security sec,
                             const exe_cpu cpu,
                             const exe_chip chip,
                             const exe_tbyb tbyb = exe_tbyb::FALSE) {
        return append(arr, 0x00000142 + (uint32_t) type + (uint32_t) sec +
                           (uint32_t) cpu + (uint32_t) chip +
                           (uint32_t) tbyb);
    }

};

#endif // _BOOT_BLOCKS_H_
