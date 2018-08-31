
#include "uart_msp432.h"
#include "std_io.h"
#include "i2c_msp432.h"
#include <cstdio>

int main(void)
{
    // Initialize backchannel UART
    uart_msp432 uart;
    std_io::inst.redirect_stdout( uart );

    // Our OPT3001 is connected to EUSCI_B1
    // with i2c adress 0x44
    i2c_msp432 light( EUSCI_B1 );

    // Buffers needed for i2c communication
    uint8_t rxbuf[2];
    uint8_t txbuf[3];

    // Write the 'Configuration'
    // (default is 0xc819)
    txbuf[0] = 0x01;
    txbuf[1] = 0xce; // MSB
    txbuf[2] = 0x00; // LSB
    light.i2cWrite(0x44, txbuf, 3);

    while (1) {
        // Set the configuration register
        txbuf[0] = 0x01;
        light.i2cWrite(0x44, txbuf, 1);

        // Wait until conversion is ready
        while(1) {
            light.i2cRead(0x44, rxbuf, 2);
            if (rxbuf[1] & 0x80)
                break;
        }

        // Set the result register
        txbuf[0] = 0x00;
        light.i2cWrite(0x44, txbuf, 1);

        // Read the raw light value
        light.i2cRead(0x44, rxbuf, 2);

        // Calculate raw value from both bytes
        uint16_t val = rxbuf[0] * 256 + rxbuf[1];

        printf("Raw value: %x\n", val);
    }
}
