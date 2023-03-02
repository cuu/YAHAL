cmake_minimum_required(VERSION 3.16)

# Include YAHAL functions and macros
include(cmake/YAHAL_import.cmake)

project(YAHAL CXX C ASM)

add_library(${YAHAL_TARGET})

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tools)

