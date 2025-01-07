cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
        gpio_rp2350.cpp
        lock_base_rp2350.cpp
        pcm_pwm_rp2350_drv.cpp
        spi_rp2350.cpp
        task_rp2350.cpp
        timer_rp2350.cpp
        uart_rp2350.cpp

        # Due to the weak irq functions these
        # files have to be last.
        startup_rp2350.cpp
        system_rp2350.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
