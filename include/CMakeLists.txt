cmake_minimum_required(VERSION 3.16)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CPU/${YAHAL_CPU}
    ${CMAKE_CURRENT_LIST_DIR}/MCU/${YAHAL_MCU}
    ${CMAKE_CURRENT_LIST_DIR}/interface
)

