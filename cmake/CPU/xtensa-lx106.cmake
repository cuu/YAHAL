##################################
# Configuration for xtensa LX106 #
##################################
# Set CPU name
set(YAHAL_CPU "xtensa-lx106")

# Architecture flags
# set(CORTEX_FLAGS "-mcpu=cortex-m0plus -march=armv6s-m -mthumb")

# Math flags 
# add_compile_definitions(ARM_MATH_CM0PLUS)

# Add flags
#foreach(LANG IN ITEMS C CXX ASM)
#    set(CMAKE_${LANG}_FLAGS "${CMAKE_${LANG}_FLAGS} ${CORTEX_FLAGS}")
#endforeach()

