#include "uart_msp432.h"
#include "std_io.h"
#include "gpio_msp432.h"
#include "soft_i2c_master.h"
#include "dma_msp432.h"
#include "spi_msp432.h"

#include <cstdio>
#include <cstring>

#include "i2c_commands.h"

//static void uart_esp_rx_handler(char c, void *ptr) {
//    uart_msp432 * uart = (uart_msp432 *)ptr;
//    // Forward any chars from the ESP to the back-channel UART
//    uart->putc(c);
//}
//
//void delay() {
//    for(int i=0; i < 200; ++i) ;
//}
//
//int main_old(void)
//{
//    uart_msp432 uart; // Default BC
//    std_io::inst.redirect_stdout(uart);
//
//    gpio_msp432_pin reset(PORT_PIN(10,5));
//    reset.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
//    for (int i=0; i < 1000000; ++i) ;
//    reset.gpioWrite(HIGH);
//    for (int i=0; i < 3000000; ++i) ;
//
//    uart_msp432 uart_esp(EUSCI_A3,115200);
//    uart_esp.uartAttachIrq(uart_esp_rx_handler, &uart);
//
//    gpio_msp432_pin sda(PORT_PIN(7,4));
//    gpio_msp432_pin scl(PORT_PIN(7,5));
//    soft_i2c_master i2c(sda, scl, delay);
//
//    gpio_msp432_pin gpio4(PORT_PIN(7,6));
//    gpio4.gpioMode(GPIO::INPUT);
//
//    gpio_msp432_pin led(PORT_PIN(2,1));
//    led.gpioMode(GPIO::OUTPUT);
//
//    gpio_msp432_pin esp_spi_cs(PORT_PIN(10, 0));
//    spi_msp432 esp_spi(EUSCI_B3_SPI, esp_spi_cs, SPI::SLAVE);
//    esp_spi.setSpeed(5000000);
//    EUSCI_B3_SPI->IFG = 0;
//
//    uint16_t res;
//    uint8_t buff[80];
//
//    buff[0] = WLAN_SSID;
//    strcpy((char *)(buff+1), "TG WLAN EG");
//    res = i2c.i2cWrite(0x55, buff, 30);
//
//    buff[0] = WLAN_PASSWD;
//    strcpy((char *)(buff+1), "7209142041838311");
//    res = i2c.i2cWrite(0x55, buff, 30);
//
//    buff[0] = CONN_WLAN;
//    buff[1] = 1;
//    res = i2c.i2cWrite(0x55, buff, 2);
//
//    for (int i=0; i < 10000000; ++i) ;
//
//    buff[0] = HTTP_HOST;
//    strcpy((char *)(buff+1), "dg-wdr-http-fra-dtag-cdn.cast.addradio.de");
//    res = i2c.i2cWrite(0x55, buff, 50);
//
//    buff[0] = HTTP_PORT;
//    buff[1] = 0;
//    buff[2] = 80;
//    res = i2c.i2cWrite(0x55, buff, 3);
//
//    buff[0] = HTTP_PATH;
//    strcpy((char *)(buff+1), "/wdr/wdr2/aachenundregion/mp3/128/stream.mp3");
//    res = i2c.i2cWrite(0x55, buff, 50);
//
//    buff[0] = CONN_SRV;
//    buff[1] = 1;
//    res = i2c.i2cWrite(0x55, buff, 2);
//
//    for (int i=0; i < 1000000; ++i) ;
//
//    uint8_t buffer[3612] = {0};
//
//    dma_msp432 & dma = dma_msp432::inst();
//    dma.ctrl_data[7].SRC_DATA_END_PTR = &(EUSCI_B3->RXBUF);
//    dma.ctrl_data[7].DST_DATA_END_PTR = 0;
//    dma.ctrl_data[7].CTRL.CYCLE_CTRL  = DMA::CYCLE_BASIC;
//    dma.ctrl_data[7].CTRL.N_MINUS_1   = 0;
//    dma.ctrl_data[7].CTRL.R_POWER     = DMA::ARB_AFTER_1;
//    dma.ctrl_data[7].CTRL.SRC_SIZE    = DMA::BYTE;
//    dma.ctrl_data[7].CTRL.SRC_INC     = DMA::NO_INCREMENT;
//    dma.ctrl_data[7].CTRL.DST_SIZE    = DMA::BYTE;
//    dma.ctrl_data[7].CTRL.DST_INC     = DMA::BYTE;
//    uint32_t ctrl7_backup = dma.ctrl_data[7].CTRL;
//
//    DMA_Channel->CH_SRCCFG[7] = 2;
//    DMA_Control->CFG          = DMA_STAT_MASTEN;
//
//    buff[0] = DATA_SIZE;
//    buff[1] = 3612 / 256;
//    buff[2] = 3612 % 256;
//    res = i2c.i2cWrite(0x55, buff, 3);
//
//    while(1) {
//        led.gpioWrite( gpio4.gpioRead());
//        if (gpio4.gpioRead()) {
//
//            buff[0] = SEND_DATA;
//            buff[1] = 1;
//            res = i2c.i2cWrite(0x55, buff, 2);
//
//            int size = 3612;
//            uint8_t *bufptr = buffer;
//            while (size) {
//                int rec = (size >= 1024) ? 1024 : size;
//                // Trigger a DMA transfer ...
//                dma.ctrl_data[7].CTRL  = ctrl7_backup;
//                bufptr += rec;
//                dma.ctrl_data[7].DST_DATA_END_PTR = bufptr - 1;
//                dma.ctrl_data[7].CTRL.N_MINUS_1   = rec - 1;
//                DMA_Control->ALTCLR    = BIT7;
//                DMA_Control->ENASET    = BIT7;
//                // Wait for DMA to complete
//                while(DMA_Control->ENASET & BIT7) ;
//                size -= rec;
//            }
//
//            // Trigger a DMA transfer ...
////            dma.ctrl_data[7].CTRL  = ctrl7_backup;
////            DMA_Channel->SW_CHTRIG = BIT7;
////            for (int i=0; i < 1000000; ++i) ;
////            for (int i=0; i < 1000000; ++i) ;
//        }
//    }
//
//    return 0;
//}
