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
// Play a single PCM datasets on the audio adapter.
//
#include "board.h"
#include "gpio_rp2040.h"
#include "pcm_pwm_rp2040_drv.h"
#include "posix_io.h"
#include "task.h"
#include "task_monitor.h"
#include "uart_rp2040.h"

// Some samples
#include "gen/hat1.h"
#include "gen/hat2.h"
#include "gen/kick.h"
#include "gen/snare.h"

class pcm_task : public task {
public:
    pcm_task() :  task("PCM Task"), _pcm_if(9, 11) {
        _pcm_if.setPcmRate(44100);
    }

    void run() override {
        while (true) {
            play_pcm(hat1.data(),  hat1.size());
            task::sleep_ms(50);
            play_pcm(hat2.data(),  hat2.size());
            task::sleep_ms(50);
            play_pcm(kick.data(),  kick.size());
            task::sleep_ms(50);
            play_pcm(snare.data(), snare.size());
            task::sleep_ms(50);
        }
    }

    void play_pcm(const uint16_t * sample, uint32_t len) {
        _pcm_if.timer_reset();
        pcm_value_t pcm;
        for (uint32_t i=0; i < len/sizeof(int16_t); i += 2) {
            pcm.left  = (int16_t) sample[i];
            pcm.right = (int16_t) sample[i+1];
            // Wait for free space in FIFO
            while (!_pcm_if.pcmFifoAvailablePut()) task::sleep_ms(5);
            _pcm_if.pcmFifoPut(pcm);
        }
    }

private:
    pcm_pwm_rp2040_drv _pcm_if;
};

int main(void)
{
    // Redirect stdout and stderr to our backchannel UART,
    // so we can see the output of the task monitor
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    pcm_task task1;
    task1.sign_up();

    gpio_rp2040 led(LED_RED_GPIO);
    led.gpioMode(GPIO::OUTPUT);
    task task2([&]() {
        // Endless loop
        while(true) {
            led.gpioToggle();
            task::sleep_ms(500);
        }
    }, "LED Task");
    task2.sign_up();

    task_monitor monitor;
    monitor.sign_up();

    task::start_scheduler();
}
