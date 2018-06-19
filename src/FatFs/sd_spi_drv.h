
#ifndef _SD_SPI_DRV_H_
#define _SD_SPI_DRV_H_

#include "block_io_interface.h"
#include "spi_interface.h"

class sd_spi_drv : public block_io_interface
{
public:
    sd_spi_drv(spi_interface & spi);

    blockio_status_t initialize() override;
    blockio_status_t status() override;

    blockio_result_t readBlock (uint8_t* buff, uint32_t block, uint16_t count) override;
    blockio_result_t writeBlock(const uint8_t* buff, uint32_t block, uint16_t count) override;

    uint32_t getBlockCount() override;

    // We do not use buffers, so there is nothing to sync...
    inline void sync() override { }

private:

    spi_interface & _spi;
    bool            _initialized;
    bool            _isV200;
    bool            _isSDHC;
    uint32_t        _blockCount;

    uint16_t        _sd_status;
    uint8_t         _cid[16];
    uint8_t         _csd[16];

    int sd_init();
    int sd_read_status();
    int sd_read_cid();
    int sd_read_csd();

    // Send Command command to SD card with argument
    void     sd_cmd(uint8_t cmd, uint32_t arg);
    uint8_t  sd_get_r1();
    uint16_t sd_get_r2();
    uint8_t  sd_get_r37(uint32_t *r7);
    int      sd_get_data(uint8_t *buf, int len);
    int      sd_put_data(const uint8_t *buf, int len);

    void sd_nec();

    // Transmit a single byte and return the received byte
    uint8_t spi_txrx(uint8_t data);

    uint8_t  crc7_one(uint8_t t, uint8_t data);
    uint16_t crc16(const uint8_t *p, int len);
    uint16_t crc16_ccitt(uint16_t crc, uint8_t ser_data);

    int sd_readsector (uint32_t address, uint8_t *buf);
    int sd_writesector(uint32_t address, const uint8_t *buf);
};

#endif // _SD_SPI_DRV_H_
