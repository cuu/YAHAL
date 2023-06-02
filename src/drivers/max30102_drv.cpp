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

#include "max30102_drv.h"
#include "task.h"
#include <cstdint>
#include <cassert>

namespace MAX30102 {
    // MAX30102 Registers
    /////////////////////
    // Status Registers
    uint8_t INT_STAT_1       = 0x00;
    uint8_t INT_STAT_2       = 0x01;
    uint8_t INT_ENABLE_1     = 0x02;
    uint8_t INT_ENABLE_2     = 0x03;
    // FIFO Registers
    uint8_t FIFO_WRITE_PTR   = 0x04;
    uint8_t FIFO_OVF_COUNTER = 0x05;
    uint8_t FIFO_READ_PTR    = 0x06;
    uint8_t FIFO_DATA        = 0x07;
    // Configuration Registers
    uint8_t FIFO_CONFIG      = 0x08;
    uint8_t MODE_CONFIG      = 0x09;
    uint8_t SPO2_CONFIG      = 0x0A;
    uint8_t LED1_PULSE_AMP   = 0x0C;
    uint8_t LED2_PULSE_AMP   = 0x0D;
    // Multi-LED Mode Control Registers
    uint8_t MUL_LED_CTRL_1   = 0x11;
    uint8_t MUL_LED_CTRL_2   = 0x12;
    // Die Temperature Registers
    uint8_t DIE_TEMP_INT     = 0x1F;
    uint8_t DIE_TEMP_FRAC    = 0x20;
    uint8_t DIE_TEMP_CFG     = 0x21;
    // Part ID Registers
    uint8_t REVISION_ID      = 0xFE;
    uint8_t PART_ID          = 0xFF;

    // Mask values
    uint8_t INT_A_FULL_MASK       = 0x80;
    uint8_t INT_DATA_RDY_MASK     = 0x40;
    uint8_t INT_ALC_OVF_MASK      = 0x20;
    uint8_t INT_DIE_TEMP_RDY_MASK = 0x02;
    uint8_t ROLLOVER_MASK         = 0x10;
    uint8_t A_FULL_MASK           = 0x0f;
    uint8_t SHUTDOWN_MASK         = 0x80;
    uint8_t RESET_MASK            = 0x40;
    uint8_t SAMPLE_AVG_MASK       = 0xe0;
    uint8_t MODE_MASK             = 0x07;
    uint8_t ADC_RANGE_MASK        = 0x60;
    uint8_t SAMPLE_RATE_MASK      = 0x1c;
    uint8_t PULSE_WIDTH_MASK      = 0x03;
    uint8_t SLOT1_MASK            = 0x07;
    uint8_t SLOT2_MASK            = 0x70;
    uint8_t SLOT3_MASK            = 0x07;
    uint8_t SLOT4_MASK            = 0x70;
    uint8_t TEMP_EN               = 0x01;

    // The hardcoded part ID for MAX30102
    uint8_t EXPECTED_PART_ID      = 0x15;
}

max30102_drv::max30102_drv(i2c_interface & i2c, uint8_t i2c_addr)
: _i2c(i2c),  _i2c_addr(i2c_addr), _data{10,10,10,10},
  _active_slots(0), _pulse_width(0) {
}

void max30102_drv::setup_sensor(MAX30102::SAMPLE_AVG  sample_avg,
                                     MAX30102::LED_MODE    led_mode,
                                     MAX30102::ADC_RANGE   adc_range,
                                     MAX30102::SAMPLE_RATE sample_rate,
                                     MAX30102::PULSE_WIDTH pulse_width,
                                     uint8_t pulse_amp) {
    // Check if the sensor is available
    assert(check_part_id());
    reset();
    set_fifo_average(sample_avg);
    enable_fifo_rollover(true);
    set_led_mode(led_mode);
    set_adc_range(adc_range);
    set_sample_rate(sample_rate);
    set_pulse_width(pulse_width);
    set_pulse_amplitude_led1(pulse_amp);
    set_pulse_amplitude_led2(pulse_amp);
    enable_int_die_temp_rdy(true);
}

void max30102_drv::set_fifo_average(MAX30102::SAMPLE_AVG samples) {
    set_register_mask_value(MAX30102::FIFO_CONFIG,
                            MAX30102::SAMPLE_AVG_MASK,
                            samples);
}

void max30102_drv::set_led_mode(MAX30102::LED_MODE mode) {
    if (mode == MAX30102::LED1_ONLY) {
        _active_slots = 1;
    }
    else if (mode == MAX30102::BOTH_LEDS) {
        _active_slots = 2;
    }
    set_register_mask_value(MAX30102::MODE_CONFIG,
                            MAX30102::MODE_MASK,
                            mode);
}

void max30102_drv::set_adc_range(MAX30102::ADC_RANGE adc_range) {
    set_register_mask_value(MAX30102::SPO2_CONFIG,
                            MAX30102::ADC_RANGE_MASK,
                            adc_range);
}

void max30102_drv::set_sample_rate(MAX30102::SAMPLE_RATE rate) {
    set_register_mask_value(MAX30102::SPO2_CONFIG,
                            MAX30102::SAMPLE_RATE_MASK,
                            rate);
}

void max30102_drv::set_pulse_width(MAX30102::PULSE_WIDTH width) {
    _pulse_width = width;
    set_register_mask_value(MAX30102::SPO2_CONFIG,
                            MAX30102::PULSE_WIDTH_MASK,
                            width);
}

uint8_t max30102_drv::slot_data_available(uint8_t slot) {
    return _data[slot].available_get();
}

uint32_t max30102_drv::get_slot_data(uint8_t slot) {
    uint32_t val = 0;
    _data[slot].get(val);
    return val;
}

bool max30102_drv::check() {
    // Get number of available samples
    int8_t number_of_samples = get_write_pointer() - get_read_pointer();
    // Handle wrap-around case
    if (number_of_samples < 0) number_of_samples += 32;
    // Do we have new data?
    if (number_of_samples) {
        // Loop over all samples
        uint8_t buf[12];
        for (uint8_t sample = 0; sample < number_of_samples; ++sample) {
            // Read data from FIFO for one sample (_active_slots * 3 bytes)
            buf[0] = MAX30102::FIFO_DATA;
            _i2c.i2cWrite(_i2c_addr, buf, 1, false);
            _i2c.i2cRead (_i2c_addr, buf, _active_slots * 3);
            // Loop of all active slots
            for(uint8_t slot=0; slot < _active_slots; ++slot) {
                uint8_t offset = slot * 3;
                uint32_t value = 0;
                value |= buf[offset];
                value <<= 8;
                value |= buf[offset+1];
                value <<= 8;
                value |= buf[offset+2];
                // Mask away upper bits - they can contain garbage
                // Shift the result according to the ADC resolution
                value = (value & 0x3ffff) >> (3 - _pulse_width);
                _data[slot].put(value);
            }
        }
        return true;
    } else {
        return false;
    }
}

uint8_t max30102_drv::get_int_status_1() {
    return read_register(MAX30102::INT_STAT_1);
}

uint8_t max30102_drv::get_int_status_2() {
    return read_register(MAX30102::INT_STAT_2);
}

void max30102_drv::enable_int_a_full(bool on) {
    if (on) {
        set_register_mask(MAX30102::INT_ENABLE_1,
                          MAX30102::INT_A_FULL_MASK);
    } else {
        clear_register_mask(MAX30102::INT_ENABLE_1,
                            MAX30102::INT_A_FULL_MASK);
    }
}

void max30102_drv::enable_int_data_rdy(bool on) {
    if (on) {
        set_register_mask(MAX30102::INT_ENABLE_1,
                          MAX30102::INT_DATA_RDY_MASK);
    } else {
        clear_register_mask(MAX30102::INT_ENABLE_1,
                            MAX30102::INT_DATA_RDY_MASK);
    }
}

void max30102_drv::enable_int_alc_ovf(bool on) {
    if (on) {
        set_register_mask(MAX30102::INT_ENABLE_1,
                          MAX30102::INT_ALC_OVF_MASK);
    } else {
        clear_register_mask(MAX30102::INT_ENABLE_1,
                            MAX30102::INT_ALC_OVF_MASK);
    }
}

void max30102_drv::enable_int_die_temp_rdy(bool on) {
    if (on) {
        set_register_mask(MAX30102::INT_ENABLE_2,
                          MAX30102::INT_DIE_TEMP_RDY_MASK);
    } else {
        clear_register_mask(MAX30102::INT_ENABLE_2,
                            MAX30102::INT_DIE_TEMP_RDY_MASK);
    }
}

void max30102_drv::enable_fifo_rollover(bool on) {
    if (on) {
        set_register_mask(MAX30102::FIFO_CONFIG,
                          MAX30102::ROLLOVER_MASK);
    } else {
        clear_register_mask(MAX30102::FIFO_CONFIG,
                            MAX30102::ROLLOVER_MASK);
    }
}

void max30102_drv::set_fifo_almost_full(uint8_t samples) {
    assert(samples >= 17 && samples <=32);
    set_register_mask_value(MAX30102::FIFO_CONFIG,
                            MAX30102::A_FULL_MASK,
                            32-samples);
}

void max30102_drv::shutdown(bool on) {
    if (on) {
        set_register_mask(MAX30102::MODE_CONFIG,
                          MAX30102::SHUTDOWN_MASK);

    } else {
        clear_register_mask(MAX30102::MODE_CONFIG,
                            MAX30102::SHUTDOWN_MASK);
    }
}

void max30102_drv::reset() {
    set_register_mask(MAX30102::MODE_CONFIG, MAX30102::RESET_MASK);
    uint8_t reset_bit = get_register_mask(MAX30102::MODE_CONFIG,
                                          MAX30102::RESET_MASK);
    while (reset_bit) {
        task::sleep(10);
        reset_bit = get_register_mask(MAX30102::MODE_CONFIG,
                                      MAX30102::RESET_MASK);
    }
}

void max30102_drv::set_pulse_amplitude_led1(uint8_t amplitude) {
    write_register(MAX30102::LED1_PULSE_AMP, amplitude);
}

void max30102_drv::set_pulse_amplitude_led2(uint8_t amplitude) {
    write_register(MAX30102::LED2_PULSE_AMP, amplitude);
}

void max30102_drv::config_slots(uint8_t slot1, uint8_t slot2,
                                uint8_t slot3, uint8_t slot4) {
    _active_slots = 0;
    if (slot1 != MAX30102::NONE) {
        set_register_mask_value(MAX30102::MUL_LED_CTRL_1,
                                MAX30102::SLOT1_MASK, slot1);
        _active_slots += 1;
    }
    if (slot2 != MAX30102::NONE) {
        set_register_mask_value(MAX30102::MUL_LED_CTRL_1,
                                MAX30102::SLOT2_MASK, slot2 << 4);
        _active_slots += 1;
    }
    if (slot3 != MAX30102::NONE) {
        set_register_mask_value(MAX30102::MUL_LED_CTRL_2,
                                MAX30102::SLOT3_MASK, slot3);
        _active_slots += 1;
    }
    if (slot4 != MAX30102::NONE) {
        set_register_mask_value(MAX30102::MUL_LED_CTRL_2,
                                MAX30102::SLOT4_MASK, slot4 << 4);
        _active_slots += 1;
    }
}

float max30102_drv::read_temperature() {
    // Trigger a new temperature reading
    write_register(MAX30102::DIE_TEMP_CFG, MAX30102::TEMP_EN);
    // Wait until rdy-interrupt is raised
    uint8_t rdy_bit = read_register(MAX30102::INT_STAT_2);
    while (!rdy_bit) {
        task::sleep(5);
        rdy_bit = read_register(MAX30102::INT_STAT_2);
    }
    uint8_t tempInt  = read_register(MAX30102::DIE_TEMP_INT);
    // Reading the fractional part will also clear the IRQ flag
    uint8_t tempFrac = read_register(MAX30102::DIE_TEMP_FRAC);
    return (float)tempInt + (float)tempFrac * 0.0625;
}

uint8_t max30102_drv::read_part_id() {
    return read_register(MAX30102::PART_ID);
}

bool max30102_drv::check_part_id() {
    return read_part_id() == MAX30102::EXPECTED_PART_ID;
}

uint8_t max30102_drv::get_revision_id() {
    return read_register(MAX30102::REVISION_ID);
}

uint8_t max30102_drv::get_write_pointer() {
    return read_register(MAX30102::FIFO_WRITE_PTR);
}

uint8_t max30102_drv::get_ovf_counter() {
    return read_register(MAX30102::FIFO_OVF_COUNTER);
}

uint8_t max30102_drv::get_read_pointer() {
    return read_register(MAX30102::FIFO_READ_PTR);
}

uint8_t max30102_drv::read_register(uint8_t reg) {
    uint8_t buf[1];
    buf[0] = reg;
    _i2c.i2cWrite(_i2c_addr, buf, 1, false);
    _i2c.i2cRead (_i2c_addr, buf, 1);
    return buf[0];
}

void max30102_drv::write_register(uint8_t reg, uint8_t data) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    _i2c.i2cWrite(_i2c_addr, buf, 2);
}

uint8_t max30102_drv::get_register_mask(uint8_t reg, uint8_t mask) {
    return read_register(reg) & mask;
}

void max30102_drv::set_register_mask(uint8_t reg, uint8_t mask) {
    // Read-Modify-Write cycle
    write_register(reg, read_register(reg) | mask);
}

void max30102_drv::set_register_mask_value(uint8_t reg, uint8_t mask, uint8_t val) {
    // Read-Modify-Write cycle
    write_register(reg, (read_register(reg) & ~mask) | (val & mask));
}

void max30102_drv::clear_register_mask(uint8_t reg, uint8_t mask) {
    write_register(reg, read_register(reg) & ~mask);
}

