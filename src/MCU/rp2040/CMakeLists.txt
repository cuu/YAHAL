cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
    gpio_rp2040.cpp
    pio_rp2040.cpp
    task_rp2040.cpp 
    uart_rp2040.cpp
    lock_base_rp2040.cpp 
    spi_rp2040.cpp
    timer_rp2040.cpp
    startup_rp2040.cpp
    system_rp2040.cpp
)

if(DEFINED YAHAL_WRAP_FLOAT)
target_sources(${YAHAL_TARGET} PRIVATE
    wrappers/bootrom.c
    wrappers/platform.c
    wrappers/float_aeabi.S
    wrappers/float_init_rom.c
    wrappers/float_math.c
    wrappers/float_v1_rom_shim.S
)
endif()

if(DEFINED YAHAL_WRAP_FLOAT)
target_sources(${YAHAL_TARGET} PRIVATE
    wrappers/bootrom.c
    wrappers/platform.c
    wrappers/double_aeabi.S
    wrappers/double_init_rom.c
    wrappers/double_math.c
    wrappers/double_v1_rom_shim.S
)
endif()

if(DEFINED YAHAL_WRAP_BITOPS)
target_sources(${YAHAL_TARGET} PRIVATE
    wrappers/bootrom.c
    wrappers/bit_ops_aeabi.S
)
endif()

if(DEFINED YAHAL_WRAP_DIVMUL)
target_sources(${YAHAL_TARGET} PRIVATE
    wrappers/bootrom.c
    wrappers/divider.S
    wrappers/pico_int64_ops_aeabi.S
)
endif()

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

