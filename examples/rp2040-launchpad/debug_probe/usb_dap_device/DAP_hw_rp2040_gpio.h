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
// DAP HW implementation for the RP2040 MCU using
// simple bit banging.
//
#ifndef DAP_HW_RP2040_GPIO_H
#define DAP_HW_RP2040_GPIO_H

#include "config.h"
#include "gpio_rp2040.h"
#include "system_rp2040.h"
#include "RP2040.h"
#include "DAP_hw_interface.h"

#include <cstdio>

using namespace _TIMER_;

class DAP_hw_rp2040_gpio : public DAP_hw_interface {
public:

    explicit DAP_hw_rp2040_gpio()
    : _swclk(GPIO_SWCLK), _swdio(GPIO_SWDIO) {
    }

    ////////////////////////////////
    // General configuration methods
    ////////////////////////////////

    // Set HW frequency in Hz, which drives the SWCLK/TCK Pin.
    inline void frequency_set(uint32_t f) override {
        _frequency = f;
    }

    static uint64_t ticks() {
        uint32_t hi1, lo, hi2;
        do {
            hi1 = TIMER.TIMEHR;
            lo  = TIMER.TIMELR;
            hi2 = TIMER.TIMEHR;
        } while (hi1 != hi2);
        return ((uint64_t)hi1 << 32) | lo;
    }

    // Delay for a number of microseconds, which is
    // used at some places in the CMSIS DAP protocol.
    void delay_us(uint32_t us) override {
        uint64_t start = ticks();
        uint64_t wait_ticks = (uint64_t)us * _ticks_per_micros;
        while ((ticks() - start) < wait_ticks) ;
    }

    // CMSIS DAP can use an optional test domain timer.
    // The following methods return the support status,
    // the frequency and the current value of the test
    // domain timer.
    inline bool test_domain_timer_support() override {
        // No domain timer so far ...
        return false;
    }
    inline uint32_t test_domain_timer_frequency() override {
        return 0;
    }
    inline uint32_t test_domain_timer_get() override {
        return 0;
    }

    ////////////////////////////
    // Pin configuration methods
    ////////////////////////////

    // Set up all needed HW Pins for JTAG operation
    // (TCK, TMS, TDI, TDO and optionally nTRST and nRESET)
    void connect_jtag_pins() override {
        // No JTAG Pins so far...
    }

    // Set up all needed HW Pins for SWD operation
    // (SWCLK, SWDIO and optionally nRESET)
    void connect_swd_pins() override {
        _swclk.gpioMode(GPIO::OUTPUT);
        _swdio.gpioMode(GPIO::OUTPUT);
    }

    // De-configure all SWD/JTAG Pins and put them
    // into a high-Z state
    void disconnect() override {
        _swclk.gpioMode(GPIO::INPUT);
        _swdio.gpioMode(GPIO::INPUT);
    }

    ////////////////////////////////
    // SWD / JTAG read write methods
    ////////////////////////////////

    // Method for toggling the SWCLK/TCK line for a
    // certain amount of cycles. Used by SWD and JTAG.
    // Starting level of the SWCLK/TCK line is LOW,
    // so ony cycle is a -> HIGH -> LOW transition
    // (using the configured frequency).
    inline void swclk_tck_cycle(uint16_t cycles) override {
        while (cycles--) {
            swclk_tck_set(true);
            delay_edge();
            swclk_tck_set(false);
            delay_edge();
        }
    }

    // Methods for reading up to 32 bits via the
    // SWD interface. Starting level of SWCLK is LOW.
    // SWDIO data is changed by the target on rising clock
    // edges. The host can read either after the falling
    // clock edge, or immediately before the next rising
    // clock edge.
    // NOTE: The first bit is driven by the target right
    // at the beginning of this method (Data Phase Shift)!
    // size is the number of bits to read.
    inline uint32_t swd_read(uint8_t size) override {
        uint32_t value = 0;
        uint32_t bit;
        for (uint8_t i = 0; i < size; i++) {
            bit = swdio_tms_get();
            value |= (bit << i);

            swclk_tck_set(true);
            delay_edge();
            swclk_tck_set(false);
            delay_edge();
        }
        return value;
    }

    // Method for writing up to 32 bits via the SWD
    // interface. The first bit has to be prepared BEFORE
    // the first rising clock edge (when SWDIO is sampled
    // by the target). size is the number of bits to write.
    inline void swd_write(uint32_t value, uint8_t size ) override {
        swdio_tms_set(value & 1);
        value >>= 1;
        delay_edge();

        for (uint8_t i = 0; i < size; i++) {
            swclk_tck_set(true);
            delay_edge();
            swdio_tms_set(value & 1);
            value >>= 1;
            swclk_tck_set(false);
            delay_edge();
        }
    }

    // Methods for reading/writing up to 32 bits via the
    // JTAG interface. Starting level of TCK is HIGH.
    // TDI data is changed on falling clock edges (writing
    // to target), and TDO is sampled on rising edges (reading
    // from target). The size parameter is the number of bits to
    // read/write. The jtag_write method returns the shifted
    // input value (the 'remaining' bits after sending 'size'
    // bits).

    inline uint32_t jtag_read(uint8_t size) override {
        uint32_t value = 0;
        uint32_t bit;
        for (uint8_t i = 0; i < size; i++) {
            swclk_tck_set(false);
            delay_edge();
            bit = tdo_get();
            swclk_tck_set(true);
            delay_edge();
            value |= (bit << i);
        }
        return value;
    }

    inline uint32_t jtag_write(uint32_t value, uint8_t size) override {
        for (uint8_t i = 0; i < size; i++) {
            tdi_set(value & 1);
            swclk_tck_set(false);
            delay_edge();
            swclk_tck_set(true);
            delay_edge();
            value >>= 1;
        }
        return value;
    }

    inline uint32_t jtag_read_write(uint32_t value, uint8_t size) override {
        uint32_t read_value = 0;
        uint32_t bit;
        for (uint8_t i = 0; i < size; i++) {
            tdi_set(value & 1);
            swclk_tck_set(false);
            delay_edge();
            bit = tdo_get();
            swclk_tck_set(true);
            delay_edge();
            value >>= 1;
            read_value |= (bit << i);
        }
        return read_value;
    }

    ///////////////////////////////////////////
    // Direct SWD/JTAG Pin access (bit banging)
    ///////////////////////////////////////////

    // When using bit-banging, this method will wait
    // the correct amount of time to achieve the needed
    // frequency of the SWCLK/TCK signal. Because this
    // method is called after every SWCLK/TCK edge, half
    // of the period duration of the currently selected
    // frequency is needed. So when e.g. the frequency is
    // set to 1MHz, this method would wait approx. 500ns.

    inline void delay_edge() {
        // We don't delay after a SWCLK edge
        // -> maximum speed!
        //delay_us(1);
    }

    inline void swclk_tck_set(bool v) override {
        if (v) _SIO_::SIO.GPIO_OUT_SET = (1 << GPIO_SWCLK);
        else   _SIO_::SIO.GPIO_OUT_CLR = (1 << GPIO_SWCLK);
    }

    inline bool swclk_tck_get() override {
        return _SIO_::SIO.GPIO_IN & (1 << GPIO_SWCLK);
    }

    inline void swdio_tms_set(bool v) override {
        if (v) _SIO_::SIO.GPIO_OUT_SET = (1 << GPIO_SWDIO);
        else   _SIO_::SIO.GPIO_OUT_CLR = (1 << GPIO_SWDIO);
    }

    inline bool swdio_tms_get() override {
        return _SIO_::SIO.GPIO_IN & (1 << GPIO_SWDIO);
    }

    inline void swdio_tms_mode_input() override {
        _SIO_::SIO.GPIO_OE_CLR = (1 << GPIO_SWDIO);
    }
    inline void swdio_tms_mode_output() override {
        _SIO_::SIO.GPIO_OE_SET = (1 << GPIO_SWDIO);
    }

    inline void tdi_set(bool) override {
    }
    inline bool tdi_get() override {
        return false;
    }
    inline bool tdo_get() override {
        return false;
    }
    inline void trst_set(bool) override {
    }
    inline bool trst_get() override {
        return false;
    }
    inline bool reset_set(bool) override {
        return false;
    }
    inline bool reset_get() override {
        return false;
    }

private:
    uint32_t    _frequency {0};
    gpio_rp2040 _swclk;
    gpio_rp2040 _swdio;
};

#endif // DAP_HW_RP2040_GPIO_H
