################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/displayDriver.c \
../Src/filter.c \
../Src/gpio.c \
../Src/interrupts.c \
../Src/ledFunctions.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/system_stm32f0xx.c \
../Src/tim.c 

S_UPPER_SRCS += \
../Src/ledDriver.S 

OBJS += \
./Src/adc.o \
./Src/displayDriver.o \
./Src/filter.o \
./Src/gpio.o \
./Src/interrupts.o \
./Src/ledDriver.o \
./Src/ledFunctions.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/system_stm32f0xx.o \
./Src/tim.o 

S_UPPER_DEPS += \
./Src/ledDriver.d 

C_DEPS += \
./Src/adc.d \
./Src/displayDriver.d \
./Src/filter.d \
./Src/gpio.d \
./Src/interrupts.d \
./Src/ledFunctions.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/system_stm32f0xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32F051x8 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Inc" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32F051x8 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Inc" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"C:/Users/Cody Mann/git/ECE362_MiniProject/MiniProjectDraft2/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


