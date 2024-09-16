################################################################
# Configuration for ARM Cortex M33 with FPU and DSP extensions #
################################################################
# Set CPU name
set(YAHAL_CPU "cortex-m33fd")

# Architecture flags
add_compile_options(-mcpu=cortex-m33 -march=armv8-m.main+fp+dsp -mthumb)
add_link_options(-mcpu=cortex-m33 -march=armv8-m.main+fp+dsp -mthumb)

# FPU flags
add_compile_definitions(ARM_MATH_CM33)
add_compile_options(-mfloat-abi=softfp)
add_link_options(-mfloat-abi=softfp)
