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
#ifndef _MULTICORE_RP2350_H_
#define _MULTICORE_RP2350_H_

#include <cstdint>
#include <functional>

class multicore_rp2350 {
public:

    // FIFO methods
    static void fifo_push_blocking(uint32_t val);
    static uint32_t fifo_pop_blocking();
    static uint32_t fifo_drain();

    // Start code on Core 1
    static void start_on_core1(
            std::function<void(void)> func,
            uint8_t * stack = nullptr,
            uint32_t * vec_table = nullptr);
    static void reset_core1();

private:
    // Helper method for calling the v
    static void _run();
    // Function to execute if provided in CTOR
    static std::function<void(void)> _f;
};

#endif // _MULTICORE_RP2350_H_
