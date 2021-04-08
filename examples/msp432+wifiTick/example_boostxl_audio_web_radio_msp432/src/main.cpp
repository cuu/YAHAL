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
// MP3 player for MSP432 launchpad and boostxl-audio //
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
#include "uart_msp432.h"
#include "std_io.h"
#include "main_task.h"
#include "task_monitor.h"

uart_msp432 uart_esp(EUSCI_A3,74880);


void uart_esp_rx_handler(char c, void *ptr) {
    static char magic_run[]  = "~ld\n";
    static uint8_t cnt  = 0;
    uart_msp432 * uart = (uart_msp432 *)ptr;

    // Forward any chars from the ESP to the back-channel UART
    uart->putc(c);

    // Simple state machine to check magic string
    const char * magic_ptr = magic_run;
    switch(cnt) {
    case 0: if (c==magic_ptr[0]) cnt = 1; break;
    case 1: if (c==magic_ptr[1]) cnt = 2; else cnt = 0; break;
    case 2: if (c==magic_ptr[2]) cnt = 3; else cnt = 0; break;
    case 3: if (c==magic_ptr[3]) {
        // Change back to 115200 baud...
        uart->putc('\r');
        uart_esp.setBaudrate(115200);
    } else
        cnt = 0;
    }
}

int main(void)
{
//    Clock_Init48MHz();

    // Redirect stdout to our backchannel UART, so
    // we can see the output of the task monitor
    uart_msp432 uart;
    std_io::inst.redirect_stdout(uart);

    // Also redirect the ESP8266 serial output to
    // the backchannel UART
    uart_esp.uartAttachIrq([&](char c) {
        static char magic_run[]  = "~ld\n";
        static uint8_t cnt  = 0;

        // Forward any chars from the ESP to the back-channel UART
        uart.putc(c);

        // Simple state machine to check magic string
        const char * magic_ptr = magic_run;
        switch(cnt) {
        case 0: if (c==magic_ptr[0]) cnt = 1; break;
        case 1: if (c==magic_ptr[1]) cnt = 2; else cnt = 0; break;
        case 2: if (c==magic_ptr[2]) cnt = 3; else cnt = 0; break;
        case 3: if (c==magic_ptr[3]) {
            // Change back to 115200 baud...
            uart.putc('\r');
            uart_esp.setBaudrate(115200);
        } else
            cnt = 0;
        }
    });

    // Start Main task as privileged task, because
    // it has to initialize the DMA stuff...
    main_task Main;
    Main.start(50, true);

    // Start the Task monitor
//    task_monitor monitor;
//    monitor.start();

    // Start the multitasking
    task::start_scheduler();
}
