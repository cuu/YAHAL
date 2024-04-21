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
///////////////////////////////////////////
// Play a single MP3 file from flash memory
///////////////////////////////////////////
//
// main() only prepares the infrastructure, namely:
//  - redirects stdout/stderr
//  - starts the main task
//  - starts the task monitor
//  - starts the scheduler
// The program logic is contained in the main_task
// and not here!

#include "uart_rp2040.h"
#include "posix_io.h"
#include "task.h"
#include "task_monitor.h"
#include "mp3_decoder_task.h"
#include "dac8311_rp2040_drv.h"

#define MOSI_PIN   7
#define SCLK_PIN   22
#define SYNC_PIN   15
#define EN_PIN     5

int main(void)
{
    // Redirect stdout to our backchannel UART, so
    // we can see the output of the task monitor
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Start Main task as privileged task
    task Main( []() {
        // Use the PCM-PWM driver for RP2040. This driver
        // will output the left/right audio on GPIO14/15.
        dac8311_rp2040_drv pcm_if(MOSI_PIN, SCLK_PIN, SYNC_PIN, EN_PIN);
        // The decoder task generates the PCM samples from
        // the MP3 file, and outputs the samples to the PCM-PWM
        mp3_decoder_task decoder(pcm_if);
        // Start decoder tasks to play the MP3
        decoder.start();
        // Wait until file has been played. The decode library
        // will automatically repeat the song, so this loop will
        // never end!
        while(decoder.isAlive()) {
            task::sleep_ms(200);
        }
    }, "Main task", 5000);
    Main.start(50, true);

    // Start the Task monitor
    task_monitor monitor;
    monitor.start();

    // Start the multitasking
    task::start_scheduler();
}
