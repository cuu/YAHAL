####################################
# Configuration for ARM Cortex M4F #
####################################

# Architecture flags
set(CORTEX_FLAGS "-mcpu=cortex-m0plus -march=armv6s-m -mthumb")

# Add flags
foreach(LANG IN ITEMS C CXX ASM)
    set(CMAKE_${LANG}_FLAGS_INIT "${CMAKE_${LANG}_FLAGS_INIT} ${CORTEX_FLAGS}")
endforeach()

