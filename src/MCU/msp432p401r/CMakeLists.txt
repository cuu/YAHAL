cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
    adc14_msp432.cpp
    clock_msp432.cpp
    dma_msp432.cpp
    gpio_msp432.cpp
    i2c_msp432.cpp
    irq_dispatcher.cpp
    spi_msp432.cpp
    startup_msp432p401r_gcc.cpp
    task_msp432.cpp
    timerA_msp432.cpp
    timer_msp432.cpp
    uart_msp432.cpp
    system_msp432p401r.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

