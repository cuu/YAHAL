cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
    adc_esp8266.cpp
    gpio_esp8266.cpp
    timer_esp8266.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

