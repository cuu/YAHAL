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
// Driver for MAX30102 puls oxymeter sensor

#ifndef _MAX30102_DRV_H_
#define _MAX30102_DRV_H_

#include "i2c_interface.h"
#include "FIFO.h"
#include <cstdint>

namespace MAX30102 {
    static const uint8_t I2C_ADDR = 0x57;

    enum SAMPLE_AVG {
        SAMPLE_AVG_1  = 0x00,
        SAMPLE_AVG_2  = 0x20,
        SAMPLE_AVG_4  = 0x40,
        SAMPLE_AVG_8  = 0x60,
        SAMPLE_AVG_16 = 0x80,
        SAMPLE_AVG_32 = 0xA0
    };

    enum LED_MODE {
        LED1_ONLY     = 0x02,
        BOTH_LEDS     = 0x03,
        MULTI_LEDS    = 0x07
    };

    enum ADC_RANGE {
        ADC_RANGE_2048  = 0x00,
        ADC_RANGE_4096  = 0x20,
        ADC_RANGE_8192  = 0x40,
        ADC_RANGE_16384 = 0x60
    };

    enum SAMPLE_RATE {
        SAMPLE_RATE_50   = 0x00,
        SAMPLE_RATE_100  = 0x04,
        SAMPLE_RATE_200  = 0x08,
        SAMPLE_RATE_400  = 0x0c,
        SAMPLE_RATE_800  = 0x10,
        SAMPLE_RATE_1000 = 0x14,
        SAMPLE_RATE_1600 = 0x18,
        SAMPLE_RATE_3200 = 0x1c
    };

    enum PULSE_WIDTH {
        PULSE_WIDTH_69   = 0x00,
        PULSE_WIDTH_118  = 0x01,
        PULSE_WIDTH_215  = 0x02,
        PULSE_WIDTH_411  = 0x03
    };

    enum SLOT_CONFIG {
        SLOT_NONE        = 0x00,
        SLOT_LED1        = 0x01,
        SLOT_LED2        = 0x02
    };

    static const uint8_t PULSE_AMP_MEDIUM = 0x80;
}

class max30102_drv {
public:
    max30102_drv(i2c_interface & i2c, uint8_t i2c_addr=MAX30102::I2C_ADDR);

    // Reset the sensor and set the (default) configuration parameters.
    // Alternatively, all these steps can also be performed by the
    // application software without using this method.
    void setup_sensor(MAX30102::SAMPLE_AVG  sample_avg  = MAX30102::SAMPLE_AVG::SAMPLE_AVG_8,
                      MAX30102::LED_MODE    led_mode    = MAX30102::LED_MODE::BOTH_LEDS,
                      MAX30102::ADC_RANGE   adc_range   = MAX30102::ADC_RANGE::ADC_RANGE_16384,
                      MAX30102::SAMPLE_RATE sample_rate = MAX30102::SAMPLE_RATE::SAMPLE_RATE_400,
                      MAX30102::PULSE_WIDTH pulse_width = MAX30102::PULSE_WIDTH::PULSE_WIDTH_411,
                      uint8_t pulse_amp                 = MAX30102::PULSE_AMP_MEDIUM);

    // Set the sample averaging level
    void set_fifo_average(MAX30102::SAMPLE_AVG samples);
    // Set the LED mode
    void set_led_mode(MAX30102::LED_MODE mode);
    // Set ADC range
    void set_adc_range(MAX30102::ADC_RANGE adc_range);
    // Set sample rate
    void set_sample_rate(MAX30102::SAMPLE_RATE rate);
    // Set pulse width
    void set_pulse_width(MAX30102::PULSE_WIDTH width);

    // Check if data is available in the FIFO.
    // Parameter is the slot number from 0..3. The length
    // of available values is returned as an integer.
    uint8_t slot_data_available(uint8_t slot);

    // Read a single value from the FIFO.
    // Parameter is the slot number from 0..3. The data
    // item is returned as an integer. In case this
    // method is calles accidently without available
    // data, a 0 is returned!
    uint32_t get_slot_data(uint8_t slot);

    // Poll the sensor for new data in its FIFO.
    // If data is existing, it is transferred to
    // the FIFO, which exist for each timing slot.
    // Returns True if new data is available.
    bool check();

    // Read the Interrupt Status 1 register (reg addr 0x00)
    uint8_t get_int_status_1();
    // Read the Interrupt Status 2 register (reg addr 0x01)
    uint8_t get_int_status_2();

    // Enable/Disable the 'FIFO Almost Full' interrupt
    void enable_int_a_full(bool on);
    // Enable/Disable the 'Data ready' interrupt
    void enable_int_data_rdy(bool on);
    // Enable/Disable the 'ALC overflow' interrupt
    void enable_int_alc_ovf(bool on);
    // Enable/Disable the 'Die Temperature Ready' interrupt
    // This interrupt needs to be enabled if the interrupt flag
    // in the Interrupt Status Register 2 is used for polling
    // until the temperature data is available!
    void enable_int_die_temp_rdy(bool on);

    // Enable/Disable FIFO rollover behaviour
    void enable_fifo_rollover(bool on);
    // Set the level when the 'FIFO Almost Full' interrupt is triggered.
    // Valid parameters are intergers in the range from 17 to 32
    void set_fifo_almost_full(uint8_t samples);
    // Enable/Disable the sensor shutdown state
    void shutdown(bool on);
    // Reset the sensor. All configuration and data registers
    // are reset to their respective power-on values.
    void reset();
    // Set LED brightness
    void set_pulse_amplitude_led1(uint8_t amplitude);
    void set_pulse_amplitude_led2(uint8_t amplitude);

    // Configure the 4 possible timing slots. According to the data sheet, slots
    // should be filled from left to right (enable slot1, then slot2 etc.)
    // This method has to be called _before_ set_led_mode(MAX30102_MODE_MULTI_LEDS)
    // is called!
    void config_slots(uint8_t slot1 = MAX30102::SLOT_CONFIG::SLOT_NONE,
                      uint8_t slot2 = MAX30102::SLOT_CONFIG::SLOT_NONE,
                      uint8_t slot3 = MAX30102::SLOT_CONFIG::SLOT_NONE,
                      uint8_t slot4 = MAX30102::SLOT_CONFIG::SLOT_NONE);

    // Read the die temperature and return the result as a float
    // number in degrees celsius °C. Treat the integer portion of
    // the register value as a signed byte and the fractional
    // portion as an unsigned byte, as described in the data sheet.
    float read_temperature();

    // Read the part ID and return the value as an integer
    uint8_t read_part_id();

    // Check the part ID. Return true if expected value matches
    bool check_part_id();

    // Read the revision ID of the sensor and return the value as an integer.
    // Some sensors return a value of '3' here. Currently there is no available
    // information what the different revisions have changed in detail. Maybe
    // the swapping of red and IR LEDs is one of the changes in later revisions?!
    uint8_t get_revision_id();

private:
    i2c_interface & _i2c;
    uint8_t         _i2c_addr;
    FIFO<uint32_t>  _data[4];
    uint8_t         _active_slots;
    uint8_t         _pulse_width;

    //Get the FIFO write pointer as an integer value
    uint8_t get_write_pointer();
    // Get the FIFO overflow counter as an integer value
    uint8_t get_ovf_counter();
    // Get the FIFO read pointer as an integer value
    uint8_t get_read_pointer();

    // Read a register via I2C with specific size (default size is 1).
    // After sending the device address and register number, no I2C
    // STOP-condition is sent, but a repeated START-condition.
    // The return value is a byte array.
    uint8_t read_register(uint8_t reg);

    // Write a register via I2C with specific size. The parameter val is
    // a byte array with the data to write. Only one I2C write operation
    // is necessary.
    void write_register(uint8_t reg, uint8_t data);

    // Read a 1-byte register and return the masked register value. This
    // method is usefull for checking specific bits within the register.
    // Return value is a integer.
    uint8_t get_register_mask(uint8_t reg, uint8_t mask);

    // Set specific bits in a 1-byte register. The parameter 'mask'
    // contains the bits to set. With this method, bits can only be
    // set, not cleared (see clear_register_mask)!
    void set_register_mask(uint8_t reg, uint8_t mask);

    // Set a group of bits to a specific values. The parameter 'mask'
    // defines the bits which should be modified. The parameter 'val'
    // contains the new bit values, which have to be at the same positions
    // as the mask bits.
    void set_register_mask_value(uint8_t reg, uint8_t mask, uint8_t val);

    // Clear specific bits in a 1-byte register. The parameter 'mask'
    // contains the bits to be cleared. With this method, bits can only
    // be cleared, not set (see set_register_mask)!
    void clear_register_mask(uint8_t reg, uint8_t mask);
};

#endif // MAX30102_DRV_H_
