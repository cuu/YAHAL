#include "board.h"

#include "usb_dcd.h"
#include "usb_device_controller.h"
#include "usb_ms_compat_descriptor.h"
#include "usb_msc_bot_device.h"

#include "posix_io.h"
#include "uart_rp2350.h"
#include "gpio_rp2350.h"
#include "pio_rp2350.h"

//#include "spi_rp2350.h"

#include "sd_spi_drv.h"
#include "task.h"
#include "mutex.h"
#include "lock_base_rp2350.h"
#include <cstdio>
#include <cstring>

#include "mfm.pio.h"

#include "MFM_reader.h"

// SD card hardware configuration.
//#define SPI       0
//#define SCLK_PIN  2
//#define MOSI_PIN  3
//#define MISO_PIN  4
//#define CS_PIN    5

uint8_t psram[8*1024*1024] PSRAM;

using namespace _TIMER0_;

int main() {
    uart_rp2350 uart; // default is back-channel UART!

    posix_io::inst.register_stdin(uart);
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Floppy adapter GPIOs
    gpio_rp2350 index           (20);
    gpio_rp2350 drive_select_1  (18);
    gpio_rp2350 motor_on        (17);
    gpio_rp2350 direction_select(11);
    gpio_rp2350 step            (16);
    gpio_rp2350 write_data      (12);
    gpio_rp2350 write_gate      (15);
    gpio_rp2350 track_00        (13);
    gpio_rp2350 write_protect   (10);
    gpio_rp2350 read_data       (14);
    gpio_rp2350 side_one_select (2);
    gpio_rp2350 disk_change     (1);

    index.gpioMode           (GPIO::INPUT             | GPIO::PULLUP);
    drive_select_1.gpioMode  (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    motor_on.gpioMode        (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    direction_select.gpioMode(GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    step.gpioMode            (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    write_data.gpioMode      (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    write_gate.gpioMode      (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    track_00.gpioMode        (GPIO::INPUT             | GPIO::PULLUP);
    write_protect.gpioMode   (GPIO::INPUT             | GPIO::PULLUP);
    read_data.gpioMode       (GPIO::INPUT      | GPIO::PULLUP);
    side_one_select.gpioMode (GPIO::OUTPUT_OPEN_DRAIN | GPIO::PULLUP | GPIO::INIT_HIGH);
    disk_change.gpioMode     (GPIO::INPUT             | GPIO::PULLUP);

    //
    // decoder(20, 14, buffer);


    drive_select_1 = 0;
    motor_on       = 0;
    task::sleep_ms(500);

    // Find track 0
    direction_select = 1;
    while(track_00) {
        step = 0;
        task::sleep_ms(3);
        step = 1;
        task::sleep_ms(3);
    }

    task::sleep_ms(200);

    // Step out to track 80
    direction_select = 0;
    task::sleep_ms(100);

    for(int i=0; i < 0; ++i) {
        step = 0;
        task::sleep_ms(3);
        step = 1;
        task::sleep_ms(3);
    }

    task::sleep_ms(200);



//    index.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
//    read_data.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
//    side.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);

    printf("Start READ\n");

    MFM::PULSE pulse_buffer[100000] {};
    uint32_t pulse_count = 0;
    uint32_t time_start  = TIMER0.TIMELR;

    // Wait for next INDEX pulse
    while(index.gpioRead() == LOW) ;
    while(index.gpioRead() == HIGH) ;

    read_data.gpioAttachIrq(GPIO::FALLING, [&]() {
        // Calculate pulse duration
        uint32_t time  = TIMER0.TIMELR;
        uint32_t delta = time - time_start;
        time_start     = time;
        // Check pulse length
        MFM::PULSE p;
        if (delta < 500)      p = MFM::PULSE::S;
        else if (delta > 700) p = MFM::PULSE::L;
        else                  p = MFM::PULSE::M;

        pulse_buffer[pulse_count++] = p;

        if (pulse_count == sizeof(pulse_buffer)) {
            read_data.gpioDisableIrq();
        }
    });

    task::sleep_ms(200);
    read_data.gpioDisableIrq();
    motor_on = true;
    printf("Received %ld flux pulses!\n", pulse_count);


    uint8_t data_buffer[10000] {};
    MFM_reader reader(data_buffer);
    reader.set_data_size(18 * 520);
    int result;

    uint32_t st = TIMER0.TIMERAWL;
    for(uint32_t i=0; i < pulse_count; ++i) {
        //printf("proc pulse %d\n", i);
        result = reader.process_pulse(pulse_buffer[i]);
        if (result) break;
    }
    uint32_t d = TIMER0.TIMERAWL - st;
    printf("Result:   %d\n", result);
    printf("Duration: %ld\n", d/200);

//    mutex<lock_base_rp2350> m;

//    SM * mfm_sm = pio_rp2350::pio0.loadProgram(mfm_decoder_program);
//    configure_SM(mfm_sm, index.getGpio(), read_data.getGpio());
//    mfm_sm->attachRXNEMPTYIrq([&] () {
        //while(!mfm_sm->RxFifoEmpty()) {
//            uint32_t val = mfm_sm->readRxFifo();
//            m.lock();
//            if (buffer_index < 30000) {
//                buffer[buffer_index++] = val;
//            }
//            m.unlock();
        //}
//    });
//    mfm_sm->enableRXNEMPTYIrq();
//    mfm_sm->enable();

//    while(true) {
//        m.lock();
//        bool b = buffer_index >= 30000;
//        m.unlock();
//        if (b) {
//            mfm_sm->disable();
//            break;
//        }
//        task::sleep_ms(5);
//    }

//    decoder.read_track();

    printf("Stop READ\n");
//    printf("buffer index: %d\n", buffer_index);

    motor_on = 1;

//    uint8_t user_data[20000];
//    MFM_decoder decode(user_data);

//    for(int i=0; i < 15000; ++i) {
//        switch (pulse_buffer[i]) {
//            case MFM::PULSE::S: printf("S"); break;
//            case MFM::PULSE::M: printf("M"); break;
//            case MFM::PULSE::L: printf("L"); break;
//        }
//    }

    return 0;

    //    while(true) {
//        task::sleep_ms(2);
//    }




    // Set up the driver stack for the SD card
    // The SPI speed is handled in the SD card driver!
//    gpio_rp2350 cs(CS_PIN);     // CS Line of SPI interface
//    spi_rp2350  spi(SPI, MISO_PIN, MOSI_PIN, SCLK_PIN, cs);
//    sd_spi_drv  sd(spi);        // SD card low level driver

    // Switch on USB logging
    usb_log::inst.setLevel(LOG_INFO);
    // USB Device driver
    usb_dcd &driver = usb_dcd::inst();
    // USB device: Root object of USB descriptor tree
    usb_device device;
    // Generic USB Device Controller on top
    usb_device_controller controller(driver, device);

    ////////////////////////
    // USB device descriptor
    ////////////////////////
    device.set_bcdUSB         (0x0210);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x2e8a);
    device.set_idProduct      (0x0151);
    device.set_Manufacturer   ("FH Aachen");
    device.set_Product        ("MSC Test Device");

    ////////////////////////
    // USB BOS descriptor //
    ////////////////////////
    usb_ms_compat_descriptor webusb(controller, device);

    ///////////////////////////////
    // USB configuration descriptor
    ///////////////////////////////
    usb_configuration config(device);
    config.set_bConfigurationValue(1);
    config.set_bmAttributes({.remote_wakeup = 0,
                             .self_powered  = 0,
                             .bus_powered   = 1});
    config.set_bMaxPower_mA(100);

    /////////////////////
    // USB MSC BOT device
    /////////////////////
    usb_msc_bot_device msc_device(controller, config);
    msc_device.set_vendor_id  ("FH AC");
    msc_device.set_product_id ("MSC Test Device");
    msc_device.set_product_rev("1.0");

    // Set callback handlers
    msc_device.capacity_handler = [&](uint16_t &block_size,
                                      uint32_t &block_count) {
        block_size  = 512;
        block_count = 8192 * 2; //sd.getBlockCount();
    };
    msc_device.read_handler = [&](uint8_t *buff, uint32_t block) {
        memcpy(buff, psram + (block << 9), 512);
//        auto res = sd.readBlock(buff, block, 1);
//        if (res != BLOCKIO::result_t::OK) {
//            TUPP_LOG(LOG_ERROR, "Reading SD card failed (%d)", res);
//        }
//        read_active = true;
        return BLOCKIO::result_t::OK;
    };
    msc_device.write_handler = [&](uint8_t *buff, uint32_t block) {
        memcpy(psram + (block << 9), buff, 512);
//        auto res = sd.writeBlock(buff, block, 1);
//        if (res != BLOCKIO::result_t::OK) {
//            TUPP_LOG(LOG_ERROR, "Writing SD card failed (%d)", res);
//        }
//        write_active = true;
        return BLOCKIO::result_t::OK;
    };
    msc_device.is_writeable_handler = [&]() {
        return true;
    };
    msc_device.start_stop_handler = [&](bool start, bool load_eject) {
        if (load_eject && !start) {
//            driver.pullup_enable(false);
        }
    };
    msc_device.remove_handler = [&](bool prevent_removal) {
//        led_rem = prevent_removal;
    };

    // Activate USB device
    driver.pullup_enable(true);

    // Wait until USB enumeration has finished
    printf("Waiting for USB connection on USB TARGET..\n");
    while (!controller.active_configuration) {
        task::sleep_ms(10);
    }

    // The first task handles the MSC requests in an endless loop.
    task msc_worker([&]() {
        while(true) msc_device.handle_request();
    }, "MSC worker");
    msc_worker.start();

    // The second task resets the LEDs to off. Since this task has
    // the same priority as the first task, it will get runtime, but
    // sleep most of the time.
    task led_reset([&]() {
        while(true) {
            // Switch off the LEDs using their related variables
//            read_active = false;
//            write_active= false;
            // Sleep, and during this sleep the variables above
            // might be set again...
            task::sleep_ms(200);
            // Check if the LEDs reflect the needed state.
            // Change the state if needed, and wait a little
            // bit so the WS2812 do not get confused...
//            if (led_green.is_on() != read_active) {
//                led_green = read_active;
                //task::sleep_ms(5);
//            }
//            if (led_red.is_on() != write_active) {
//                led_red = write_active;
                //task::sleep_ms(5);
//            }
        }
    }, "LED reset");
//    led_reset.start();

    task::start_scheduler();
}
