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
///////////////////////////////////////////////////////
// MP3 player for RP2040 launchpad and boostxl-audio //
///////////////////////////////////////////////////////
//
// main() only prepares the infrastructure, namely:
//  - redirects stdout
//  - starts the main task
//  - starts the task monitor
//  - starts the scheduler
// The program logic is contained in the main_task
// and not here!

#include <cstdint>
#include "uart_rp2040.h"
#include "posix_io.h"
#include "main_task.h"
#include "task_monitor.h"

int main(void)
{
    // Redirect stdout to our backchannel UART, so
    // we can see the output of the task monitor
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Start Main task as privileged task, because
    // it has to initialize the PIO stuff...
    main_task Main;
    Main.start(50, true);

    // Start the Task monitor
    task_monitor monitor;
    monitor.start();

    // Start the multitasking
    task::start_scheduler();
}
