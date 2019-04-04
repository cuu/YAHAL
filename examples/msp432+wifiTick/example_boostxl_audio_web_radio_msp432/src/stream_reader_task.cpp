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
#include <cstdio>

#include "stream_reader_task.h"
#include "i2c_commands.h"
//#include "dma_msp432.h"
#include "yahal_assert.h"


#define I2C_ADDR 0x55

void __attribute__((optimize("O0"))) delay(uint32_t us) {
    for(int i=0; i < 150; ++i) ;
}

void __attribute__((optimize("O0"))) delay1(uint32_t us) {
    for(int i=0; i < 100; ++i) ;
}

stream_reader_task::stream_reader_task(audio_output & ao) : task("MP3 stream", 500),
    _wifi_tick( [this] (uint32_t ms) { sleep(ms); } ),
    _sda(PORT_PIN(7,4)),
    _scl(PORT_PIN(7,5)),
    _i2c(_sda, _scl, delay),
    _esp_spi_cs(PORT_PIN(10, 0)),
    _esp_spi(EUSCI_B3_SPI, _esp_spi_cs),
    _req_buff(nullptr),
    _req_btr(0),
    _req_br(nullptr),
    _req_result(0),
    _execute(false),
    _audio_output(ao),
    _eof(false)
{
    _esp_spi.setSpeed(10000000);
    _esp_spi.generateCS(false);
    _i2c.init();
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

    buff[0] = CONNECT_WLAN;
    buff[1] = 1;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 2);
    yahal_assert(res == 2);

    // Wait until ESP8266 is connected to WLAN
    do {
        sleep(500);
        res = _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 1);
        if (res != 1) continue;
    } while (buff[1]);
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

    buff[0] = CONNECT_SERVER;
    buff[1] = 1;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 2);
    yahal_assert(res == 2);

    _eof = false;

    // Wait until ESP8266 is connected to server
    do {
        sleep(500);
        res = _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 1);
        if (res != 1) continue;
    } while (buff[1]);
}


void stream_reader_task::stopSrv() {
    char buff[80];
    int  res;

    buff[0] = STOP_SERVER;
    buff[1] = 1;
    res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 2);
    yahal_assert(res == 2);

    _eof = true;

    // Wait until ESP8266 is connected to server
    do {
        sleep(500);
        res = _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 1);
        if (res != 1) continue;
    } while (buff[1]);
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

    _wifi_tick.led(HIGH);
    _wifi_tick.reset();
    _wifi_tick.led(LOW);

    do {
        // Wait for a new request
        /////////////////////////
        _execute_cv.wait(_execute_mutex, [this]() {return _execute;});

        // Get the size of the FIFO on the ESP8266
        //////////////////////////////////////////
        buff[0] = FIFO_SIZE;
        res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 1, false);
        yahal_assert(res == 1);
        res = _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 2);
        yahal_assert(res == 2);
        int fifo_size = buff[1] * 256 + buff[2];

        int err = fifo_size - 20000;
        err /= 10;
        _audio_output.addToOffset(err);

        // Send the amount of bytes needed and
        // wait until data is available
        buff[0] = READ_DATA;
        buff[1] = _req_btr / 256;
        buff[2] = _req_btr % 256;
        res = _i2c.i2cWrite(I2C_ADDR, (uint8_t *)buff, 3);
        yahal_assert(res == 3);

        // Wait until data is prepared
        do {
            sleep(20);
            _i2c.i2cRead(I2C_ADDR, (uint8_t *)buff+1, 2);
        } while (buff[1] || buff[2]);

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
        // Read the metadata
//        for (int i=0; i < 320; i+=32) {
//            _esp_spi.setCS(LOW);
//            _esp_spi.spiTx(minibuf, 2);
//            _esp_spi.spiRx(0, _metaData+i, 32);
//            _esp_spi.setCS(HIGH);
//        }
        // We have no errors ...
        _req_result = 0;
        // Notify end of execution
        _execute = false;
        _caller_cv.notify_one();
    } while (true);
}


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
