##############################################
# Initiaize YAHAL by setting the properties of
# the board, MCU, toolchain etc.
##############################################

if (NOT TARGET yahal_init_guard)
add_library(yahal_init_guard INTERFACE)

#
# Check if a target board has been set
#
if (DEFINED ENV{YAHAL_BOARD} AND (NOT YAHAL_BOARD))
    set(YAHAL_BOARD $ENV{YAHAL_BOARD})
    message("Using YAHAL_BOARD from environment ('${YAHAL_BOARD}')")
endif()
if (NOT YAHAL_BOARD)
    message(FATAL_ERROR "No target board was specified! (YAHAL_BOARD)")
endif()

#
# This script might be called from the YAHAHL top-level
# CMakeLists.txt. In this case YAHAL_DIR is not yet set!
#
if (NOT YAHAL_DIR)
    set(YAHAL_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
    get_filename_component(YAHAL_DIR "${YAHAL_DIR}" REALPATH ${CMAKE_CURRENT_LIST_DIR}/..)
endif ()
set(YAHAL_DIR ${YAHAL_DIR} CACHE PATH "Path to the YAHAL library")
message("YAHAL_DIR is ${YAHAL_DIR}")

#
# Add YAHAL's cmake folder to the known paths of cmake modules
#
list(APPEND CMAKE_MODULE_PATH ${YAHAL_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${YAHAL_DIR}/cmake/packages)

#
# Load board definition
#
include(boards/${YAHAL_BOARD})


#string(TOLOWER "${CMAKE_CURRENT_LIST_DIR}" __list_dir)
#string(TOLOWER "${CMAKE_SOURCE_DIR}/cmake" __source_dir)
#message(${CMAKE_CURRENT_LIST_DIR})
#message(${CMAKE_SOURCE_DIR})
#if (__source_dir STREQUAL __list_dir)
#    message("****** Root build *******")
#else()
#    message("****** App build *******")
#endif()


#
# Macro to add YAHAL as a subdirectory to a project
#
macro(yahal_add_me)
    if (NOT CMAKE_PROJECT_NAME)
        message(WARNING "yahal_add_me() should be called after the project is created (and languages added)")
    endif()
    add_subdirectory(${YAHAL_DIR} YAHAL)

endmacro()


macro (yahal_add_custom_targets TARGET)
    if (OPENOCD_CONFIG)
        set(TF $<TARGET_FILE:${TARGET}>)
        add_custom_target(upload 
            openocd ${OPENOCD_CONFIG} -c "program \"${TF}\" verify reset exit"
            DEPENDS ${TF}
            VERBATIM
        )
    endif()
endmacro()


function(yahal_add_hex_output TARGET)
    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)
    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${TF} ${TN}.hex
    )
endfunction()


function(yahal_add_bin_output TARGET)
    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)
    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${TF} ${TN}.bin
    )
endfunction()


function(yahal_add_dis_output TARGET)
    set(TF $<TARGET_FILE:${TARGET}>)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    set(TO $<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>)

    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_OBJDUMP} ${TF} -h    > ${TN}.dis
        COMMAND ${CMAKE_OBJDUMP} ${TF} -d -C >>${TN}.dis
    )
endfunction()


function(yahal_rename_mapfile TARGET)
    set(TN $<TARGET_PROPERTY:${TARGET},NAME>)
    add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E rename mapfile ${TN}.map
    )
endfunction()


function(yahal_add_extra_outputs TARGET)
    set_property(TARGET ${TARGET} PROPERTY SUFFIX .elf)
    yahal_add_hex_output(${TARGET})
    yahal_add_bin_output(${TARGET})
    yahal_add_dis_output(${TARGET})
    yahal_rename_mapfile(${TARGET})
endfunction()

endif()
