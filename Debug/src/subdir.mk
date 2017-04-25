################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/baro.c \
../src/gps.c \
../src/imu.c \
../src/led.c \
../src/main.c \
../src/radio.c \
../src/syscalls.c 

OBJS += \
./src/baro.o \
./src/gps.o \
./src/imu.o \
./src/led.o \
./src/main.o \
./src/radio.o \
./src/syscalls.o 

C_DEPS += \
./src/baro.d \
./src/gps.d \
./src/imu.d \
./src/led.d \
./src/main.d \
./src/radio.d \
./src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32 -DSTM32F105RCTx -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_CL -I"C:/Users/Ryan/workspace/avionics/inc" -I"C:/Users/Ryan/workspace/avionics/CMSIS/core" -I"C:/Users/Ryan/workspace/avionics/CMSIS/device" -I"C:/Users/Ryan/workspace/avionics/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


