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


void uart_esp_rx_handler(char c, void *ptr) {
    uart_msp432 * uart = (uart_msp432 *)ptr;
    // Forward any chars from the ESP to the back-channel UART
    uart->putc(c);
}

int main(void)
{
    // Redirect stdout to our backchannel UART, so
    // we can see the output of the task monitor
    uart_msp432 uart;
    std_io::inst.redirect_stdout(uart);

    // Also redirect the ESP8266 serial output to
    // the backchannel UART
    uart_msp432 uart_esp(EUSCI_A3,115200);
    uart_esp.uartAttachIrq(uart_esp_rx_handler, &uart);

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
