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
#include "task.h"

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

class Main {
public:

    void main() {

        // Initialize GPIOs
        hw.button_s1.gpioMode( GPIO::INPUT | GPIO::PULLUP);
        hw.button_s1.gpioAttachIrq(GPIO::RISING, [this]() {
            // Small delay for debounce
            task::sleep_ms(20);
            // Check the program button (S2)
            in_prgm_mode   = !hw.button_s2.gpioRead();
            baud_is_115200 = false;
            baud_is_set    = false;
        });
        hw.button_s2.gpioMode( GPIO::INPUT | GPIO::PULLUP);
        hw.esp_gpio0.gpioMode( GPIO::OUTPUT_OPEN_DRAIN | GPIO::INIT_HIGH );
        hw.esp_gpio2.gpioMode( GPIO::INPUT );
        hw.red_led  .gpioMode( GPIO::OUTPUT | GPIO::INIT_LOW  );
        hw.esp_reset.gpioMode( GPIO::OUTPUT | GPIO::INIT_HIGH );

        // Initialize UARTs
        // Forward any chars from the back-channel UART to the ESP
        hw.uart_bc.uartAttachIrq([this](char c) { hw.uart_esp.putc(c); });

        // Forward any chars from the ESP to the back-channel UART
        hw.uart_esp.uartAttachIrq([this](char c) {
            static char magic_prgm[] = "\r\n\r\n";
            static char magic_run[]  = "~ld\r";
            static uint8_t cnt  = 0;

            hw.uart_bc.putc(c);

            // No check for magic strings during programming
            if (in_prgm_mode && baud_is_115200) return;

            // Simple state machine to check magic string
            const char * magic_ptr = in_prgm_mode ? magic_prgm : magic_run;
            switch(cnt) {
            case 0: if (c==magic_ptr[0]) cnt = 1; break;
            case 1: if (c==magic_ptr[1]) cnt = 2; else cnt = 0; break;
            case 2: if (c==magic_ptr[2]) cnt = 3; else cnt = 0; break;
            case 3: if (c==magic_ptr[3]) {
                // Change back to 115200 baud...
                hw.uart_bc.putc('\r');
                baud_is_115200 = true;
                baud_is_set    = false;
            } else
                cnt = 0;
            }
        });

        // Put ESP8266 to programming mode as default
        hw.esp_reset.gpioWrite( LOW );  task::sleep_ms(100);
        hw.esp_gpio0.gpioWrite( LOW );  task::sleep_ms(100);
        hw.esp_reset.gpioWrite( HIGH ); task::sleep_ms(100);
        
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

private:

    HW hw;
    bool baud_is_115200 = true;
    bool baud_is_set    = true;
    bool in_prgm_mode   = false;
};

int main(void)
{
    Main m;
    m.main();
    return 0;
}

