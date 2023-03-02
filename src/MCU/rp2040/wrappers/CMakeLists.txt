cmake_minimum_required(VERSION 3.16)

add_library(rp2040_wrapper OBJECT
    bootrom.c
    platform.c
    asm_helper.S

    double_init_rom.c
    double_math.c
    double_v1_rom_shim.S
    double_aeabi.S

    float_init_rom.c
    float_math.c
    float_v1_rom_shim.S
    float_aeabi.S

    divider_helper.S
    divider.S
    pico_int64_ops_aeabi.S

    bit_ops_aeabi.S
)

target_include_directories(rp2040_wrapper PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${YAHAL_TARGET} rp2040_wrapper)
