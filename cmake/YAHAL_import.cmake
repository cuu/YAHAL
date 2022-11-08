#####################################################
# This script tries to locate the YAHAL root folder #
#####################################################

#
# Check if we can get the path from a environment variable
#
if (DEFINED ENV{YAHAL_DIR} AND (NOT YAHAL_DIR))
    set(YAHAL_DIR $ENV{YAHAL_DIR})
    message("Using YAHAL_DIR from environment ('${YAHAL_DIR}')")
else()
    # For most examples YAHAL is located three directories ahead
    message("Trying to find YAHAL at ../../..")
    set(YAHAL_DIR "../../..")
endif ()

#
# Try to resolve a relative path
#
get_filename_component(YAHAL_DIR "${YAHAL_DIR}" REALPATH BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
if (NOT EXISTS ${YAHAL_DIR})
    message(FATAL_ERROR "Directory '${YAHAL_DIR}' not found")
endif ()

#
# Check if YAHAL_DIR points to the correct folder.
#
set(YAHAL_INIT_CMAKE_FILE ${YAHAL_DIR}/cmake/YAHAL_init.cmake)
if (NOT EXISTS ${YAHAL_INIT_CMAKE_FILE})
    message(FATAL_ERROR "Directory '${YAHAL_DIR}' does not appear to be a YAHAL root folder")
endif ()

#
# Finally include the init-script
#
include(${YAHAL_INIT_CMAKE_FILE})

