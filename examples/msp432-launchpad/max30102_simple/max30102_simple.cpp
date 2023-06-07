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

#include <cstdio>
#include "uart_msp432.h"
#include "posix_io.h"
#include "max30102_drv.h"
#include "i2c_msp432.h"

int main(void)
{
    uart_msp432 uart; // default is backchannel UART!

    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );
    posix_io::inst.register_stderr( uart );

    // Initialize I2C port
    i2c_msp432 i2c(EUSCI_B3);
    i2c.setSpeed(400000);

    // Setup MAX30102 sensor
    max30102_drv max(i2c);
    max.setup_sensor();

    while(true) {
        if (max.check()) {
            uint32_t ir_value = max.get_slot_data(0);
            uint32_t red_value = max.get_slot_data(1);
            printf("%ld %ld\n", ir_value, red_value);
        }
    }
}

