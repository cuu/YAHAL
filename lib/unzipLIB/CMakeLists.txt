cmake_minimum_required(VERSION 3.16)

set(UNZIPLIB_TARGET unzipLIB_${PROJECT_NAME})

add_library(${UNZIPLIB_TARGET})

target_compile_options(${UNZIPLIB_TARGET}
        PRIVATE -Ofast)

add_subdirectory(src)
