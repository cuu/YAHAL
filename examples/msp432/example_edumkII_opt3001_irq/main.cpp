
// Example showing how to operate the OPT3001
// with interrupts. GPIO 4.6 is connected to
// the (open drain) IRQ output of the OPT3001.
// GPIO 4.6 is configured to generate a interrupt
// on falling edges. The handler then reads and
// prints the raw light value, and resets the
// IRQ line by reading the config register.
// Find details of the OPT3001 IRQ generation
// in the OPT3001 data sheet.

#include "gpio_msp432.h"
#include "uart_msp432.h"
#include "std_io.h"
#include "i2c_msp432.h"
#include <cstdio>

// Global objects
i2c_msp432      opt3001( EUSCI_B1 );
gpio_msp432_pin opt_irq( PORT_PIN(4,6) );

uint8_t rxbuf[2];
uint8_t txbuf[3];

// Handler to process a OPT3001 interrupt

void handler(gpio_pin_t gpio, void *) {
    (void)(gpio);
    // Read the Result register
    txbuf[0] = 0x00;
    opt3001.i2cWrite(0x44, txbuf, 1);
    opt3001.i2cRead (0x44, rxbuf, 2);
    uint16_t raw = (rxbuf[0] << 8) + rxbuf[1];
    printf("Raw light value: %x\n", raw);

    // Read the Configuration register
    // to reset the IRQ line
    txbuf[0] = 0x01;
    opt3001.i2cWrite(0x44, txbuf, 1);
    opt3001.i2cRead (0x44, rxbuf, 2);
}


int main(void)
{
    // Initialize backchannel UART
    uart_msp432 uart;
    std_io::inst.redirect_stdout( uart );

    // Initialize GPIOs
    opt_irq.gpioMode(GPIO::INPUT);
    opt_irq.gpioAttachIrq(GPIO::FALLING, handler);

    // Reset OPT3001
    txbuf[0] = 0x06;
    opt3001.i2cWrite(0x00, txbuf, 1);

    // Write the 'Configuration'
    // (default is 0xc819)
    txbuf[0] = 0x01;
    txbuf[1] = 0xce; // MSB
    txbuf[2] = 0x10; // LSB
    opt3001.i2cWrite(0x44, txbuf, 3);

    // Write the 'LOW' register
    txbuf[0] = 0x02;
    txbuf[1] = 0xff;
    txbuf[2] = 0xff;
    opt3001.i2cWrite(0x44, txbuf, 3);

    while (1) {
        // Sleep until we receive a interrupt
        __WFE();
    }
}


