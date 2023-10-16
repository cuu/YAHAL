cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
        adc_rp2040.cpp
        dac8311_rp2040_drv.cpp
        gpio_rp2040.cpp
        i2c_rp2040.cpp
        lock_base_rp2040.cpp
        pio_rp2040.cpp
        spi_rp2040.cpp
        task_rp2040.cpp
        timer_rp2040.cpp
        uart_rp2040.cpp
        ws2812_rp2040.cpp

        # Due to the weak irq functions these
        # files have to be last.
        startup_rp2040.cpp
        system_rp2040.cpp
)

# generate PIO header files
generate_pio_header(
        ${YAHAL_TARGET}
        ${CMAKE_CURRENT_LIST_DIR}/pio/ws2812.pio
        OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/pio)
generate_pio_header(
        ${YAHAL_TARGET}
        ${CMAKE_CURRENT_LIST_DIR}/pio/dac8311.pio
        OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/pio)

add_subdirectory(wrappers)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
