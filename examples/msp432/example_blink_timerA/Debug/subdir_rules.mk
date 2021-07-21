################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/opt/ti/ccs1020/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc-7.2.1" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -D__MSP432P401R__ -Dgcc -I"/home/student/git/YAHAL/include/interface" -I"/home/student/git/YAHAL/src/FatFs" -I"/home/student/git/YAHAL/src/driver" -I"/home/student/git/YAHAL/src/libmad" -I"/home/student/git/YAHAL/src/platform/msp432" -I"/home/student/git/YAHAL/src/task" -I"/home/student/git/YAHAL/src/uGUI" -I"/home/student/git/YAHAL/src/uGUI/fonts" -I"/home/student/git/YAHAL/src/util" -I"/home/student/git/YAHAL/src/platform/msp432/DSP/Include" -I"/opt/ti/ccs1020/ccs/ccs_base/arm/include" -I"/opt/ti/ccs1020/ccs/ccs_base/arm/include/CMSIS" -I"/home/student/mct_workspace/example_blink_timerA" -I"/opt/ti/ccs1020/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/arm-none-eabi/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"   -fno-threadsafe-statics $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/opt/ti/ccs1020/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc-7.2.1" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -D__MSP432P401R__ -Dgcc -I"/home/student/git/YAHAL/include/interface" -I"/home/student/git/YAHAL/src/FatFs" -I"/home/student/git/YAHAL/src/driver" -I"/home/student/git/YAHAL/src/libmad" -I"/home/student/git/YAHAL/src/platform/msp432" -I"/home/student/git/YAHAL/src/task" -I"/home/student/git/YAHAL/src/uGUI" -I"/home/student/git/YAHAL/src/uGUI/fonts" -I"/home/student/git/YAHAL/src/util" -I"/home/student/git/YAHAL/src/platform/msp432/DSP/Include" -I"/opt/ti/ccs1020/ccs/ccs_base/arm/include" -I"/opt/ti/ccs1020/ccs/ccs_base/arm/include/CMSIS" -I"/home/student/mct_workspace/example_blink_timerA" -I"/opt/ti/ccs1020/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/arm-none-eabi/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


