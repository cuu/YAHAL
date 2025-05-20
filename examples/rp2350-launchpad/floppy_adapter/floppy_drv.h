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
#ifndef FLOPPY_DRV_H
#define FLOPPY_DRV_H

#include <cassert>
#include "block_io_interface.h"
#include "timer_interface.h"
#include "floppy_defines.h"
#include "floppy_mfm_reader.h"

namespace FLOPPY {

    class floppy_drv : public block_io_interface {
    public:

        friend class floppy_statistics;

        // The CTOR. The user has to provide the pin configuration,
        // the floppy drive type and a timer for the spindle motor
        floppy_drv(floppy_pins &, floppy_drive &,
                   timer_interface & motor_timer);

        // Global read access to the driver. Will be used e.g.
        // by the statistics class.
        static const floppy_drv * inst;

        // Initialize the drive. The method will:
        //   - try to detect if a disk is present
        //   - if yes, try to detect the floppy format
        //     (if not specified by set_format())
        // This method will do basically nothing when
        // called on an already initialized driver object.
        ret_t init();

        // Read-only access to the current floppy format.
        // If nullptr, no valid format has been detected
        // or there is no disk in the drive.
        const floppy_format * const & format;

        // (Optionally) set the floppy disk format
        inline void set_format(floppy_format * f) {
            _format = f;
        }

        // Read a single sector. The method will first call
        // init() (see above) The method will then check if
        // the track data is already in the data buffer and
        // use this data if possible. If the method returned
        // SUCCESS, ptr will point to the sector data. In
        // case of errors, ptr will be set to nullptr.
        ret_t read_sector(uint8_t track, uint8_t head, uint8_t sector, uint8_t * & ptr);

        // Calibrate the head (seek to track 0, then to maximum track
        // and then back to 0 again). Afterward try to autodetect the
        // floppy format.
        blockio_status_t initialize() override;

        // Return the current device status
        blockio_status_t status() override;

        // Read in 'count' 512-byte blocks. Start reading at 'start_block'.
        // Store the data in buff, which has to point to a memory buffer
        // with at least 512 * count bytes size.
        BLOCKIO::result_t readBlock(uint8_t* buff, uint32_t start_block,
                                    uint16_t count) override {

            return BLOCKIO::result_t::OK;
        }

        // Write 'count' 512-byte blocks. Start storing at 'start_block'.
        // Read the data from buff, which has to point to a memory buffer
        // with at least 512 * count bytes size.
        BLOCKIO::result_t writeBlock(const uint8_t* buff, uint32_t start_block,
                                     uint16_t count) override {
            return BLOCKIO::result_t::OK;
        }

        // Get the block count (total size of device is 512 * count bytes)
        uint32_t getBlockCount() override;

        // Sync the IO device (dirty buffers are written)
        BLOCKIO::result_t sync() override {
            // Nothing to do unless we write data to disk
            return BLOCKIO::result_t::OK;
        }

    private:
        floppy_pins &       _pins;
        floppy_drive &      _drive;
        floppy_format *     _format {nullptr};
        timer_interface &   _motor_timer;

        int _current_track {0};

        // Flux and MFM reader stuff
        floppy_mfm_reader  _mfm_reader;
        uint32_t    _pulse_M_low_threshold {0};
        uint32_t    _pulse_M_high_threshold {0};
        PULSE       _flux_buffer[100000] {};
        uint32_t    _flux_buffer_count {0};
        uint32_t    _pulse_start {0};
        uint8_t     _data_buffer[12000] {};
        bool        _data_buffer_valid {false};

        // The IRQ handler for the READ_DATA line
        void read_data_irq_handler();

        // The motor timer IRQ handler
        void motor_timer_irq_handler();

        // Start the motor and select the drive.
        // The motor will be automatically switched
        // off by a timer after the defined follow-up time.
        void motor_start_select();

        // Methods to move the head
        void seek_pulse();
        void seek_to_00();
        void seek_to_track(int track);

        // Read the current track into the flux and data buffers.
        ret_t read_track();
    };

}
#endif // FLOPPY_DRV_H
