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

add_subdirectory(wrappers)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

