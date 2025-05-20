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
#include "floppy_drv.h"
#include "floppy_logger.h"
#include "task.h"
#include "RP2350.h"
#include "system_rp2350.h"

namespace FLOPPY {

    // Global access instance. Will be set in CTOR
    const floppy_drv * floppy_drv::inst = nullptr;

    floppy_drv::floppy_drv(floppy_pins     & pins,
                           floppy_drive    & drive,
                           timer_interface & motor_timer)
    : format(_format), _pins(pins), _drive(drive), _motor_timer(motor_timer) {
        LOG(LOG_DEBUG, "floppy_drv::floppy_drv");
        // Set the global access pointer.
        inst = this;
        // Set up the GPIO pins
        _pins.index.gpioMode           (GPIO::INPUT             | GPIO::PULLUP);
        _pins.drive_select.gpioMode    (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.motor_on.gpioMode        (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.direction_select.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.step.gpioMode            (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.write_data.gpioMode      (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.write_gate.gpioMode      (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.track_00.gpioMode        (GPIO::INPUT             | GPIO::PULLUP);
        _pins.write_protect.gpioMode   (GPIO::INPUT             | GPIO::PULLUP);
        _pins.read_data.gpioMode       (GPIO::INPUT             | GPIO::PULLUP);
        _pins.side_one_select.gpioMode (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
        _pins.disk_change.gpioMode     (GPIO::INPUT             | GPIO::PULLUP);

        // Set up motor timer
        _motor_timer.setPeriod(_drive.motor_follow_up_time_ms * 1000, TIMER::ONE_SHOT);
        _motor_timer.setCallback( [&]() {
            motor_timer_irq_handler();
        });

        // Set up IRQ handler for falling READ_DATA edges
        _pins.read_data.gpioAttachIrq(GPIO::FALLING, [&]() {
            read_data_irq_handler();
        });
        // Don't enable the IRQ now - wait for a read operation
        _pins.read_data.gpioDisableIrq();
    }

    ret_t floppy_drv::init() {
        LOG(LOG_DEBUG, "floppy_drv::init()");
        // Select the drive
        _pins.drive_select = LOW;
        task::sleep_ms(1);
        // Check for an existing floppy
        if (_pins.disk_change == HIGH && _format != nullptr) {
            return RET_CODE::SUCCESS;
        } else {
            // Okay, we had a disk change or no floppy.
            // Calibrate the head to see if we have a disk
            seek_to_00();
            seek_to_track(_drive.number_of_tracks-1);
            seek_to_00();
            // Check for no disk
            if (_pins.disk_change == LOW) {
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
                _pins.side_one_select = HIGH;
                _format = f;
                result = read_track();
                LOG(LOG_INFO, "Result: %s", result.to_str());
                if (result == RET_CODE::SUCCESS) {
                    return result;
                }
            }
            // We did not find a fitting format.
            // Reset the floppy configuration.
            _format = nullptr;
            _flux_buffer_count = 0;
            _data_buffer_valid = false;
            return RET_CODE::UNSUPPORTED_FORMAT;
        }
    }

    ret_t floppy_drv::read_sector(uint8_t track, uint8_t head, uint8_t sector, uint8_t * & ptr) {
        LOG(LOG_DEBUG, "floppy_drv::read_sector(%d %d %d)", track, head, sector);
        assert(track <  _format->number_of_tracks);
        assert(head  <= _format->double_sided);
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
            _pins.side_one_select = head ? LOW : HIGH;
            res = read_track();
            // Return on read errors
            if (res != RET_CODE::SUCCESS) return res;
        }
        // Locate the correct sector. Sectors are often
        // not stores consecutively on the disk (using an
        // interleave factor). So we have to search.
        ptr = _data_buffer;
        for(int i=0; i <= _format->sectors_per_track; ++i) {
            auto id_ptr = ((id_am_format *)ptr);
            if (id_ptr->sector == sector) {
                ptr += sizeof(id_am_format);
                return RET_CODE::SUCCESS;
            }
            // Step forward to next sector ID. The '+2'
            // are the 2 CRC bytes at the end of the sector data
            ptr += sizeof(id_am_format) + _format->sector_size + 2;
        }
        return RET_CODE::SECTOR_NOT_FOUND;
    }

    blockio_status_t floppy_drv::initialize() {
        LOG(LOG_DEBUG, "floppy_drv::initialize()");
        ret_t res = init();
        return status();
    }

    blockio_status_t floppy_drv::status() {
        LOG(LOG_DEBUG, "floppy_drv::status()");
        blockio_status_t status = 0;
        if (_format == nullptr)         status |= BLOCKIO::NOINIT;
        if (_pins.write_protect == LOW) status |= BLOCKIO::PROTECT;
        if (_flux_buffer_count == 0)    status |= BLOCKIO::NODISK;
        return status;
    }

    uint32_t floppy_drv::getBlockCount() {
        LOG(LOG_DEBUG, "floppy_drv::getBlockCount()");
        assert(_format != nullptr);
        uint32_t count = _format->number_of_tracks * _format->sectors_per_track;
        count *= _format->double_sided ? 2 : 1;
        count *= _format->sector_size;
        count /= 512;
        return count;
    }

    // private Methods

    void floppy_drv::read_data_irq_handler() {
        // Calculate pulse duration
        uint32_t time  = _TIMER0_::TIMER0.TIMELR;
        uint32_t delta = time - _pulse_start;
        _pulse_start   = time;
        // Check pulse length
        PULSE p;
        if (delta < _pulse_M_low_threshold) {
            p = PULSE::S;
        } else if (delta > _pulse_M_high_threshold) {
            p = PULSE::L;
        } else {
            p = PULSE::M;
        }
        // Store the pulse
        _flux_buffer[_flux_buffer_count++] = p;
        // Check for buffer overflow
        if (_flux_buffer_count == sizeof(_flux_buffer)) {
            _pins.read_data.gpioDisableIrq();
        }
    }

   void floppy_drv::motor_timer_irq_handler() {
        // Switch off the spindle motor after timeout
        _pins.motor_on = HIGH;
        // Deselect the drive
        _pins.drive_select = HIGH;
    }


    void floppy_drv::motor_start_select() {
        LOG(LOG_DEBUG, "floppy_drv::motor_start_select()");
        if (_motor_timer.isRunning()) {
            // Motor is already running, just restart the timer
            _motor_timer.reset();
        } else {
            // Select the drive
            _pins.drive_select = LOW;
            // Power on the spindle motor
            _pins.motor_on = LOW;
            task::sleep_ms(_drive.motor_on_delay_ms);
            _motor_timer.start();
        }
    }

    void floppy_drv::seek_pulse() {
        LOG(LOG_DEBUG, "floppy_drv::seek_pulse()");
        _pins.step = LOW;
        task::sleep_ms(_drive.step_pulse_ms);
        _pins.step = HIGH;
        task::sleep_ms(_drive.step_interval_ms - _drive.step_pulse_ms);
    }

    void floppy_drv::seek_to_00() {
        LOG(LOG_DEBUG, "floppy_drv::seek_to_00()");
        motor_start_select();
        _pins.direction_select = HIGH;
        while(_pins.track_00) seek_pulse();
        task::sleep_ms(_drive.step_settle_time_ms);
        _current_track = 0;
    }

    void floppy_drv::seek_to_track(int track) {
        LOG(LOG_DEBUG, "floppy_drv::seek_to_track(%d)", track);
        motor_start_select();
        int delta = track - _current_track;
        _pins.direction_select = (delta < 0);
        if (delta < 0) delta = -delta;
        while(delta--) seek_pulse();
        task::sleep_ms(_drive.step_settle_time_ms);
        _current_track = track;
    }

    ret_t floppy_drv::read_track() {
        LOG(LOG_DEBUG, "floppy_drv::read_track()");
        motor_start_select();
        _pins.read_data.gpioDisableIrq();
        _flux_buffer_count = 0;

        // Calculate the pulse timing based on the floppy data rate.
        // We assume that the timer is using CLK_SYS as the clock source.
        // tmp is timer clock in kHz. Divided by 4 * data rate in
        // kHz gives the count for 1/4 of an S pulse. Multiplied by
        // 5 and 7 is the middle between S/M and M/L.
        uint32_t tmp = CLK_SYS / 1000;
        tmp /= _format->data_rate_kHz * 4;
        _pulse_M_low_threshold  = tmp * 5;
        _pulse_M_high_threshold = tmp * 7;

        // Wait for next falling INDEX pulse
        // Time out after 3 disk rotations
        uint16_t ms_per_rotation = 60000 / _drive.motor_speed_rpm;
        uint64_t timeout = task::millis() + (3 * ms_per_rotation);
        bool index_detected = false;
        while(task::millis() < timeout) {
            if (_pins.index == LOW) {
                index_detected = true;
                break;
            }
        }
        if (!index_detected) return RET_CODE::NO_DISK;

        // Read in the flux data
        _pulse_start = _TIMER0_::TIMER0.TIMERAWL;
        _pins.read_data.gpioEnableIrq();
        task::sleep_ms(ms_per_rotation);
        _pins.read_data.gpioDisableIrq();

        // Decode the flux data
        _mfm_reader.set_data_buffer(_data_buffer);
        _mfm_reader.set_data_size(_format->sectors_per_track * (_format->sector_size + 2 + sizeof(id_am_format) ));
        _mfm_reader.set_floppy_format(_format);
        _mfm_reader.reset();
        ret_t result;
        for(uint32_t i=0; i < _flux_buffer_count; ++i) {
            result = _mfm_reader.process_pulse(_flux_buffer[i]);
            if (result != RET_CODE::CONTINUE) break;
        }
        if (result == RET_CODE::SUCCESS) {
            _data_buffer_valid=true;
        }
        return result;
    }

}
