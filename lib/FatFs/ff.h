/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem module  R0.13b                              /
/-----------------------------------------------------------------------------/
/
/ Copyright (C) 2018, ChaN, all right reserved.
/
/ FatFs module is an open source software. Redistribution and use of FatFs in
/ source and binary forms, with or without modification, are permitted provided
/ that the following condition is met:
/
/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/
/----------------------------------------------------------------------------*/

#ifndef FF_DEFINED
#define FF_DEFINED  63463   // Revision ID

#include "stdint.h"         // Standard integer types
#include "ffconf.h"         // FatFs configuration options
#include "block_io_interface.h"
#include "posix_io_interface.h"

#if FF_DEFINED != FFCONF_DEF
#error Wrong configuration file (ffconf.h).
#endif

#ifndef EOF
#define EOF (-1)
#endif

/* File access mode and open method flags (3rd argument of f_open) */
#define FA_READ             0x01
#define FA_WRITE            0x02
#define FA_OPEN_EXISTING    0x00
#define FA_CREATE_NEW       0x04
#define FA_CREATE_ALWAYS    0x08
#define FA_OPEN_ALWAYS      0x10
#define FA_OPEN_APPEND      0x30

/* Fast seek controls (2nd argument of f_lseek) */
#define CREATE_LINKMAP  ((FSIZE_t)0 - 1)

/* Format options (2nd argument of f_mkfs) */
#define FM_FAT      0x01
#define FM_FAT32    0x02
#define FM_EXFAT    0x04
#define FM_ANY      0x07
#define FM_SFD      0x08

/* Filesystem type (fs_type) */
#define FS_FAT12    1
#define FS_FAT16    2
#define FS_FAT32    3
#define FS_EXFAT    4

/* File attribute bits for directory entry (FILEINFO.fattrib) */
#define AM_RDO  0x01    /* Read only */
#define AM_HID  0x02    /* Hidden */
#define AM_SYS  0x04    /* System */
#define AM_DIR  0x10    /* Directory */
#define AM_ARC  0x20    /* Archive */


typedef uint16_t WCHAR;

/* Type of path name strings on FatFs API */

#ifndef _INC_TCHAR
#define _INC_TCHAR

#if FF_USE_LFN && FF_LFN_UNICODE == 1 	/* Unicode in UTF-16 encoding */
typedef WCHAR TCHAR;
#define _T(x) L ## x
#define _TEXT(x) L ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 2	/* Unicode in UTF-8 encoding */
typedef char TCHAR;
#define _T(x) u8 ## x
#define _TEXT(x) u8 ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 3	/* Unicode in UTF-32 encoding */
typedef uint32_t TCHAR;
#define _T(x) U ## x
#define _TEXT(x) U ## x
#elif FF_USE_LFN && (FF_LFN_UNICODE < 0 || FF_LFN_UNICODE > 3)
#error Wrong FF_LFN_UNICODE setting
#else									/* ANSI/OEM code in SBCS/DBCS */
typedef char TCHAR;
#define _T(x) x
#define _TEXT(x) x
#endif

#endif

/* Type of file size variables */

#if FF_FS_EXFAT
typedef uint64_t FSIZE_t;
#else
typedef uint32_t FSIZE_t;
#endif

class FatFs : public posix_io_interface
{

public:

    /*-------------------------------------*/
    /* FatFs module public data structures */
    /*-------------------------------------*/

    /* Object ID and allocation information (FFOBJID) */

    typedef struct
    {
        FatFs*   fs;      /* Pointer to the hosting volume of this object */
        uint16_t id;      /* Hosting volume mount ID */
        uint8_t  attr;    /* Object attribute */
        uint8_t  stat;    /* Object chain status (b1-0: =0:not contiguous, =2:contiguous, =3:flagmented in this session, b2:sub-directory stretched) */
        uint32_t sclust;  /* Object data start cluster (0:no cluster or root directory) */
        FSIZE_t  objsize; /* Object size (valid when sclust != 0) */
#if FF_FS_EXFAT
        uint32_t n_cont;  /* Size of first fragment - 1 (valid when stat == 3) */
        uint32_t n_frag;  /* Size of last fragment needs to be written to FAT (valid when not zero) */
        uint32_t c_scl;   /* Containing directory start cluster (valid when sclust != 0) */
        uint32_t c_size;  /* b31-b8:Size of containing directory, b7-b0: Chain status (valid when c_scl != 0) */
        uint32_t c_ofs;   /* Offset in the containing directory (valid when file object and sclust != 0) */
#endif
#if FF_FS_LOCK
        uint16_t lockid;  /* File lock ID origin from 1 (index of file semaphore table Files[]) */
#endif
    } FFOBJID;

    /* File object structure (FILE) */

    typedef struct
    {
        FFOBJID  obj;     /* Object identifier (must be the 1st member to detect invalid object pointer) */
        uint8_t  flag;    /* File status flags */
        uint8_t  err;     /* Abort flag (error code) */
        FSIZE_t  fptr;    /* File read/write pointer (Zeroed on file open) */
        uint32_t clust;   /* Current cluster of fpter (invalid when fptr is 0) */
        uint32_t sect;    /* Sector number appearing in buf[] (0:invalid) */
#if !FF_FS_READONLY
        uint32_t dir_sect;/* Sector number containing the directory entry (not used at exFAT) */
        uint8_t* dir_ptr; /* Pointer to the directory entry in the win[] (not used at exFAT) */
#endif
#if FF_USE_FASTSEEK
        uint32_t* cltbl;  /* Pointer to the cluster link map table (nulled on open, set by application) */
#endif
#if !FF_FS_TINY
        uint8_t buf[FF_MAX_SS]; /* File private data read/write window */
#endif
    } FILE;

    /* Directory object structure (DIR) */

    typedef struct
    {
        FFOBJID  obj;     /* Object identifier */
        uint32_t dptr;    /* Current read/write offset */
        uint32_t clust;   /* Current cluster */
        uint32_t sect;    /* Current sector (0:Read operation has terminated) */
        uint8_t* dir;     /* Pointer to the directory item in the win[] */
        uint8_t  fn[12];  /* SFN (in/out) {body[8],ext[3],status[1]} */
#if FF_USE_LFN
        uint32_t blk_ofs; /* Offset of current entry block being processed (0xFFFFFFFF:Invalid) */
#endif
#if FF_USE_FIND
        const TCHAR* pat; /* Pointer to the name matching pattern */
#endif
    } DIR;

    /* File information structure (FILEINFO) */

    typedef struct
    {
        FSIZE_t  fsize;   /* File size */
        uint16_t fdate;   /* Modified date */
        uint16_t ftime;   /* Modified time */
        uint8_t  fattrib; /* File attribute */
#if FF_USE_LFN
        TCHAR altname[FF_SFN_BUF + 1]; /* Altenative file name */
        TCHAR fname  [FF_LFN_BUF + 1]; /* Primary file name */
#else
        TCHAR fname[12 + 1]; /* File name */
#endif
    } FILEINFO;

    /* File function return code (FRESULT) */

    typedef enum
    {
        FR_OK = 0,              /* (0) Succeeded */
        FR_DISK_ERR,            /* (1) A hard error occurred in the low level disk I/O layer */
        FR_INT_ERR,             /* (2) Assertion failed */
        FR_NOT_READY,           /* (3) The physical drive cannot work */
        FR_NO_FILE,             /* (4) Could not find the file */
        FR_NO_PATH,             /* (5) Could not find the path */
        FR_INVALID_NAME,        /* (6) The path name format is invalid */
        FR_DENIED,              /* (7) Access denied due to prohibited access or directory full */
        FR_EXIST,               /* (8) Access denied due to prohibited access */
        FR_INVALID_OBJECT,      /* (9) The file/directory object is invalid */
        FR_WRITE_PROTECTED,     /* (10) The physical drive is write protected */
        FR_INVALID_DRIVE,       /* (11) The logical drive number is invalid */
        FR_NOT_ENABLED,         /* (12) The volume has no work area */
        FR_NO_FILESYSTEM,       /* (13) There is no valid FAT volume */
        FR_MKFS_ABORTED,        /* (14) The f_mkfs() aborted due to any problem */
        FR_TIMEOUT,             /* (15) Could not get a grant to access the volume within defined period */
        FR_LOCKED,              /* (16) The operation is rejected according to the file sharing policy */
        FR_NOT_ENOUGH_CORE,     /* (17) LFN working buffer could not be allocated */
        FR_TOO_MANY_OPEN_FILES, /* (18) Number of open files > FF_FS_LOCK */
        FR_INVALID_PARAMETER    /* (19) Given parameter is invalid */
    } FRESULT;

public:

    /*--------------------------------------------------------------*/
    /* FatFs module public application interface                    */
    /*--------------------------------------------------------------*/

    FatFs(block_io_interface & io);

    FRESULT open     (FILE* fp, const TCHAR* path, uint8_t mode); /* Open or create a file */
    FRESULT close    (FILE* fp); /* Close an open file object */
    FRESULT read     (FILE* fp, void* buff, uint16_t btr, uint16_t* br); /* Read data from the file */
    FRESULT write    (FILE* fp, const void* buff, uint16_t btw, uint16_t* bw); /* Write data to the file */
    FRESULT lseek    (FILE* fp, FSIZE_t ofs); /* Move file pointer of the file object */
    FRESULT truncate (FILE* fp); /* Truncate the file */
    FRESULT sync     (FILE* fp); /* Flush cached data of the writing file */
    FRESULT opendir  (DIR* dp, const TCHAR* path); /* Open a directory */
    FRESULT closedir (DIR* dp); /* Close an open directory */
    FRESULT readdir  (DIR* dp, FILEINFO* fno); /* Read a directory item */
    FRESULT findfirst(DIR* dp, FILEINFO* fno, const TCHAR* path, const TCHAR* pattern); /* Find first file */
    FRESULT findnext (DIR* dp, FILEINFO* fno); /* Find next file */
    FRESULT mkdir    (const TCHAR* path); /* Create a sub directory */
    FRESULT unlink   (const TCHAR* path); /* Delete an existing file or directory */
    FRESULT rename   (const TCHAR* path_old, const TCHAR* path_new); /* Rename/Move a file or directory */
    FRESULT stat     (const TCHAR* path, FILEINFO* fno); /* Get file status */
    FRESULT chmod    (const TCHAR* path, uint8_t attr, uint8_t mask); /* Change attribute of a file/dir */
    FRESULT utime    (const TCHAR* path, const FILEINFO* fno); /* Change timestamp of a file/dir */
    FRESULT chdir    (const TCHAR* path); /* Change current directory */
    FRESULT getcwd   (TCHAR* buff, uint16_t len); /* Get current directory */
    FRESULT getfree  (uint32_t* nclst); /* Get number of free clusters on the drive */
    FRESULT getlabel (const TCHAR* path, TCHAR* label, uint32_t* vsn); /* Get volume label */
    FRESULT setlabel (const TCHAR* label); /* Set volume label */
    FRESULT forward  (FILE* fp, uint16_t (*func)(const uint8_t*, uint16_t), uint16_t btf, uint16_t* bf); /* Forward data to the stream */
    FRESULT expand   (FILE* fp, FSIZE_t szf, uint8_t opt); /* Allocate a contiguous block to the file */
    FRESULT mount    (uint8_t partition=0); /* Mount a logical drive */
    FRESULT umount   (); /* Unmount a logical drive */
//    FRESULT mkfs     (const TCHAR* path, uint8_t opt, uint32_t au, void* work, uint16_t len); /* Create a FAT volume */
//    FRESULT fdisk    (uint8_t pdrv, const uint32_t* szt, void* work); /* Divide a physical drive into some partitions */
//    FRESULT setcp    (uint16_t cp); /* Set current code page */
//    int     putc     (TCHAR c, FILE* fp); /* Put a character to the file */
//    int     puts     (const TCHAR* str, FILE* cp); /* Put a string to the file */
//    int     printf   (FILE* fp, const TCHAR* str, ...); /* Put a formatted string to the file */
//    TCHAR*  gets     (TCHAR* buff, int len, FILE* fp); /* Get a string from the file */

private:

    /*--------------------------------------------------------------*/
    /* FatFs module private methods and attributes                  */
    /*--------------------------------------------------------------*/

    uint16_t ld_word   (const uint8_t* ptr);
    uint32_t ld_dword  (const uint8_t* ptr);
    uint64_t ld_qword  (const uint8_t* ptr);
    void     st_word   (uint8_t* ptr, uint16_t val);
    void     st_dword  (uint8_t* ptr, uint32_t val);
    void     st_qword  (uint8_t* ptr, uint64_t val);

    void     mem_cpy(void* dst, const void* src, uint16_t cnt);
    void     mem_set(void* dst, int val, uint16_t cnt);
    int      mem_cmp(const void* dst, const void* src, uint16_t cnt);

    int      chk_chr(const char* str, int chr);
    int      dbc_1st(uint8_t c);
    int      dbc_2nd(uint8_t c);
    uint32_t tchar2uni(const TCHAR** str);
    uint8_t  put_utf(uint32_t chr, TCHAR* buf, uint16_t szb);

    int      lock_fs();
    void     unlock_fs(FRESULT res);

    FRESULT  chk_lock(DIR* dp, int acc);
    int      enq_lock(void);
    uint16_t inc_lock(DIR* dp, int acc);
    FRESULT  dec_lock(uint16_t i);
    void     clear_lock();

    FRESULT  sync_window();
    FRESULT  move_window(uint32_t sector);
    FRESULT  sync_fs();

    uint32_t clst2sect(uint32_t clst);
    uint32_t get_fat(uint32_t clst);
    FRESULT  put_fat(uint32_t clst, uint32_t val);

    uint32_t find_bitmap(uint32_t clst, uint32_t ncl);
    FRESULT  change_bitmap(uint32_t clst, uint32_t ncl, int bv);
    FRESULT  fill_first_frag(FFOBJID* obj);
    FRESULT  fill_last_frag(FFOBJID* obj, uint32_t lcl, uint32_t term);
    FRESULT  remove_chain(FFOBJID* obj, uint32_t clst, uint32_t pclst);
    uint32_t create_chain(uint32_t clst);
    uint32_t clmt_clust(FILE* fp, FSIZE_t ofs);
    FRESULT  dir_clear(uint32_t clst);
    FRESULT  dir_sdi(DIR* dp, uint32_t ofs);
    FRESULT  dir_next(DIR* dp, int stretch);
    FRESULT  dir_alloc(DIR* dp, uint16_t nent);
    uint32_t ld_clust(const uint8_t* dir);
    void     st_clust(uint8_t* dir, uint32_t cl);
    int      cmp_lfn(const WCHAR* lfnbuf, uint8_t* dir);
    int      pick_lfn(WCHAR* lfnbuf, uint8_t* dir);
    void     put_lfn(const WCHAR* lfn, uint8_t* dir, uint8_t ord, uint8_t sum);
    void     gen_numname(uint8_t* dst, const uint8_t* src, const WCHAR* lfn,
                     uint16_t seq);
    uint8_t  sum_sfn(const uint8_t* dir);
    uint16_t xdir_sum(const uint8_t* dir);
    uint16_t xname_sum(const WCHAR* name);
    uint32_t xsum32(uint8_t dat, uint32_t sum);
    void     get_xfileinfo(uint8_t* dirb, FILEINFO* fno);
    FRESULT  load_xdir(DIR* dp);
    void     init_alloc_info(FFOBJID* obj);
    FRESULT  load_obj_xdir(DIR* dp, const FFOBJID* obj);
    FRESULT  store_xdir(DIR* dp);
    void     create_xdir(uint8_t* dirb, const WCHAR* lfn);
    FRESULT  dir_read(DIR* dp, int vol);
    FRESULT  dir_find(DIR* dp);
    FRESULT  dir_register(DIR* dp);
    FRESULT  dir_remove(DIR* dp);
    void     get_fileinfo(DIR* dp, FILEINFO* fno);
    uint32_t get_achar(const TCHAR** ptr);
    int      pattern_matching(const TCHAR* pat, const TCHAR* nam, int skip, int inf);
    FRESULT  create_name(DIR* dp, const TCHAR** path);
    FRESULT  follow_path(DIR* dp, const TCHAR* path);
    uint8_t  check_fs(uint32_t sect);
    FRESULT  find_volume(uint8_t mode);
    FRESULT  validate(FFOBJID* obj);

    uint8_t  _fs_type;   /* Filesystem type (0:N/A) */
    uint8_t  _n_fats;    /* Number of FATs (1 or 2) */
    uint8_t  _wflag;     /* win[] flag (b0:dirty) */
    uint8_t  _fsi_flag;  /* FSINFO flags (b7:disabled, b0:dirty) */
    uint16_t _id;        /* Volume mount ID */
    uint16_t _n_rootdir; /* Number of root directory entries (FAT12/16) */
    uint16_t _csize;     /* Cluster size [sectors] */
#if FF_MAX_SS != FF_MIN_SS
    uint16_t _ssize;     /* Sector size (512, 1024, 2048 or 4096) */
#endif
#if FF_USE_LFN
    WCHAR*   _lfnbuf;    /* LFN working buffer */
#endif
#if FF_FS_EXFAT
    uint8_t* _dirbuf;    /* Directory entry block scratchpad buffer for exFAT */
#endif
#if FF_FS_REENTRANT
    FF_SYNC_t _sobj;     /* Identifier of sync object */
#endif
#if !FF_FS_READONLY
    uint32_t _last_clst; /* Last allocated cluster */
    uint32_t _free_clst; /* Number of free clusters */
#endif
#if FF_FS_RPATH
    uint32_t _cdir;      /* Current directory start cluster (0:root) */
#if FF_FS_EXFAT
    uint32_t _cdc_scl;   /* Containing directory start cluster (invalid when cdir is 0) */
    uint32_t _cdc_size;  /* b31-b8:Size of containing directory, b7-b0: Chain status */
    uint32_t _cdc_ofs;   /* Offset in the containing directory (invalid when cdir is 0) */
#endif
#endif
    uint32_t _n_fatent;  /* Number of FAT entries (number of clusters + 2) */
    uint32_t _fsize;     /* Size of an FAT [sectors] */
    uint32_t _volbase;   /* Volume base sector */
    uint32_t _fatbase;   /* FAT base sector */
    uint32_t _dirbase;   /* Root directory base sector/cluster */
    uint32_t _database;  /* Data base sector */
    uint32_t _winsect;   /* Current sector appearing in the win[] */
    uint8_t  _win[FF_MAX_SS]; /* Disk access window for Directory, FAT (and file data at tiny cfg) */

    bool     _mounted;
    uint8_t  _partition; /* 0=auto, 1...4 primary partition */

    block_io_interface & _io;

    FatFs::FILE * _f_ptrs[10] = { 0 }; // File handles for Posix adapter

public:
    // Posix File IO adapter
    ////////////////////////
    int _read  (int file, char *buf, int len) override;
    int _write (int file, const char *buf, int len) override;
    int _open  (const char *name, int flags, int mode) override;
    int _close (int file) override;
    int _link  (char *old_name, char *new_name) override;
    int _unlink(char *name) override;
    int _stat  (char *name, struct stat *st) override;
    int _fstat (int file, struct stat *st) override;
    int _lseek (int file, int offset, int whence) override;
    int _isatty(int file) override;

    void set_errno(FRESULT r);

};

#define f_eof(fp) ((int)((fp)->fptr == (fp)->obj.objsize))
#define f_error(fp) ((fp)->err)
#define f_tell(fp) ((fp)->fptr)
#define f_size(fp) ((fp)->obj.objsize)
#define f_rewind(fp) f_lseek((fp), 0)
#define f_rewinddir(dp) f_readdir((dp), 0)
#define f_rmdir(path) f_unlink(path)
#define f_unmount(path) f_mount(0, path, 0)


/*--------------------------------------------------------------*/
/* Additional user defined functions                            */

/* RTC function */
#if !FF_FS_READONLY && !FF_FS_NORTC
uint32_t get_fattime(void);
#endif

/* LFN support functions */
#if FF_USE_LFN >= 1						/* Code conversion (defined in unicode.c) */
WCHAR ff_oem2uni (WCHAR oem, uint16_t cp); /* OEM code to Unicode conversion */
WCHAR ff_uni2oem (uint32_t uni, uint16_t cp); /* Unicode to OEM code conversion */
uint32_t ff_wtoupper (uint32_t uni); /* Unicode upper-case conversion */
#endif
#if FF_USE_LFN == 3						/* Dynamic memory allocation */
void* ff_memalloc (uint16_t msize); /* Allocate memory block */
void ff_memfree (void* mblock); /* Free memory block */
#endif

/* Sync functions */
#if FF_FS_REENTRANT
int ff_cre_syncobj (uint8_t vol, FF_SYNC_t* sobj); /* Create a sync object */
int ff_req_grant (FF_SYNC_t sobj); /* Lock sync object */
void ff_rel_grant (FF_SYNC_t sobj); /* Unlock sync object */
int ff_del_syncobj (FF_SYNC_t sobj); /* Delete a sync object */
#endif


#endif /* FF_DEFINED */
