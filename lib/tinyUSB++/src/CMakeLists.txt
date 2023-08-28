target_sources(${PROJECT_NAME} PRIVATE
    usb_device.cpp
    usb_configuration.cpp
    usb_interface_association.cpp
    usb_interface.cpp
    usb_endpoint.cpp
    usb_strings.cpp
    usb_device_controller.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
