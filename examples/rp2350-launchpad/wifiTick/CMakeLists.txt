# Finde alle Unterordner mit CMakeLists.txt im aktuellen Verzeichnis
file(GLOB subdirectories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)

# Schleife über alle gefundenen Unterordner
foreach(subdirectory ${subdirectories})
    # Überspringe alle mit "esp8266" im Namen
    if(subdirectory MATCHES "esp8266")
        continue()
    endif()
    
    # Ermittle den Pfad zum aktuellen Unterordner
    get_filename_component(subdirectory_path ${subdirectory} DIRECTORY)

    # Füge den Unterordner hinzu
    add_subdirectory(${subdirectory_path})
endforeach()
