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
#ifndef ELF2UF2_UF2_STRUCTS_H
#define ELF2UF2_UF2_STRUCTS_H

#include <array>
#include <iostream>
#include <cstdint>
using std::array;

#define UF2_MAGIC_START0 0x0A324655u
#define UF2_MAGIC_START1 0x9E5D5157u
#define UF2_MAGIC_END    0x0AB16F30u

#define UF2_FLAG_NOT_MAIN_FLASH          0x00000001u
#define UF2_FLAG_FILE_CONTAINER          0x00001000u
#define UF2_FLAG_FAMILY_ID_PRESENT       0x00002000u
#define UF2_FLAG_MD5_PRESENT             0x00004000u
#define UF2_FLAG_EXTENSION_FLAGS_PRESENT 0x00008000u

const array<uint8_t, 4> UF2_EXTENSION_RP2_IGNORE_BLOCK {0x04, 0xe3, 0x57, 0x99};

enum class family_id_t : uint32_t {
    ATMEGA32        = 0x16573617,    // Microchip (Atmel) ATmega32
    SAML21          = 0x1851780a,    // Microchip (Atmel) SAML21
    NRF52           = 0x1b57745f,    // Nordic NRF52
    ESP32           = 0x1c5f21b0,    // ESP32
    STM32L1         = 0x1e1f432d,    // ST STM32L1xx
    STM32L0         = 0x202e3a91,    // ST STM32L= 0xx
    STM32WL         = 0x21460ff0,    // ST STM32WLxx
    RTL8710B        = 0x22e0d6fc,    // Realtek AmebaZ RTL8710B
    LPC55           = 0x2abc77ec,    // NXP LPC55xx
    STM32G0         = 0x300f5633,    // ST STM32G= 0xx
    GD32F350        = 0x31d228c6,    // GD32F350
    RTL8720D        = 0x3379CFE2,    // Realtek AmebaD RTL8720D
    STM32L5         = 0x04240bdf,    // ST STM32L5xx
    STM32G4         = 0x4c71240a,    // ST STM32G4xx
    MIMXRT10XX      = 0x4fb2d5bd,    // NXP i.MX RT10XX
    XR809           = 0x51e903a8,    // Xradiotech 809
    STM32F7         = 0x53b80f00,    // ST STM32F7xx
    SAMD51          = 0x55114460,    // Microchip (Atmel) SAMD51
    STM32F4         = 0x57755a57,    // ST STM32F4xx
    FX2             = 0x5a18069b,    // Cypress FX2
    STM32F2         = 0x5d1a0a2e,    // ST STM32F2xx
    STM32F1         = 0x5ee21072,    // ST STM32F103
    NRF52833        = 0x621e937a,    // Nordic NRF52833
    STM32F0         = 0x647824b6,    // ST STM32F= 0xx
    BK7231U         = 0x675a40b0,    // Beken 7231U/7231T
    SAMD21          = 0x68ed2b88,    // Microchip (Atmel) SAMD21
    BK7251          = 0x6a82cc42,    // Beken 7251/7252
    STM32F3         = 0x6b846188,    // ST STM32F3xx
    STM32F407       = 0x6d0922fa,    // ST STM32F407
    STM32H5         = 0x4e8f1c5d,    // ST STM32H5xx
    STM32H7         = 0x6db66082,    // ST STM32H7xx
    STM32WB         = 0x70d16653,    // ST STM32WBxx
    BK7231N         = 0x7b3ef230,    // Beken 7231N
    ESP8266         = 0x7eab61ed,    // ESP8266
    KL32L2          = 0x7f83e793,    // NXP KL32L2x
    STM32F407VG     = 0x8fb060fe,    // ST STM32F407VG
    RTL8710A        = 0x9fffd543,    // Realtek Ameba1 RTL8710A
    NRF52840        = 0xada52840,    // Nordic NRF52840
    NRF52820        = 0x820d9a5f,    // Nordic NRF52820_xxAA
    ESP32S2         = 0xbfdd4eee,    // ESP32-S2
    ESP32S3         = 0xc47e5767,    // ESP32-S3
    ESP32C3         = 0xd42ba06c,    // ESP32-C3
    ESP32C2         = 0x2b88d29c,    // ESP32-C2
    ESP32H2         = 0x332726f6,    // ESP32-H2
    ESP32C6         = 0x540ddf62,    // ESP32-C6
    ESP32P4         = 0x3d308e94,    // ESP32-P4
    ESP32C5         = 0xf71c0343,    // ESP32-C5
    ESP32C61        = 0x77d850c4,    // ESP32-C61
    ESP32H21        = 0xb6dd00af,    // ESP32-H21
    ESP32H4         = 0x9e0baa8a,    // ESP32-H4
    BL602           = 0xde1270b7,    // Boufallo 602
    RTL8720C        = 0xe08f7564,    // Realtek AmebaZ2 RTL8720C
    RP2040          = 0xe48bff56,    // Raspberry Pi RP2040
    RP2XXX_ABSOLUTE = 0xe48bff57,    // Raspberry Pi Microcontrollers: Absolute (unpartitioned) download
    RP2XXX_DATA     = 0xe48bff58,    // Raspberry Pi Microcontrollers: Data partition download
    RP2350_ARM_S    = 0xe48bff59,    // Raspberry Pi RP2350 Secure Arm image
    RP2350_RISCV    = 0xe48bff5a,    // Raspberry Pi RP2350 RISC-V image
    RP2350_ARM_NS   = 0xe48bff5b,    // Raspberry Pi RP2350 Non-secure Arm image
    STM32L4         = 0x00ff6919,    // ST STM32L4xx
    GD32VF103       = 0x9af03e33,    // GigaDevice GD32VF103
    CSK4            = 0x4f6ace52,    // LISTENAI CSK30= 0x/40= 0x
    CSK6            = 0x6e7348a8,    // LISTENAI CSK6= 0xx
    M0SENSE         = 0x11de784a,    // M0SENSE BL702
    MaixPlay_U4     = 0x4b684d71,    // Sipeed MaixPlay-U4(BL618)
    RZA1LU          = 0x9517422f,    // Renesas RZ/A1LU (R7S721= 0xx)
    STM32F411xE     = 0x2dc309c5,    // ST STM32F411xE
    STM32F411xC     = 0x06d1097b,    // ST STM32F411xC
    NRF52832xxAA    = 0x72721d4e,    // Nordic NRF52832xxAA
    NRF52832xxAB    = 0x6f752678,    // Nordic NRF52832xxAB
    AT32F415        = 0xa0c97b8e,    // ArteryTek AT32F415
    CH32V           = 0x699b62ec,    // WCH CH32V2xx and CH32V3xx
    RA4M1           = 0x7be8976d,    // Renesas RA4M1
};

std::ostream & operator << (std::ostream & os, const family_id_t &);

union filesize_family_t {
    uint32_t    filesize;
    family_id_t family_id;
};

typedef struct __attribute__((packed)) {
    // 32 byte header
    uint32_t            magicStart0;
    uint32_t            magicStart1;
    uint32_t            flags;
    uint32_t            targetAddr;
    uint32_t            payloadSize;
    uint32_t            blockNo;
    uint32_t            numBlocks;
    // file size or family or 0
    filesize_family_t   filesize_family;

    // raw data;
    uint8_t data[476];

    // store magic also at the end to limit damage from partial block reads
    uint32_t magicEnd;
} UF2_Block;

static_assert(sizeof(UF2_Block) == 512);

#endif //ELF2UF2_UF2_STRUCTS_H
