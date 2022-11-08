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
macro(YAHAL_init)
    if (NOT CMAKE_PROJECT_NAME)
        message(WARNING "YAHAL_init() should be called after the project is created (and languages added)")
    endif()
    add_subdirectory(${YAHAL_DIR} YAHAL)
endmacro()

endif()

