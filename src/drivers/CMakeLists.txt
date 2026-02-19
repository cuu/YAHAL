cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
        bme280_drv.cpp
        cy8x95xxa_drv.cpp
        gp2y1010au0f_drv.cpp
        ina219_drv.cpp
        max30102_drv.cpp
        mcp23s17_drv.cpp
        mfrc522_drv.cpp
        opt3001_drv.cpp
        sd_spi_drv.cpp
        sharp96_drv.cpp
        soft_i2c_master.cpp
        soft_i2c_slave.cpp
        soft_i2c_slave_states.cpp
        ssd2119_drv.cpp
        st7735s_drv.cpp
	ili9488_drv.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

