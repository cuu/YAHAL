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
// A simple example using a I2C interface of
// the RP2040. The I2C interface is used to
// directly read/write data to the OPT3001
// light sensor. The raw light value is printed
// on the backchannel uart.

#include "uart_rp2040.h"
#include "posix_io.h"
#include "i2c_rp2040.h"
#include "mpu6050.h"

#include "task.h"
#include <cstdio>

#define ever (;true;)

int main()
{
    // Initialize backchannel UART
    uart_rp2040 uart;
    posix_io::inst.register_stdout(uart);
    posix_io::inst.register_stderr(uart);

    // Initialize I2C port
    i2c_rp2040 i2c(1, 10, 11, 0);
    i2c.setSpeed(400000); // Set speed to 100kHz

    MPU6050_Init(i2c);

    for ever {
        float temp = MPU6050_countTemp(i2c);
        printf("Temp: %d\n", (int)temp );
        int32_t * accel = MPU6050_getAccel(i2c);
        printf("X: %d\n", accel[0] );
        printf("Y: %d\n", accel[1] );
        printf("Z: %d\n", accel[2] );
        task::sleep_ms(1000);
    }

}
