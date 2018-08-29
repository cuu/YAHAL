
#include "sd_spi_drv.h"
#include "gpio_interface.h" // for LOW/HIGH

sd_spi_drv::sd_spi_drv(spi_interface & spi) :
    _spi(spi), _initialized(false), _isV200(false),
    _isSDHC(false), _blockCount(0), _sd_status(0) { }

blockio_status_t sd_spi_drv::initialize() {
    // Check is device was successfully
    // been initialized before
    if (_initialized) return 0;

    // Try to initialize the SD card
    bool sd_init_ok = false;
    for (int tries = 0; tries < 10; ++tries) {
        int r = sd_init();
        if (r == 0) {
            sd_init_ok = true;
            break;
        }
    }
    if (!sd_init_ok)
        return BLOCKIO::NOINIT;

    // read various registers
    if (sd_read_status()) return BLOCKIO::NOINIT;
    if (sd_read_cid())    return BLOCKIO::NOINIT;
    if (sd_read_csd())    return BLOCKIO::NOINIT;

    _initialized = true;
    return 0;
}

blockio_status_t sd_spi_drv::status() {
    if (!_initialized) {
        return BLOCKIO::NOINIT;
    } else {
        return 0;
    }
}

BLOCKIO::result_t sd_spi_drv::readBlock (uint8_t* buff, uint32_t block, uint16_t count) {
    if (!_initialized) initialize();

    for (int i=0; i < count; ++i) {
        int r = sd_readsector(block+i, buff+512*i);
        if (r) return BLOCKIO::ERROR;
    }
    return BLOCKIO::OK;
}

BLOCKIO::result_t sd_spi_drv::writeBlock(const uint8_t* buff, uint32_t block, uint16_t count) {
    if (!_initialized) initialize();

    for (int i=0; i < count; ++i) {
        int r = sd_writesector(block+i, buff+512*i);
        if (r) return BLOCKIO::ERROR;
    }
    return BLOCKIO::OK;
}


uint32_t sd_spi_drv::getBlockCount() {
    if (!_initialized) initialize();
    return _blockCount;
}

/////////////////////////////////////

int sd_spi_drv::sd_init()
{
    int tries;
    uint8_t  r;
    uint32_t r3, r7;

    // Set up SPI interface
    _spi.generateCS(false);
    _spi.setCS(HIGH);

    // Start with a slow SPI clock
    _spi.setSpeed(400000);

    // 74+ clocks with CS high
    for (int i=0; i < 10; i++)
        spi_txrx(0xff);

    // CMD0 (Reset)
    _spi.setCS(LOW);
    sd_cmd(0, 0);
    r = sd_get_r1();
    sd_nec();
    _spi.setCS(HIGH);
    if (r == 0xff) return -1; // SPI error
    if (r != 0x01) return -2; // protocol error

    // CMD8 (supply voltage)
    _spi.setCS(LOW);
    sd_cmd(8, 0x1aa); // 2.7-3.6V okay?
    r = sd_get_r37(&r7);
    sd_nec();
    _spi.setCS(HIGH);
    if (r == 0xff) return -1; // SPI error
    if (r &  0xfa) return -2; // protocol error
    if (r == 0x01) _isV200 = true;

    // CMD58 (read OCR) (bits 30/31 maybe NOT available here!!)
    _spi.setCS(LOW);
    sd_cmd(58, 0);
    r = sd_get_r37(&r3);
    sd_nec();
    _spi.setCS(HIGH);
    if (r == 0xff) return -1; // SPI error
    if (r &  0xfe) return -2; // protocol error

    for (tries=100; tries > 0; --tries) {
        // CMD55 (next is application command ACMD)
        _spi.setCS(LOW);
        sd_cmd(55, 0);
        r = sd_get_r1();
        sd_nec();
        _spi.setCS(HIGH);
        if (r == 0xff) return -1; // SPI error
        if (r  & 0xfe) return -2; // protocol error

        // ACMD41 (activate initialization)
        _spi.setCS(LOW);
        // Try both versions!
        r3 = (tries > 50) ? 0x40000000 : 0;
        sd_cmd(41, r3);
        r = sd_get_r1();
        sd_nec();
        _spi.setCS(HIGH);
        if (r == 0xff) return -1; // SPI error
        if (r &  0xfe) return -2; // protocol error
        if (r == 0) break;
    }
    if (tries == 0) return -2; // protocol error

    if (_isV200) {
        // CMD58 (read OCR)
        _spi.setCS(LOW);
        sd_cmd(58, 0);
        r = sd_get_r37(&r3);
        sd_nec();
        _spi.setCS(HIGH);
        if (r == 0xff) return -1; // SPI error
        if (r &  0xfe) return -2; // protocol error
        _isSDHC = r3 & 0x40000000;
    }

    // CMD16 (Set block length)
    // SDHC has fixed block length of 512 bytes,
    // but non-SDHC cards might have other length...
    if (!_isSDHC) {
        _spi.setCS(LOW);
        sd_cmd(16, 512);
        r = sd_get_r1();
        sd_nec();
        _spi.setCS(HIGH);
        if (r == 0xff) return -1; // SPI error
        if (r & 0xfe)  return -2; // protocol error
    }

    // CMD59 (CRC on/off)
    _spi.setCS(LOW);
    sd_cmd(59, 0);
    r = sd_get_r1();
    sd_nec();
    _spi.setCS(HIGH);
    if (r == 0xff) return -1; // SPI error
    if (r & 0xfe)  return -2; // protocol error

    // set speed to 24MHz
    _spi.setSpeed(24000000);
    return 0;
}

int sd_spi_drv::sd_read_status()
{
    // CMD13 (read status)
    _spi.setCS(LOW);
    sd_cmd(13, 0);
    uint16_t r2 = sd_get_r2();
    sd_nec();
    _spi.setCS(HIGH);

    _sd_status = r2;
    if (r2 & 0x8000)
        return -1;

    return 0;
}


 int sd_spi_drv::sd_read_cid()
{
    // CMD10 (send CID)
    _spi.setCS(LOW);
    sd_cmd(10, 0);
    int r = sd_get_r1();
    if (r == 0xff) {
        _spi.setCS(HIGH);
        return -1; // SPI error
    }
    if (r & 0xfe) {
        _spi.setCS(HIGH);
        return -2; // protocol error
    }
    r = sd_get_data(_cid, 16);
    sd_nec();
    _spi.setCS(HIGH);

    return r;
}


int sd_spi_drv::sd_read_csd()
{
    int r;

    // CMD9 (send CSD)
    _spi.setCS(LOW);
    sd_cmd(9, 0);
    r = sd_get_r1();
    if (r == 0xff) {
        _spi.setCS(HIGH);
        return -1; // SPI error
    }
    if (r & 0xfe) {
        _spi.setCS(HIGH);
        return -2; // protocol error
    }
    r = sd_get_data(_csd, 16);
    sd_nec();
    _spi.setCS(HIGH);

    if (r) return r;

    if ((_csd[0] & 0xc0) == 0) {
        // CSD v1 or V2 standard capacity
        uint32_t c_size  = (((_csd[6] & 3) << 10) | (_csd[7]  << 2) | (_csd[8]  >> 6));
        uint32_t c_mult  =  ((_csd[9] & 3) << 1)  | (_csd[10] >> 7);
        uint32_t blk_len =   (_csd[5] & 0xf);
        _blockCount = (c_size+1) * (1 << (c_mult + blk_len - 7));
    } else {
        // CSD V2 high capacity (HC)
        uint32_t c_size = (_csd[7]<<16) | (_csd[8]<<8) | _csd[9]; // in 512 kB
        _blockCount = c_size *1024;
    }
    return 0;
}

void sd_spi_drv::sd_cmd(uint8_t cmd, uint32_t arg)
{
    uint8_t crc = 0;
    spi_txrx(0x40 | cmd);
    crc = crc7_one(crc, 0x40 | cmd);
    spi_txrx(arg >> 24);
    crc = crc7_one(crc, arg >> 24);
    spi_txrx(arg >> 16);
    crc = crc7_one(crc, arg >> 16);
    spi_txrx(arg >> 8);
    crc = crc7_one(crc, arg >> 8);
    spi_txrx(arg);
    crc = crc7_one(crc, arg);
    spi_txrx(crc | 0x1);
}

uint8_t sd_spi_drv::sd_get_r1()
{
    for (int tries=0; tries < 1000; ++tries) {
        uint8_t r = spi_txrx(0xff);
        if ((r & 0x80) == 0)
            return r;
    }
    return 0xff;
}

uint16_t sd_spi_drv::sd_get_r2()
{
    int tries = 1000;
    uint16_t r;
    while (tries--) {
        r = spi_txrx(0xff);
        if ((r & 0x80) == 0)
            break;
    }
    if (tries < 0)
        return 0xff;
    r = r<<8 | spi_txrx(0xff);
    return r;
}

uint8_t sd_spi_drv::sd_get_r37(uint32_t *r37) {
    uint32_t r;
    r = sd_get_r1();
    if (r != 0x01)
        return r;
    r  = spi_txrx(0xff) << 24;
    r |= spi_txrx(0xff) << 16;
    r |= spi_txrx(0xff) << 8;
    r |= spi_txrx(0xff);
    *r37 = r;
    return 0x01;
}

int sd_spi_drv::sd_get_data(uint8_t *buf, int len)
{
    int tries = 20000;
    uint8_t r;
    uint16_t _crc16;
    uint16_t calc_crc;

    // Wait for data to start (0xfe)
    while (tries--) {
        r = spi_txrx(0xff);
        if (r == 0xfe)
            break;
    }
    if (tries < 0)
        return -4; // no data

    _spi.spiRx(0xff, buf, len);

    _crc16  = spi_txrx(0xff) << 8;
    _crc16 |= spi_txrx(0xff);

    calc_crc = crc16(buf, len);
    if (_crc16 != calc_crc) {
        return -5; // wrong CRC
    }
    return 0;
}

int sd_spi_drv::sd_put_data(const uint8_t *buf, int len)
{
    uint8_t r;
    int tries = 10;
    uint8_t b[16];
    int bi = 0;
    uint16_t crc;

    (void)b;
    spi_txrx(0xfe); // data start

    _spi.spiTx(buf, len);

    crc = crc16(buf, len);
    // crc16
    spi_txrx(crc>>8);
    spi_txrx(crc);

    // normally just one dummy read in between... specs don't say how many
    while (tries--) {
        b[bi++] = r = spi_txrx(0xff);
        if (r != 0xff)
            break;
    }
    if (tries < 0)
        return -1;

    // poll busy, about 300 reads for 256 MB card
    tries = 100000;
    while (tries--) {
        if (spi_txrx(0xff) == 0xff)
            break;
    }
    if (tries < 0)
        return -2;

    // data accepted, WIN
    if ((r & 0x1f) == 0x05)
        return 0;

    return r;
}

void sd_spi_drv::sd_nec()
{
    for (int i=0; i<8; i++)
        spi_txrx(0xff);
}

uint8_t sd_spi_drv::spi_txrx(uint8_t data)
{
    uint8_t out = 0;
    _spi.spiTxRx(&data, &out, 1);
    return out;
}

// CRC helper methods

uint8_t sd_spi_drv::crc7_one(uint8_t t, uint8_t data)
{
    int i;
    const uint8_t g = 0x89;
    t ^= data;
    for (i=0; i<8; i++) {
        if (t & 0x80)
            t ^= g;
        t <<= 1;
    }
    return t;
}

uint16_t sd_spi_drv::crc16(const uint8_t *p, int len)
{
    int i;
    uint16_t crc = 0;
    for (i=0; i<len; i++)
        crc = crc16_ccitt(crc, p[i]);
    return crc;
}

uint16_t sd_spi_drv::crc16_ccitt(uint16_t crc, uint8_t ser_data)
{
    crc  = (uint8_t)(crc >> 8) | (crc << 8);
    crc ^= ser_data;
    crc ^= (uint8_t)(crc & 0xff) >> 4;
    crc ^= (crc << 8) << 4;
    crc ^= ((crc & 0xff) << 4) << 1;
    return crc;
}

int sd_spi_drv::sd_readsector(uint32_t sector, uint8_t *buf)
{
    int r;
    // CMD17 (read single block)
    _spi.setCS(LOW);
    if (_isSDHC) sd_cmd(17, sector);
    else         sd_cmd(17, sector * 512);

    r = sd_get_r1();
    if (r == 0xff) {
        _spi.setCS(HIGH);
        return -1; // SPI error
    }
    if (r & 0xfe) {
        _spi.setCS(HIGH);
        return -2; // protocol error
    }
    r = sd_get_data(buf, 512);
    sd_nec();
    _spi.setCS(HIGH);
    return r;
}

int sd_spi_drv::sd_writesector(uint32_t sector, const uint8_t *buf)
{
    // CMD24 (write single block)
    _spi.setCS(LOW);
    if (_isSDHC) sd_cmd(24, sector);
    else         sd_cmd(24, sector * 512);

    uint8_t r = sd_get_r1();
    if (r == 0xff) {
        _spi.setCS(HIGH);
        return -1; // SPI error
    }
    if (r & 0xfe) {
        _spi.setCS(HIGH);
        return -2; // protocol error
    }

    spi_txrx(0xff); // Nwr (>= 1) high bytes
    r = sd_put_data(buf, 512);
    sd_nec();
    _spi.setCS(HIGH);
    return r;
}
