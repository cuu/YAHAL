cmake_minimum_required(VERSION 3.16)

function(yahal_add_uf2_output TARGET)
    # Load package if not already loaded
    if (NOT ELF2UF2_FOUND)
        find_package(ELF2UF2)
    endif()

    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)

    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ELF2UF2 ${TF} ${TN}.uf2 
    )
endfunction()


function(generate_pio_header TARGET PIO)
    # Load package if not already loaded
    if (NOT PIOASM_FOUND)
        find_package(PIOASM REQUIRED)
    endif()

    cmake_parse_arguments(generate_pio_header "" "OUTPUT_FORMAT;OUTPUT_DIR" "" ${ARGN} )

    # Output format default is yahal
    if (generate_pio_header_OUTPUT_FORMAT)
        set(OUTPUT_FORMAT "${generate_pio_header_OUTPUT_FORMAT}")
    else()
        set(OUTPUT_FORMAT "yahal")
    endif()

    # Output directory default is cmake's binary dir
    if (generate_pio_header_OUTPUT_DIR)
        get_filename_component(HEADER_DIR ${generate_pio_header_OUTPUT_DIR} ABSOLUTE)
    else()
        set(HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    # Calculate header file name (same as pio file)
    get_filename_component(PIO_NAME ${PIO} NAME)
    set(HEADER "${HEADER_DIR}/${PIO_NAME}.h")

    get_filename_component(HEADER_GEN_TARGET ${PIO} NAME_WE)
    set(HEADER_GEN_TARGET "${TARGET}_${HEADER_GEN_TARGET}_pio_h")

    add_custom_target(${HEADER_GEN_TARGET} DEPENDS ${HEADER})

    add_custom_command(OUTPUT ${HEADER}
        DEPENDS ${PIO}
        COMMAND PIOASM -o ${OUTPUT_FORMAT} ${PIO} ${HEADER}
    )
    add_dependencies(${TARGET} ${HEADER_GEN_TARGET})

    get_target_property(target_type ${TARGET} TYPE)

    if ("INTERFACE_LIBRARY" STREQUAL "${target_type}")
        target_include_directories(${TARGET} INTERFACE ${HEADER_DIR})
    else()
        target_include_directories(${TARGET} PUBLIC ${HEADER_DIR})
    endif()
endfunction()


function(png_to_cpp TARGET PNG)
    # Load package if not already loaded
    if (NOT PNG2CPP_FOUND)
        find_package(PNG2CPP REQUIRED)
    endif()

    # Parse argument
    cmake_parse_arguments(png_to_cpp "" "BG_COLOR;OUTPUT_FILE" "" ${ARGN} )

    # Paramters are all relative to current CMakeList.txt
    set(PNG     "${CMAKE_CURRENT_LIST_DIR}/${PNG}")
    set(CPPFILE "${CMAKE_CURRENT_LIST_DIR}/${png_to_cpp_OUTPUT_FILE}")
    get_filename_component(NAME_WE ${PNG} NAME_WE)

    #Add a new target which depends on the cpp file
    set(PNG_TARGET "${PROJECT_NAME}_${NAME_WE}_cpp")
    add_custom_target(${PNG_TARGET} DEPENDS ${CPPFILE})

    add_custom_command(
        OUTPUT          ${CPPFILE}
        MAIN_DEPENDENCY ${PNG}
        COMMAND PNG2CPP -o ${CPPFILE} -b ${png_to_cpp_BG_COLOR} ${PNG}
    )

    add_dependencies(${TARGET} ${PNG_TARGET})
endfunction()

function(file_to_cpp TARGET FILE)
    # Load package if not already loaded
    if (NOT FILE2CPP_FOUND)
        find_package(FILE2CPP REQUIRED)
    endif()

    # Parse argument
    cmake_parse_arguments(file_to_cpp "" "OUTPUT_DIR" "" ${ARGN} )

    # Paramters are all relative to current CMakeList.txt
    set(INFILE  "${CMAKE_CURRENT_LIST_DIR}/${FILE}")
    set(OUT_DIR "${CMAKE_CURRENT_LIST_DIR}/${file_to_cpp_OUTPUT_DIR}")
    get_filename_component(NAME_WE ${FILE} NAME_WE)
    set(CPPFILE "${OUT_DIR}/${NAME_WE}.cpp")
    set(HFILE   "${OUT_DIR}/${NAME_WE}.h")

    #Add a new target which depends on the cpp file
    set(FILE_TARGET "${PROJECT_NAME}_${NAME_WE}_cpp")
    add_custom_target(${FILE_TARGET} DEPENDS ${CPPFILE})

    add_custom_command(
        OUTPUT          ${CPPFILE} ${HFILE}
        MAIN_DEPENDENCY ${INFILE}
        COMMAND FILE2CPP -o ${OUT_DIR} ${INFILE}
    )

    add_dependencies(${TARGET} ${FILE_TARGET})

    target_include_directories(${TARGET} PRIVATE ${OUT_DIR})
endfunction()

function(mp3pcm_to_cpp TARGET FILE)
    # Load package if not already loaded
    if (NOT MP3PCM2CPP_FOUND)
        find_package(MP3PCM2CPP REQUIRED)
    endif()

    # Parse argument
    cmake_parse_arguments(mp3pcm_to_cpp "" "MODE;OUTPUT_DIR" "" ${ARGN} )
    # Paramters are all relative to current CMakeList.txt
    set(INFILE  "${CMAKE_CURRENT_LIST_DIR}/${FILE}")
    set(OUT_DIR "${CMAKE_CURRENT_LIST_DIR}/${mp3pcm_to_cpp_OUTPUT_DIR}")
    if (mp3pcm_to_cpp_MODE)
        set(MODE    "${mp3pcm_to_cpp_MODE}")
    else()
        set(MODE    "stereo")
    endif()
    get_filename_component(NAME_WE ${FILE} NAME_WE)
    set(CPPFILE "${OUT_DIR}/${NAME_WE}.cpp")
    set(HFILE   "${OUT_DIR}/${NAME_WE}.h")

    #Add a new target which depends on the cpp file
    set(FILE_TARGET "${PROJECT_NAME}_${NAME_WE}_cpp")
    add_custom_target(${FILE_TARGET} DEPENDS ${CPPFILE})

    add_custom_command(
        OUTPUT          ${CPPFILE} ${HFILE}
        MAIN_DEPENDENCY ${INFILE}
        COMMAND MP3PCM2CPP -m ${MODE} -o ${OUT_DIR} ${INFILE}
    )

    add_dependencies(${TARGET} ${FILE_TARGET})

    target_include_directories(${TARGET} PRIVATE ${OUT_DIR})
endfunction()
