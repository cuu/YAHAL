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
#include <cstdint>
#include "uart_msp432.h"
#include "std_io.h"
#include "main_task.h"
#include "task_monitor.h"

int main(void)
{
    // Redirect stdout to our backchannel UART, so
    // we can see the output of the task monitor
    uart_msp432 uart;
    std_io::inst.redirect_stdout(uart);

    // Start Main task as privileged task, because
    // it has to initialize the DMA stuff...
    main_task Main;
    Main.start(50, true);

    // Start the Task monitor
    task_monitor monitor;
    monitor.start();

    // Start the multitasking
    task::start_scheduler();
}
