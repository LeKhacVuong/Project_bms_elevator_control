################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/board/board.c 

OBJS += \
./User/board/board.o 

C_DEPS += \
./User/board/board.d 


# Each subdirectory must supply rules for building sources it contributes
User/board/%.o User/board/%.su User/board/%.cyclo: ../User/board/%.c User/board/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/board" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/TM1637" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-board

clean-User-2f-board:
	-$(RM) ./User/board/board.cyclo ./User/board/board.d ./User/board/board.o ./User/board/board.su

.PHONY: clean-User-2f-board

