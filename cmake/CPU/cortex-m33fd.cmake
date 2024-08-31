####################################
# Configuration for ARM Cortex M33 #
####################################
# Set CPU name
set(YAHAL_CPU "cortex-m33")

# Architecture flags
add_compile_options(-mcpu=cortex-m33 -march=armv8-m.main+fp+dsp -mthumb)
add_link_options(-mcpu=cortex-m33 -march=armv8-m.main+fp+dsp -mthumb)

# Math flags 
add_compile_definitions(ARM_MATH_CM33)
add_compile_options(-mfloat-abi=softfp)
add_link_options(-mfloat-abi=softfp)

