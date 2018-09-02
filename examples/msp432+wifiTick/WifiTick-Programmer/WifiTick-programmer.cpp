///////////////////////////////////////////////
//
// WifiTick programmer
// (c) 2017 A. Terstegge
//
// Button S1: Reset line of ESP8266
// Button S2: GPIO0 line of ESP8266
//
// To program the ESP8266, S2 has to be pressed
// while S1 is being released.
// The backchannel uart of the MSP432 lauchpad
// is used for programming the ESP8266
// (baudrate is 115200).
//
// This program features automatic baud rate
// selection on the ESP8266 side, so the boot
// messages are also readable!
//
///////////////////////////////////////////////

#include "gpio_msp432.h"
#include "uart_msp432.h"

/////////////////////////////////
// Hardware-dependent section. //
/////////////////////////////////

struct HW {

    // HW components
    ////////////////
    gpio_msp432_pin button_s1;
    gpio_msp432_pin button_s2;
    gpio_msp432_pin esp_gpio0;
    gpio_msp432_pin esp_gpio2;
    gpio_msp432_pin red_led;
    gpio_msp432_pin esp_reset;
    uart_msp432     uart_bc;  // back-channel UART
    uart_msp432     uart_esp; // ESP8266 UART

    HW() :
        // HW configuration
        ///////////////////
        button_s1( PORT_PIN( 1, 1) ),
        button_s2( PORT_PIN( 1, 4) ),
        esp_gpio0( PORT_PIN( 7, 4) ),
        esp_gpio2( PORT_PIN( 7, 5) ),
        red_led  ( PORT_PIN( 8, 0) ),
        esp_reset( PORT_PIN(10, 5) ),
        uart_bc  ( EUSCI_A0,115200 ),
        uart_esp ( EUSCI_A3,115200 ) {
    }
};

///////////////////////////////////
// Hardware-independent section. //
///////////////////////////////////

// declaration of IRQ handlers
void button_s1_handler(uint16_t);
void uart_bc_rx_handler (char);
void uart_esp_rx_handler(char);

class Main {

    HW hw;
    bool baud_is_115200 = true;
    bool baud_is_set    = true;
    bool in_prgm_mode   = false;

public:

    // The IRQ handlers are our best friends
    friend void button_s1_handler(uint16_t);
    friend void uart_bc_rx_handler (char);
    friend void uart_esp_rx_handler(char);

    void main() {

        // Initialize GPIOs
        hw.button_s1.gpioMode( GPIO::INPUT | GPIO::PULLUP);
        hw.button_s1.gpioAttachIrq(button_s1_handler, GPIO::RISING);
        hw.button_s2.gpioMode( GPIO::INPUT | GPIO::PULLUP);
        hw.esp_gpio0.gpioMode( GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH );
        hw.esp_gpio2.gpioMode( GPIO::INPUT );
        hw.red_led  .gpioMode( GPIO::OUTPUT | GPIO::INIT_LOW  );
        hw.esp_reset.gpioMode( GPIO::OUTPUT | GPIO::INIT_HIGH );

        // Initialize UARTs
        hw.uart_bc. uartAttachIrq(uart_bc_rx_handler);
        hw.uart_esp.uartAttachIrq(uart_esp_rx_handler);

        // The never-ending main loop
        while(true) {
            // Handle buttons in main loop
            hw.esp_reset.gpioWrite( hw.button_s1.gpioRead() );
            hw.esp_gpio0.gpioWrite( hw.button_s2.gpioRead() );

            // Display the inverse of ESP gpio2 on the
            // red LED. This behavior is similar to the
            // well-known ESP-12-E module
            hw.red_led.gpioWrite( !hw.esp_gpio2.gpioRead() );

            // Change the baud-rate if needed
            if (!baud_is_set) {
                hw.uart_esp.setBaudrate( baud_is_115200 ? 115200 : 74880);
                baud_is_set = true;
            }
        }
    }
};

Main m;

// This handler is called when the
// Reset button (S1) is released
void button_s1_handler(uint16_t) {
    // Small delay for debounce
    for(int i=0; i < 200; ++i) ;
    // Check the program button (S2)
    m.in_prgm_mode   = !m.hw.button_s2.gpioRead();
    m.baud_is_115200 = false;
    m.baud_is_set    = false;
}

void uart_bc_rx_handler(char c) {
    // Forward any chars from the back-channel UART to the ESP
    m.hw.uart_esp.putc(c);
}

void uart_esp_rx_handler(char c) {
    static char magic_prgm[] = "\r\n\r\n";
    static char magic_run[]  = "~ld\n";
    static uint8_t cnt  = 0;

    // Forward any chars from the ESP to the back-channel UART
    m.hw.uart_bc.putc(c);

    // No check for magic strings during programming
    if (m.in_prgm_mode && m.baud_is_115200) return;

    // Simple state machine to check magic string
    const char * magic_ptr = m.in_prgm_mode ? magic_prgm : magic_run;
    switch(cnt) {
    case 0: if (c==magic_ptr[0]) cnt = 1; break;
    case 1: if (c==magic_ptr[1]) cnt = 2; else cnt = 0; break;
    case 2: if (c==magic_ptr[2]) cnt = 3; else cnt = 0; break;
    case 3: if (c==magic_ptr[3]) {
        // Change back to 115200 baud...
        m.hw.uart_bc.putc('\r');
        m.baud_is_115200 = true;
        m.baud_is_set    = false;
    } else
        cnt = 0;
    }
}

int main(void)
{
    m.main();
    return 0;
}

