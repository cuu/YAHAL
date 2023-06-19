cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(rp2040-launchpad-examples)

# Finde alle Unterordner mit CMakeLists.txt im aktuellen Verzeichnis
file(GLOB subdirectories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)

# Schleife über alle gefundenen Unterordner
foreach(subdirectory ${subdirectories})
    # Ermittle den Pfad zum aktuellen Unterordner
    get_filename_component(subdirectory_path ${subdirectory} DIRECTORY)

    # Füge den Unterordner hinzu
    add_subdirectory(${subdirectory_path})
endforeach()
