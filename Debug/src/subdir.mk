################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c 

OBJS += \
./src/main.o \
./src/syscalls.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32 -DSTM32F105RCTx -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_CL -I"C:/Users/Ryan/workspace/avionics/inc" -I"C:/Users/Ryan/workspace/avionics/CMSIS/core" -I"C:/Users/Ryan/workspace/avionics/CMSIS/device" -I"C:/Users/Ryan/workspace/avionics/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


