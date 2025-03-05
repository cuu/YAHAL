cmake_minimum_required(VERSION 3.16)
project(elf2uf2)

set(CMAKE_CXX_STANDARD 20)

add_executable(elf2uf2
        elf2uf2.cpp
)

# Needed for elfio, because include paths are
# given as elfio/... in the source code.
target_include_directories(elf2uf2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(boot_blocks)
add_subdirectory(crc32)
add_subdirectory(uf2)

