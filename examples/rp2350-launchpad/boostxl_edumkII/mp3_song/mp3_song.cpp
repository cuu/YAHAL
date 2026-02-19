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

#include "boostxl_eduMKII.h"
#include "mp3_decoder_task.h"
#include "pcm_pwm_rp2350_drv.h"
#include "posix_io.h"
#include "task.h"
#include "task_monitor.h"
#include "uart_rp2350.h"

int main()
{
    // Redirect stdout to our back channel UART, so
    // we can see the output of the task monitor
    uart_rp2350 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Start Main task as privileged task
    task Main( []() {
        // Use the PCM-PWM driver for RP2350. This driver
        // will output the mono audio channel on the
        // buzzer/loudspeaker of the Edu-MKII boosterpack.
        pcm_pwm_rp2350_drv pcm_if(EDU_BUZZER);
        // The decoder task generates the PCM samples from
        // the MP3 file, and outputs the samples to the PCM-PWM
        mp3_decoder_task decoder(pcm_if);
        // Start decoder tasks to play the MP3
        decoder.sign_up();
        // Wait until file has been played. The decode library
        // will automatically repeat the song, so this loop will
        // never end!
        while(decoder.isLinkedIn()) {
            task::sleep_ms(200);
        }
    }, "Main task", 5000);
    Main.sign_up(core_t::CURRENT_CORE, 50, true);

    // Start the Task monitor
    task_monitor monitor;
    monitor.sign_up();

    // Start the multitasking
    task::start_scheduler();
}
