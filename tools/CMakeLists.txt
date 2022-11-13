cmake_minimum_required(VERSION 3.16)

function(png_to_cpp TARGET PNG)
    if (NOT PNG2CPP_FOUND)
        find_package(PNG2CPP REQUIRED)
    endif()
    set(PNG ${CMAKE_CURRENT_SOURCE_DIR}/${PNG})

    get_filename_component(PNG_NAME ${PNG} NAME_WE)
    get_filename_component(PNG_PATH ${PNG} DIRECTORY)
    set(CPPFILE "${PNG_PATH}/${PNG_NAME}.cpp")

    set(PNG_TARGET "${PNG_NAME}_cpp")
    add_custom_target(${PNG_TARGET} DEPENDS ${CPPFILE})

    add_custom_command(
        OUTPUT          ${CPPFILE}
        MAIN_DEPENDENCY ${PNG}
        COMMAND PNG2CPP -f ${PNG}
    )

    add_dependencies(${TARGET} ${PNG_TARGET})
endfunction()
