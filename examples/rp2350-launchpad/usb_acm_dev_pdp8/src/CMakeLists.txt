target_sources(usb_acm_dev_pdp8 PRIVATE
    CPU.cpp
    Devices.cpp
    Device_TTI.cpp
    Device_TTO.cpp
    Memory.cpp
    Focal69.cpp
)

target_include_directories(usb_acm_dev_pdp8 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
