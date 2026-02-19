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
// a PIO program for increased performance.
//
#ifndef DAP_HW_RP2040_PIO_H
#define DAP_HW_RP2040_PIO_H

#include <cassert>
#include "config.h"

#include "gpio_rp2040.h"
#include "pio_rp2040.h"
#include "system_rp2040.h"

#include "RP2040.h"
#include "DAP_hw_interface.h"
#include "swd_ctrl.pio.h"

using namespace _TIMER_;

class DAP_hw_rp2040_pio : public DAP_hw_interface {
public:

    explicit DAP_hw_rp2040_pio()
    : _swclk(GPIO_SWCLK), _swdio(GPIO_SWDIO) {
        // Load and configure the PIO program.
        _pio_swd = pio_rp2040::pio0.loadProgram(pio_swd_program);
        configure_SM(_pio_swd, GPIO_SWDIO, GPIO_SWCLK);
        _pio_swd->enable();
    }

    ////////////////////////////////
    // General configuration methods
    ////////////////////////////////

    inline void frequency_set(uint32_t f) override {
        _pio_swd->setClock(SM_CYCLES_PER_SWCLK * f);
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

    void delay_us(uint32_t us) override {
        uint64_t start = ticks();
        uint64_t wait_ticks = (uint64_t)us * _ticks_per_micros;
        while ((ticks() - start) < wait_ticks) ;
    }

    constexpr bool test_domain_timer_support() override {
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

    void connect_jtag_pins() override {
        // No JTAG Pins so far...
    }
    void connect_swd_pins() override {
        _swclk.gpioMode(GPIO::OUTPUT | GPIO::FAST | GPIO::DRIVE_4mA);
        _swdio.gpioMode(GPIO::OUTPUT | GPIO::FAST | GPIO::DRIVE_4mA);
        _swclk.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
        _swdio.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    }

    void disconnect() override {
        _swclk.gpioMode(GPIO::INPUT);
        _swdio.gpioMode(GPIO::INPUT);
        _swclk.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
        _swdio.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__null);
    }

    /////////////////////////////////////////
    // Optional SWD / JTAG read write methods
    /////////////////////////////////////////

    inline void swclk_tck_cycle(uint16_t len) override {
        if (len == 0) return;
        swd_cmd_t cmd;
        cmd.len = --len;
        cmd.cmd = pio_swd_offset_cycle + _pio_swd->load_addr;
        _pio_swd->writeTxFifo(cmd.value);
    }

    inline uint32_t swd_read(uint8_t len) override {
        swd_cmd_t cmd;
        cmd.len = --len;
        cmd.cmd = pio_swd_offset_read + _pio_swd->load_addr;
        _pio_swd->writeTxFifo(cmd.value);
        uint32_t val = _pio_swd->readRxFifo();
        val >>= (31-len);
        return val;
    }

    inline void swd_write(uint32_t val, uint8_t len) override {
        swd_cmd_t cmd;
        cmd.len = --len;
        cmd.cmd = pio_swd_offset_write + _pio_swd->load_addr;
        _pio_swd->writeTxFifo(cmd.value);
        _pio_swd->writeTxFifo(val);
    }

    inline uint32_t jtag_read(uint8_t) override {
        return 0;
    }
    inline uint32_t jtag_write(uint32_t, uint8_t) override {
        return 0;
    }
    inline uint32_t jtag_read_write(uint32_t, uint8_t) override {
        return 0;
    }

    ///////////////////////////////////////////
    // Direct SWD/JTAG Pin access (bit banging)
    ///////////////////////////////////////////

    inline void swclk_tck_set(bool) override {
        // We ignore manual setting of SWCLK.
        // Such requests might come from the
        // SWJ_Pins command, but PIO is in charge
        // of the SWCLK pin...
    }

    inline bool swclk_tck_get() override {
        return _SIO_::SIO.GPIO_IN & (1<<GPIO_SWCLK);
    }

    inline void swdio_tms_set(bool) override {
        // We ignore manual setting of SWDIO.
        // Such requests might come from the
        // SWJ_Pins command, but PIO is in charge
        // of the SWDIO pin...
    }

    inline bool swdio_tms_get() override {
        return _SIO_::SIO.GPIO_IN & (1<<GPIO_SWDIO);
    }

    inline void swdio_tms_mode_input() override {
        swd_cmd_t cmd;
        cmd.cmd    = pio_swd_offset_setdir + _pio_swd->load_addr;
        cmd.out_en = 0;
        _pio_swd->writeTxFifo(cmd.value);
    }

    inline void swdio_tms_mode_output() override {
        swd_cmd_t cmd;
        cmd.cmd    = pio_swd_offset_setdir + _pio_swd->load_addr;
        cmd.out_en = 1;
        _pio_swd->writeTxFifo(cmd.value);
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
    gpio_rp2040 _swclk;
    gpio_rp2040 _swdio;

    SM *        _pio_swd;
};

#endif // DAP_HW_RP2040_PIO_H
