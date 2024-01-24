cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(mp3pcm2cpp CXX)

add_executable(mp3pcm2cpp
    mp3pcm2cpp.cpp
)

add_subdirectory(../../lib/MAD MAD)
target_link_libraries(mp3pcm2cpp PRIVATE MAD_mp3pcm2cpp)

