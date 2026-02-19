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
// This class implements a driver for various floppy
// disk drives and formats. It provides read access
// using the method read_sector(). The floppy format
// will be auto-detected. The class also implements
// the blockio interface.
//
#include <cstring>

#include "floppy_drv.h"
#include "floppy_logger.h"
#include "read_track.pio.h"
#include "write_track.pio.h"

#include "task.h"
#include "RP2350.h"
#include "system_rp2350.h"

namespace FLOPPY {

    // Global access instance. Will be set in CTOR
    const floppy_drv * floppy_drv::inst = nullptr;

    floppy_drv::floppy_drv(floppy_pins     & pins,
                           floppy_drive    & drive,
                           timer_interface & motor_timer)
    : format(_format),
      _pin_index(pins.index),           _pin_drive_select(pins.drive_select),
      _pin_motor_on(pins.motor_on),     _pin_direction_select(pins.direction_select),
      _pin_step(pins.step),             _pin_write_data(pins.write_data),
      _pin_write_gate(pins.write_gate), _pin_track_00(pins.track_00),
      _pin_write_protect(pins.write_protect), _pin_read_data(pins.read_data),
      _pin_side_one_select(pins.side_one_select), _pin_disk_change(pins.disk_change),
      _drive(drive), _motor_timer(motor_timer)
    {
        LOG(LOG_DEBUG, "floppy_drv::floppy_drv");
        // Set the global access pointer.
        inst = this;

        // Set up the GPIO pins
        _pin_index.gpioMode           (GPIO::INPUT             | GPIO::PULLUP);
        _pin_drive_select.gpioMode    (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_motor_on.gpioMode        (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_direction_select.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_step.gpioMode            (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_write_data.gpioMode      (GPIO::OUTPUT); //_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_write_gate.gpioMode      (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_track_00.gpioMode        (GPIO::INPUT             | GPIO::PULLUP);
        _pin_write_protect.gpioMode   (GPIO::INPUT             | GPIO::PULLUP);
        _pin_read_data.gpioMode       (GPIO::INPUT             | GPIO::PULLUP);
        _pin_side_one_select.gpioMode (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pin_disk_change.gpioMode     (GPIO::INPUT             | GPIO::PULLUP);

        // Set up motor timer
        _motor_timer.setPeriod(_drive.motor_follow_up_time_ms * 1000, TIMER::ONE_SHOT);
        _motor_timer.setCallback( [&]() {
            // Switch off the spindle motor after timeout
            _pin_motor_on = HIGH;
            // Deselect the drive
            _pin_drive_select = HIGH;
        });

        // Load and configure the PIO program for track reading
        _sm_read_track = pio_rp2350::pio0.loadProgram(read_track_program);
        // The IRQ handler will be call approx. every 48us (21kHz), because
        // the state machine will trigger an IRQ when 6 FIFO entries have
        // been stored, which are equivalent to 24 flux pulses (2us each).
        _sm_read_track->attachIrq([&] () {
            while(!_sm_read_track->RxFifoEmpty()) {
                // Get 4 flux values and store them
                *_flux_buffer_ptr++ = _sm_read_track->readRxFifo();
            }
        });
        configure_read_SM(_sm_read_track, _pin_read_data.getGpio());

        // Load and configure the PIO program for track writing
        _sm_write_track = pio_rp2350::pio0.loadProgram(write_track_program);
        _sm_write_track->attachIrq([&] () {
            while(!_sm_write_track->TxFifoFull()) {
                _sm_write_track->writeTxFifo(0x1a2a1a1a);
            }
        });
        configure_write_SM(_sm_write_track, _pin_write_gate.getGpio(),
                                            _pin_write_data.getGpio());
        _pin_write_data.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
        _sm_write_track->enableIrq();
        _sm_write_track->enable();
    }

    ret_t floppy_drv::init() {
        LOG(LOG_DEBUG, "floppy_drv::init()");
        // Select the drive
        _pin_drive_select = LOW;
        task::sleep_ms(1);
        // Check for an existing floppy
        if (_pin_disk_change == HIGH && _format != nullptr) {
            return RET_CODE::SUCCESS;
        } else {
            // Okay, we had a disk change or no floppy.
            // Calibrate the head to see if we have a disk
            seek_to_00();
            seek_to_track(_drive.number_of_tracks-1);
            seek_to_00();
            // Check for no disk
            if (_pin_disk_change == LOW) {
                return RET_CODE::NO_DISK;
            }
            // We HAVE a disk! Iterate over all possible floppy formats
            ret_t result;
            for (auto f : floppy_formats) {
                // Skip over formats with wrong disk size
                if (f->floppy_size != _drive.floppy_size) {
                    continue;
                }
                LOG(LOG_INFO, "Trying format %s", f->name);
                // Try to read track 0 head 0
                _pin_side_one_select = HIGH;
                set_format(f);
                result = read_track();
                LOG(LOG_INFO, "Result: %s", result.to_str());
                if (result == RET_CODE::SUCCESS) {
                    // Clear the stat data
                    floppy_statistics::inst().reset();
                    _data_buffer_valid = false;
                    return result;
                }
            }
            // We did not find a fitting format.
            // Reset the floppy configuration.
            set_format(nullptr);
            _data_buffer_valid = false;
            return RET_CODE::UNSUPPORTED_FORMAT;
        }
    }

    void floppy_drv::set_format(floppy_format * f) {
        // Set the private attribute
        _format = f;
        if (f == nullptr) return;
        // Calculate the number of PIO cycles (instructions) for a single
        // MFM bit. With 50MHz PIO clock and an MFM data rate of 500 kbit/s,
        // we have 100 cycles per MFM data bit (in this example 2us).
        uint32_t cycles_per_bit = PIO_READ_CLK / 1000 / _format->data_rate_kHz;
        // For the thresholds, we take 5/4 and 7/4 of these cycles, and
        // calculate the corresponding count value which the PIO will report
        // in the FIFO.
        _pulse_M_low_threshold  = COUNT_PER_CYCLES(cycles_per_bit * 5/4);
        _pulse_M_high_threshold = COUNT_PER_CYCLES(cycles_per_bit * 7/4);
    }


    ret_t floppy_drv::read_sector(uint8_t track, uint8_t head, uint8_t sector) {
        LOG(LOG_DEBUG, "floppy_drv::read_sector(%d %d %d)", track, head, sector);
        assert(track < _format->number_of_tracks);
        assert(head  < _format->number_of_heads);
        assert(sector > 0 && sector <= _format->number_of_tracks);

        ret_t res = init();
        if (res != RET_CODE::SUCCESS) return res;

        // Check if the current data buffer fits to the request
        bool need_to_read_track = true;
        if (_data_buffer_valid) {
            auto id_ptr = ((id_am_format *)_data_buffer);
            if ((track == id_ptr->cylinder) && (head == id_ptr->head)) {
                need_to_read_track = false;
            }
        }
        if (need_to_read_track) {
            seek_to_track(track);
            _pin_side_one_select = (head == 1) ? LOW : HIGH;
            res = read_track();
            // Return on read errors
            if (res != RET_CODE::SUCCESS) return res;
        }
        // Locate the correct sector. Sectors are often
        // not stores consecutively on the disk (using an
        // interleave factor). So we have to search.
        uint8_t * ptr = _data_buffer;
        uint16_t crc_read, crc_calculated;
        for(int i=0; i <= _format->sectors_per_track; ++i) {
            auto id_ptr = ((id_am_format *)ptr);
            // Check the CRC of the sector ID
            crc_read = (id_ptr->crc_msb << 8) | id_ptr->crc_lsb;
            crc_calculated = calculate_crc(format->ID_AM, ptr,
                                           sizeof(id_am_format)-2);
            if (crc_read != crc_calculated) {
                return RET_CODE::IDAM_CRC_ERROR;
            }
            if (id_ptr->sector == sector) {
                // Skip the sector ID
                ptr += sizeof(id_am_format);
                // Compare generated and read in CRC values
                crc_read = (*(ptr + format->sector_size) << 8) |
                           (*(ptr + format->sector_size+1));
                crc_calculated = calculate_crc(format->D_AM, ptr,
                                               format->sector_size);
                if (crc_read != crc_calculated) {
                    return RET_CODE::DATA_CRC_ERROR;
                }
                return {RET_CODE::SUCCESS, ptr};
            }
            // Step forward to next sector ID. The '+2'
            // are the 2 CRC bytes at the end of the sector data
            ptr += sizeof(id_am_format) + _format->sector_size + 2;
        }
        return RET_CODE::SECTOR_NOT_FOUND;
    }

    blockio_status_t floppy_drv::initialize() {
        LOG(LOG_DEBUG, "floppy_drv::initialize()");
        init();
        return status();
    }

    blockio_status_t floppy_drv::status() {
        LOG(LOG_DEBUG, "floppy_drv::status()");
        blockio_status_t status = 0;
        // Select drive so that pins have a correct state
        motor_start_select();
        // Check various status items
        if (_format == nullptr)        status |= BLOCKIO::NOINIT;
        if (_pin_write_protect == LOW) status |= BLOCKIO::PROTECT;
        if (_pin_disk_change   == LOW) status |= BLOCKIO::NODISK;
        return status;
    }

    BLOCKIO::result_t floppy_drv::readBlock(uint8_t* buff, uint32_t start_block,
                                uint16_t count) {
        // Iterate over all blocks
        for (uint32_t block = start_block; block < start_block+count; ++block) {
            uint8_t sector = (block % format->sectors_per_track) + 1;
            uint8_t head   = (block / format->sectors_per_track) % format->number_of_heads;
            uint8_t track  = (block / format->sectors_per_track) / format->number_of_heads;

            ret_t res=read_sector(track, head, sector);
            if (res != RET_CODE::SUCCESS) {
                LOG(LOG_INFO, "read_sector returned %s", res.to_str());
                //return BLOCKIO::result_t::ERROR;
            }
            // Copy the data into the provided buffer
            memcpy(buff, res.data_ptr, 512);
            buff += 512;
        }
        return BLOCKIO::result_t::OK;
    }

    uint32_t floppy_drv::getBlockCount() {
        LOG(LOG_DEBUG, "floppy_drv::getBlockCount()");
        assert(_format != nullptr);
        uint32_t count = 1;
        count *= _format->number_of_tracks;
        count *= _format->number_of_heads;
        count *= _format->sectors_per_track;
        count *= _format->sector_size;
        count /= 512;
        return count;
    }

    // private Methods

    void floppy_drv::motor_start_select() {
        LOG(LOG_DEBUG, "floppy_drv::motor_start_select()");
        if (_motor_timer.isRunning()) {
            // Motor is already running, just restart the timer
            _motor_timer.reset();
        } else {
            // Select the drive
            _pin_drive_select = LOW;
            // Power on the spindle motor
            _pin_motor_on = LOW;
            task::sleep_ms(_drive.motor_on_delay_ms);
            _motor_timer.start();
        }
    }

    void floppy_drv::seek_pulse() {
        LOG(LOG_DEBUG, "floppy_drv::seek_pulse()");
        _pin_step = LOW;
        task::sleep_ms(_drive.step_pulse_ms);
        _pin_step = HIGH;
        task::sleep_ms(_drive.step_interval_ms - _drive.step_pulse_ms);
    }

    void floppy_drv::seek_to_00() {
        LOG(LOG_DEBUG, "floppy_drv::seek_to_00()");
        motor_start_select();
        _pin_direction_select = HIGH;
        while(_pin_track_00) seek_pulse();
        task::sleep_ms(_drive.step_settle_time_ms);
        _current_track = 0;
    }

    void floppy_drv::seek_to_track(int track) {
        LOG(LOG_DEBUG, "floppy_drv::seek_to_track(%d)", track);
        motor_start_select();
        int delta = track - _current_track;
        _pin_direction_select = (delta < 0);
        if (delta < 0) delta = -delta;
        while(delta--) seek_pulse();
        task::sleep_ms(_drive.step_settle_time_ms);
        _current_track = track;
    }

    ret_t floppy_drv::read_track() {
        LOG(LOG_DEBUG, "floppy_drv::read_track()");
        motor_start_select();

        // Prepare the PIO program
        _sm_read_track->disable();
        _sm_read_track->reset();
        _sm_read_track->enableIrq();
        _flux_buffer_ptr = (uint32_t *)_flux_buffer;

        // Wait for next falling INDEX pulse
        // Time out after 3 disk rotations
        uint16_t ms_per_rotation = 60000 / _drive.motor_speed_rpm;
        uint64_t timeout = task::millis() + (3 * ms_per_rotation);
        bool index_detected = false;
        while(task::millis() < timeout) {
            if (_pin_index == LOW) {
                index_detected = true;
                break;
            }
        }
        if (!index_detected) return RET_CODE::NO_DISK;

        // Start reading MFM data by starting the PIO program
        _sm_read_track->enable();
        // Read in the flux data for one disk roatation
        task::sleep_ms(ms_per_rotation);
        // Stop the PIO program
        _sm_read_track->disableIrq();
        _sm_read_track->disable();

        // Decode the flux data
        uint32_t flux_count = (uint8_t *)_flux_buffer_ptr - _flux_buffer;
        _mfm_reader.set_data_buffer(_data_buffer);
        _mfm_reader.set_data_size(_format->sectors_per_track *
                                   (sizeof(id_am_format) + _format->sector_size + 2));
        _mfm_reader.set_floppy_format(_format);
        _mfm_reader.reset();
        ret_t result;
        PULSE p;
        for(uint32_t i=0; i < flux_count; ++i) {
            uint8_t val = _flux_buffer[i];
            if      (val < _pulse_M_low_threshold)  { p = PULSE::S; }
            else if (val > _pulse_M_high_threshold) { p = PULSE::L; }
            else                                    { p = PULSE::M; }
            result = _mfm_reader.process_pulse(p);
            if (result != RET_CODE::CONTINUE) break;
        }
        _data_buffer_valid = (result == RET_CODE::SUCCESS);
        return result;
    }


    uint16_t floppy_drv::calculate_crc(const MARK_TYPE & mark, uint8_t* buffer, size_t length) {
        uint16_t crc = 0xffff; // start value
        for(auto & b : mark) crc = update_crc(crc, b);
        for (size_t i = 0; i < length; ++i) {
            crc = update_crc(crc, buffer[i]);
        }
        return crc;
    }

    uint16_t floppy_drv::update_crc(uint16_t crc, uint8_t value) {
        for (int i = 8; i < 16; ++i) {
            crc = (crc << 1) ^ ((((crc ^ (value << i)) & 0x8000) ? 0x1021 : 0));
        }
        return crc;
    }

}
