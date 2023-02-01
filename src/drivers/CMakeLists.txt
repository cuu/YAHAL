cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
    bme280_drv.cpp
    gp2y1010au0f_drv.cpp
    opt3001_drv.cpp
    soft_i2c_master.cpp
    ssd2119_drv.cpp
    button_gnd_drv.cpp
    ina219_drv.cpp
    sd_spi_drv.cpp
    soft_i2c_slave.cpp
    st7735s_drv.cpp
    cy8x95xxa_drv.cpp
    mcp23s17_drv.cpp
    sharp96_drv.cpp
    soft_i2c_slave_states.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

