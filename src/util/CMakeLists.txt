cmake_minimum_required(VERSION 3.16)

target_sources(${YAHAL_TARGET} PRIVATE
    cpp_support.cpp
    posix_io.cpp
    std_io.cpp
    yahal_String.cpp
)

target_include_directories(${YAHAL_TARGET} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

