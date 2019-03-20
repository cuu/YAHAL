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

#include <cstring>

#include "stream_reader_task.h"
#include "i2c_commands.h"
//#include "dma_msp432.h"
#include "yahal_assert.h"


#define I2C_ADDR 0x55

void __attribute__((optimize("O0"))) delay(uint32_t us) {
    for(int i=0; i < 200; ++i) ;
}

void __attribute__((optimize("O0"))) delay1(uint32_t us) {
    for(int i=0; i < 100; ++i) ;
}

stream_reader_task::stream_reader_task() : task("MP3 stream", 500),
    _sda(PORT_PIN(7,4)),
    _scl(PORT_PIN(7,5)),
    _i2c(_sda, _scl, delay),
    //_reset    (PORT_PIN(10,5)),
    _esp_spi_cs(PORT_PIN(10, 0)),
    _esp_spi(EUSCI_B3_SPI, _esp_spi_cs),
    _oneQuarter(PORT_PIN(9,7)),
    _twoQuarters(PORT_PIN(7,6)),
    _threeQuarters(PORT_PIN(7,7)),
    _ctrl7_backup(0),
    _req_buff(nullptr),
    _req_btr(0),
    _req_br(nullptr),
    _req_result(0),
    _execute(false)
{
    _oneQuarter.gpioMode(GPIO::INPUT);
    _twoQuarters.gpioMode(GPIO::INPUT);
    _threeQuarters.gpioMode(GPIO::INPUT);
    //_reset.    gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);

    _esp_spi.setSpeed(15000000);
    _esp_spi.generateCS(false);

    _i2c.init();

//    sleep(1500);
//    _reset.gpioWrite(HIGH);
//    sleep(1500);
}

void stream_reader_task::connectToWlan(const char *ssid, const char *passwd) {
    char buff[80];
    int  res,len;

    buff[0] = WLAN_SSID;
    strcpy(buff+1, ssid);
    len = strlen(ssid)+2;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, len);
    yahal_assert(res == len);

    buff[0] = WLAN_PASSWD;
    strcpy(buff+1, passwd);
    len = strlen(passwd)+2;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, len);
    yahal_assert(res == len);

    buff[0] = CONN_WLAN;
    buff[1] = 1;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 2);
    yahal_assert(res == 2);

    sleep(5000);
//    do {
//        sleep(5000);
//        res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 1, false);
//        yahal_assert(res == 1);
//        res = _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 1);
//        yahal_assert(res == 1);
//    } while (buff[1]);
}

void stream_reader_task::connectToSrv(const char *host, int port, const char *path) {
    char buff[80];
    int  res,len;

    buff[0] = HTTP_HOST;
    strcpy(buff+1, host);
    len = strlen(host)+2;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, len);
    yahal_assert(res == len);

    buff[0] = HTTP_PORT;
    buff[1] = port / 256;
    buff[2] = port % 256;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 3);
    yahal_assert(res == 3);

    buff[0] = HTTP_PATH;
    strcpy(buff+1, path);
    len = strlen(path)+2;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, len);
    yahal_assert(res == len);

    buff[0] = CONN_SRV;
    buff[1] = 1;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 2);
    yahal_assert(res == 2);

    sleep(1000);
//    do {
//        sleep(500);
//        res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 1, false);
//        yahal_assert(res == 1);
//        res = _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 1);
//        yahal_assert(res == 1);
//    } while (buff[1]);
}

int stream_reader_task::read_data(uint8_t* buff, uint16_t btr, uint16_t* br) {
    // Copy request parameters
    _req_buff = buff;
    _req_btr  = btr;
    _req_br   = br;
    // Trigger task execution
    _execute_mutex.lock();
    _execute = true;
    _execute_mutex.unlock();
    _execute_cv.notify_one();
    // Wait for execution to complete
    _caller_cv.wait(_caller_mutex, [this]() {return !_execute;});
    // Return the result of the execution
    return _req_result;
}

void stream_reader_task::run() {
    char buff[80];
    int  res;

//    dma_msp432 & dma = dma_msp432::inst();
//    dma.ctrl_data[7].SRC_DATA_END_PTR = &(EUSCI_B3->RXBUF);
//    dma.ctrl_data[7].CTRL.CYCLE_CTRL  = DMA::CYCLE_BASIC;
//    dma.ctrl_data[7].CTRL.R_POWER     = DMA::ARB_AFTER_1;
//    dma.ctrl_data[7].CTRL.SRC_SIZE    = DMA::BYTE;
//    dma.ctrl_data[7].CTRL.SRC_INC     = DMA::NO_INCREMENT;
//    dma.ctrl_data[7].CTRL.DST_SIZE    = DMA::BYTE;
//    dma.ctrl_data[7].CTRL.DST_INC     = DMA::BYTE;
//    _ctrl7_backup = dma.ctrl_data[7].CTRL;
//
//    DMA_Channel->CH_SRCCFG[7] = 2;
//    DMA_Control->CFG          = DMA_STAT_MASTEN;
//    DMA_Control->PRIOSET      = BIT7;

    //if (!_oneQuarter.gpioRead()) sleep(20);

    while(!_twoQuarters.gpioRead()) sleep(20);

    do {
        // Wait for a new request
        _execute_cv.wait(_execute_mutex, [this]() {return _execute;});

        // Send the amount of bytes needed
        buff[0] = DATA_SIZE;
        buff[1] = _req_btr / 256;
        buff[2] = _req_btr % 256;
        res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 3);
        yahal_assert(res == 3);

        uint8_t minibuf[2];
        minibuf[0] = 0x03;
        minibuf[1] = 0x00;

        // Receive the data
        *_req_br = 0;
        while (_req_btr) {
            int rec = (_req_btr >= 32) ? 32 : _req_btr;

            _esp_spi.setCS(LOW);
            _esp_spi.spiTx(minibuf, 2);
            _esp_spi.spiRx(0, _req_buff, rec);
            _esp_spi.setCS(HIGH);

            delay1(0);

            _req_buff += rec;
            _req_btr  -= rec;
            *_req_br  += rec;
        }

        // We have no errors ...
        _req_result = 0;
        // Notify end of execution
        _execute = false;
        _caller_cv.notify_one();
    } while (true);
}
