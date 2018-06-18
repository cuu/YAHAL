/*
 * spi_io.cpp
 *
 *  Created on: 17.06.2018
 *      Author: student
 */

#include "diskio.h"
#include "gpio_msp432.h"
#include "spi_msp432.h"

#define CAP_VER2_00  (1<<0)
#define CAP_SDHC     (1<<1)

int initialized = 0;
int sectors;
int erase_sectors;
int capabilities;
uint32_t hcs;

gpio_msp432_pin sd_cs (PORT_PIN(10, 0));
spi_msp432      spi_sd(EUSCI_B3_SPI, sd_cs);

/////////////////
// CRC helpers //
/////////////////
uint8_t crc7_one(uint8_t t, uint8_t data)
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

uint8_t crc7(const uint8_t *p, int len)
{
    int j;
    uint8_t crc = 0;
    for (j=0; j<len; j++)
        crc = crc7_one(crc, p[j]);
    return crc>>1;
}

uint16_t crc16_ccitt(uint16_t crc, uint8_t ser_data)
{
    crc  = (uint8_t)(crc >> 8) | (crc << 8);
    crc ^= ser_data;
    crc ^= (uint8_t)(crc & 0xff) >> 4;
    crc ^= (crc << 8) << 4;
    crc ^= ((crc & 0xff) << 4) << 1;
    return crc;
}

uint16_t crc16(const uint8_t *p, int len)
{
    int i;
    uint16_t crc = 0;
    for (i=0; i<len; i++)
        crc = crc16_ccitt(crc, p[i]);
    return crc;
}


uint8_t spi_txrx(uint8_t data)
{
    uint8_t out = 0;
    spi_sd.spiTxRx(&data, &out, 1);
    return out;
}


void sd_cmd(uint8_t cmd, uint32_t arg)
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
    //spi_txrx(0x95);
    spi_txrx(crc | 0x1);    /* crc7, for cmd0 */
}

uint8_t sd_get_r1()
{
    int tries = 1000;
    uint8_t r;

    while (tries--) {
        r = spi_txrx(0xff);
        if ((r & 0x80) == 0)
            return r;
    }
    return 0xff;
}

uint16_t sd_get_r2()
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

// r1, then 32-bit reply... same format as r3
uint8_t sd_get_r7(uint32_t *r7)
{
    uint32_t r;
    r = sd_get_r1();
    if (r != 0x01)
        return r;
    r  = spi_txrx(0xff) << 24;
    r |= spi_txrx(0xff) << 16;
    r |= spi_txrx(0xff) << 8;
    r |= spi_txrx(0xff);
    *r7 = r;
    return 0x01;
}


static void sd_nec()
{
    int i;
    for (i=0; i<8; i++)
        spi_txrx(0xff);
}

int sd_init()
{
    int i;
    int r;
    uint32_t r7;
    uint32_t r3;
    int tries;

    capabilities = 0;

    // start with 400 kHz clock
    spi_sd.setSpeed(400000);
    spi_sd.setCS(HIGH);
    // TODO: We have to set MOSI also to HIGH ...
    // 74+ clocks with CS high
    for (i=0; i<10; i++)
        spi_txrx(0xff);

    // SD card reset
    spi_sd.setCS(LOW);
    sd_cmd(0, 0);
    r = sd_get_r1();
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r == 0xff)
        goto err_spi;
    if (r != 0x01) { // we expect IDLE flag ...
        goto err;
    }

    // ask about voltage supply
    spi_sd.setCS(LOW);
    sd_cmd(8, 0x1aa /* VHS = 1 */);
    r = sd_get_r7(&r7);
    sd_nec();
    spi_sd.setCS(HIGH);
    capabilities |= CAP_VER2_00;
    if (r == 0xff)
        goto err_spi;
    if (r == 0x01) {
    }
    else if (r & 0x4) {
        capabilities &= ~CAP_VER2_00;
    } else {
        return -2;
    }


    // ask about voltage supply
    spi_sd.setCS(LOW);
    sd_cmd(58, 0);
    r = sd_get_r7(&r3);
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r == 0xff)
        goto err_spi;
    if (r != 0x01 && !(r & 0x4)) { /* allow it to not be implemented - old cards */
        return -2;
    }
    else {
        int i;
        for (i=4; i<=23; i++)
            if (r3 & 1<<i)
                break;
        for (i=23; i>=4; i--)
            if (r3 & 1<<i)
                break;
        /* CCS shouldn't be valid here yet */
    }


    tries = 1000;
    hcs = 0;
    /* say we support SDHC */
    if (capabilities & CAP_VER2_00)
        hcs = 1<<30;

    // needs to be polled until in_idle_state becomes 0
    do {
        // send we don't support SDHC
        spi_sd.setCS(LOW);
        // next cmd is ACMD
        sd_cmd(55, 0);
        r = sd_get_r1();
        sd_nec();
        spi_sd.setCS(HIGH);
        if (r == 0xff)
            goto err_spi;
        // well... it's probably not idle here, but specs aren't clear
        if (r & 0xfe) {
            goto err;
        }

        spi_sd.setCS(LOW);
        sd_cmd(41, hcs);
        r = sd_get_r1();
        sd_nec();
        spi_sd.setCS(HIGH);
        if (r == 0xff)
            goto err_spi;
        if (r & 0xfe) {
            goto err;
        }
    } while (r != 0 && tries--);
    if (tries == -1) {
        goto err;
    }

    // Seems after this card is initialized which means bit 0 of R1
    // will be cleared. Not too sure.


    if (capabilities & CAP_VER2_00) {
        // ask about voltage supply
        spi_sd.setCS(LOW);
        sd_cmd(58, 0);
        r = sd_get_r7(&r3);
        sd_nec();
        spi_sd.setCS(HIGH);
        if (r == 0xff)
            goto err_spi;
        if (r & 0xfe) {
            return -2;
        }
        else {
#if 1
            int i;
            for (i=4; i<=23; i++)
                if (r3 & 1<<i)
                    break;
            for (i=23; i>=4; i--)
                if (r3 & 1<<i)
                    break;
            /* CCS shouldn't be valid here yet */
            // XXX power up status should be 1 here, since we're finished initializing, but it's not. WHY?
            // that means CCS is invalid, so we'll set CAP_SDHC later
#endif
            if (r3>>30 & 1) {
                capabilities |= CAP_SDHC;
            }
        }
    }

    // with SDHC block length is fixed to 1024
    if ((capabilities & CAP_SDHC) == 0) {
        spi_sd.setCS(LOW);
        sd_cmd(16, 512);
        r = sd_get_r1();
        sd_nec();
        spi_sd.setCS(HIGH);
        if (r == 0xff)
            goto err_spi;
        if (r & 0xfe) {
            goto err;
        }
    }

    // set CRC on
    spi_sd.setCS(LOW);
    sd_cmd(59, 0);
    r = sd_get_r1();
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r == 0xff)
        goto err_spi;
    if (r & 0xfe) {
        goto err;
    }

    // set speed to 24MHz
    spi_sd.setSpeed(24000000);

    return 0;

 err_spi:
    return -1;

 err:
    return -2;
}

int sd_read_status()
{
    uint16_t r2;

    spi_sd.setCS(LOW);
    sd_cmd(13, 0);
    r2 = sd_get_r2();
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r2 & 0x8000)
        return -1;

    return 0;
}

// 0xfe marks data start, then len bytes of data and crc16
int sd_get_data(uint8_t *buf, int len)
{
    int tries = 20000;
    uint8_t r;
    uint16_t _crc16;
    uint16_t calc_crc;
//    int i;

    while (tries--) {
        r = spi_txrx(0xff);
        if (r == 0xfe)
            break;
    }
    if (tries < 0)
        return -1;

    spi_sd.spiRx(0xff, buf, len);

    _crc16  = spi_txrx(0xff) << 8;
    _crc16 |= spi_txrx(0xff);

    calc_crc = crc16(buf, len);
    if (_crc16 != calc_crc) {
        return -1;
    }

    return 0;
}


int sd_put_data(const uint8_t *buf, int len)
{
    uint8_t r;
    int tries = 10;
    uint8_t b[16];
    int bi = 0;
    uint16_t crc;

    (void)b;
    spi_txrx(0xfe); // data start

    spi_sd.spiTx(buf, len);

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

static int sd_read_csd()
{
    uint8_t buf[16];
    int r;
    int capacity;

    spi_sd.setCS(LOW);
    sd_cmd(9, 0);
    r = sd_get_r1();
    if (r == 0xff) {
        spi_sd.setCS(HIGH);
        return -1;
    }
    if (r & 0xfe) {
        spi_sd.setCS(HIGH);
        return -2;
    }

    r = sd_get_data(buf, 16);
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r == -1) {
        return -3;
    }

    if ((buf[0] >> 6) + 1 == 1) {
    /* CSD v1 */
//    printf("CSD: CSD v%i taac:%02x, nsac:%i, tran:%02x, classes:%02x%x, read_bl_len:%i, "
//        "read_bl_part:%i, write_blk_misalign:%i, read_blk_misalign:%i, dsr_imp:%i, "
//        "c_size:%i, vdd_rmin:%i, vdd_rmax:%i, vdd_wmin:%i, vdd_wmax:%i, "
//        "c_size_mult:%i, erase_blk_en:%i, erase_s_size:%i, "
//        "wp_grp_size:%i, wp_grp_enable:%i, r2w_factor:%i, write_bl_len:%i, write_bl_part:%i, "
//        "filef_gpr:%i, copy:%i, perm_wr_prot:%i, tmp_wr_prot:%i, filef:%i\n",
//            (buf[0] >> 6) + 1,
//            buf[1], buf[2], buf[3],
//            buf[4], buf[5] >> 4, 1<<(buf[5] & 0xf), /* classes, read_bl_len */
//            buf[6]>>7, (buf[6]>>6)&1, (buf[6]>>5)&1, (buf[6]>>4)&1,
//            (buf[6]&0x3)<<10 | buf[7]<<2 | buf[8]>>6, /* c_size */
//            (buf[8]&0x38)>>3, buf[8]&0x07, buf[9]>>5, (buf[9]>>2)&0x7,
//            1<<(2+(((buf[9]&3) << 1) | buf[10]>>7)), /* c_size_mult */
//            (buf[10]>>6)&1,
//            ((buf[10]&0x3f)<<1 | buf[11]>>7) + 1, /* erase sector size */
//            (buf[11]&0x7f) + 1, /* write protect group size */
//            buf[12]>>7, 1<<((buf[12]>>2)&7),
//            1<<((buf[12]&3)<<2 | buf[13]>>6), /* write_bl_len */
//            (buf[13]>>5)&1,
//            buf[14]>>7, (buf[14]>>6)&1, (buf[14]>>5)&1, (buf[14]>>4)&1,
//            (buf[14]>>2)&3 /* file format */);

    capacity = (((buf[6]&0x3)<<10 | buf[7]<<2 | buf[8]>>6)+1) << (2+(((buf[9]&3) << 1) | buf[10]>>7)) << ((buf[5] & 0xf) - 9);
    /* ^ = (c_size+1) * 2**(c_size_mult+2) * 2**(read_bl_len-9) */

    } else {
    /* CSD v2 */
        /* this means the card is HC */
        capabilities |= CAP_SDHC;

//    printf("CSD: CSD v%i taac:%02x, nsac:%i, tran:%02x, classes:%02x%x, read_bl_len:%i, "
//        "read_bl_part:%i, write_blk_misalign:%i, read_blk_misalign:%i, dsr_imp:%i, "
//        "c_size:%i, erase_blk_en:%i, erase_s_size:%i, "
//        "wp_grp_size:%i, wp_grp_enable:%i, r2w_factor:%i, write_bl_len:%i, write_bl_part:%i, "
//        "filef_gpr:%i, copy:%i, perm_wr_prot:%i, tmp_wr_prot:%i, filef:%i\n",
//            (buf[0] >> 6) + 1,
//            buf[1], buf[2], buf[3],
//            buf[4], buf[5] >> 4, 1<<(buf[5] & 0xf), /* classes, read_bl_len */
//            buf[6]>>7, (buf[6]>>6)&1, (buf[6]>>5)&1, (buf[6]>>4)&1,
//            buf[7]<<16 | buf[8]<<8 | buf[9], /* c_size */
//            (buf[10]>>6)&1,
//            ((buf[10]&0x3f)<<1 | buf[11]>>7) + 1, /* erase sector size */
//            (buf[11]&0x7f) + 1, /* write protect group size */
//            buf[12]>>7, 1<<((buf[12]>>2)&7),
//            1<<((buf[12]&3)<<2 | buf[13]>>6), /* write_bl_len */
//            (buf[13]>>5)&1,
//            buf[14]>>7, (buf[14]>>6)&1, (buf[14]>>5)&1, (buf[14]>>4)&1,
//            (buf[14]>>2)&3 /* file format */);

    capacity = buf[7]<<16 | buf[8]<<8 | buf[9]; /* in 512 kB */
    capacity *= 1024; /* in 512 B sectors */

    }

    sectors = capacity;

    /* if erase_blk_en = 0, then only this many sectors can be erased at once
     * this is NOT yet tested */
    erase_sectors = 1;
    if (((buf[10]>>6)&1) == 0)
        erase_sectors = ((buf[10]&0x3f)<<1 | buf[11]>>7) + 1;

    return 0;
}

static int sd_read_cid()
{
    uint8_t buf[16];
    int r;

    spi_sd.setCS(LOW);
    sd_cmd(10, 0);
    r = sd_get_r1();
    if (r == 0xff) {
        spi_sd.setCS(HIGH);
        return -1;
    }
    if (r & 0xfe) {
        spi_sd.setCS(HIGH);
        return -2;
    }

    r = sd_get_data(buf, 16);
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r == -1) {
        return -3;
    }

//    printf("CID: mid:%x, oid:%c%c, pnm:%c%c%c%c%c, prv:%i.%i, psn:%02x%02x%02x%02x, mdt:%i/%i\n",
//            buf[0], buf[1], buf[2],         /* mid, oid */
//            buf[3], buf[4], buf[5], buf[6], buf[7], /* pnm */
//            buf[8] >> 4, buf[8] & 0xf,      /* prv */
//            buf[9], buf[10], buf[11], buf[12],  /* psn */
//            2000 + (buf[13]<<4 | buf[14]>>4), 1 + (buf[14] & 0xf));

    return 0;
}





int sd_readsector(uint32_t address, uint8_t *buf)
{
    int r;

    spi_sd.setCS(LOW);
    if (capabilities & CAP_SDHC)
        sd_cmd(17, address); /* read single block */
    else
        sd_cmd(17, address*512); /* read single block */

    r = sd_get_r1();
    if (r == 0xff) {
        spi_sd.setCS(HIGH);
        r = -1;
        goto fail;
    }
    if (r & 0xfe) {
        spi_sd.setCS(HIGH);
        r = -2;
        goto fail;
    }

    r = sd_get_data(buf, 512);
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r == -1) {
        r = -3;
        goto fail;
    }

    return 0;
 fail:
    return r;
}

int sd_writesector(uint32_t address, const uint8_t *buf)
{
    int r;

    spi_sd.setCS(LOW);
    if (capabilities & CAP_SDHC)
        sd_cmd(24, address); /* write block */
    else
        sd_cmd(24, address*512); /* write block */

    r = sd_get_r1();
    if (r == 0xff) {
        spi_sd.setCS(HIGH);
        r = -1;
        goto fail;
    }
    if (r & 0xfe) {
        spi_sd.setCS(HIGH);
        r = -2;
        goto fail;
    }

    spi_txrx(0xff); /* Nwr (>= 1) high bytes */
    r = sd_put_data(buf, 512);
    sd_nec();
    spi_sd.setCS(HIGH);
    if (r != 0) {
        r = -3;
        goto fail;
    }

    /* efsl code is weird shit, 0 is error in there?
     * not that it's properly handled or anything,
     * and the return type is char, fucking efsl */
    return 0;
 fail:
    return r;
}


int hwif_init()
{
    int tries = 10;

    if (initialized)
        return 0;

//    spi_init();

    while (tries--) {
        if (sd_init() == 0)
            break;
    }
    if (tries == -1)
        return -1;

    /* read status register */
    sd_read_status();

    sd_read_cid();
    if (sd_read_csd() != 0)
        return -1;

    initialized = 1;
    return 0;
}

int sd_read(uint32_t address, uint8_t *buf)
{
    int r;
    int tries = 10;

    r = sd_readsector(address, buf);

    while (r < 0 && tries--) {
        if (sd_init() != 0)
            continue;

        /* read status register */
        sd_read_status();

        r = sd_readsector(address, buf);
    }
    if (tries == -1) {
    }
    return r;
}

int sd_write(uint32_t address,const uint8_t *buf)
{
    int r;
    int tries = 10;

    r = sd_writesector(address, buf);

    while (r < 0 && tries--) {
        if (sd_init() != 0)
            continue;

        /* read status register */
        sd_read_status();

        r = sd_writesector(address, buf);
    }
    if (tries == -1) {
    }
    return r;
}

extern "C" {

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv       /* Physical drive nmuber to identify the drive */
)
{
    (void)pdrv;
    if (initialized)
        return 0;

    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv               /* Physical drive nmuber to identify the drive */
)
{
    (void)pdrv;
    if (hwif_init() == 0)
        return 0;

    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,      /* Physical drive nmuber to identify the drive */
    BYTE *buff,     /* Data buffer to store read data */
    DWORD sector,   /* Sector address in LBA */
    UINT count      /* Number of sectors to read */
)
{
    (void)pdrv;

    for (UINT i=0; i<count; i++)
        if (sd_read(sector+i, buff+512*i) != 0)
            return RES_ERROR;

    return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
    BYTE pdrv,          /* Physical drive nmuber to identify the drive */
    const BYTE *buff,   /* Data to be written */
    DWORD sector,       /* Sector address in LBA */
    UINT count          /* Number of sectors to write */
)
{
    (void)pdrv;

    for (UINT i=0; i<count; i++)
        if (sd_write(sector+i, buff+512*i) != 0)
            return RES_ERROR;

    return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,      /* Physical drive nmuber (0..) */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
    (void)pdrv;
    switch (cmd) {
    case CTRL_SYNC:
        return RES_OK;
    case GET_SECTOR_SIZE:
        *(WORD*)buff = 512;
        return RES_OK;
    case GET_SECTOR_COUNT:
        *(DWORD*)buff = sectors;
        return RES_OK;
    case GET_BLOCK_SIZE:
        *(DWORD*)buff = erase_sectors;
        return RES_OK;
    }
    return RES_PARERR;
}


/*
 * FAT filestamp format:
 * [31:25] - year - 1980
 * [24:21] - month 1..12
 * [20:16] - day 1..31
 * [15:11] - hour 0..23
 * [10:5]  - minute 0..59
 * [4:0]   - second/2 0..29
 * so... midnight 2009 is 0x3a000000
 */
DWORD get_fattime()
{
    int time = 300;
    int y = 2016, m = 4, d = 4;
    time %= 86400;
    return (y-1980)<<25 | m<<21 | d<<16 |
        (time/3600)<<11 | (time/60%60)<<5 | (time/2%30);
}


}


