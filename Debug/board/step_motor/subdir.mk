################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/step_motor/step_motor.c 

OBJS += \
./board/step_motor/step_motor.o 

C_DEPS += \
./board/step_motor/step_motor.d 


# Each subdirectory must supply rules for building sources it contributes
board/step_motor/%.o board/step_motor/%.su board/step_motor/%.cyclo: ../board/step_motor/%.c board/step_motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"/home/lekhacvuong/Project_bms_elevator_control/Core/Inc" -I"/home/lekhacvuong/Project_bms_elevator_control/board/matric_button" -I"/home/lekhacvuong/Project_bms_elevator_control/board/modbus_rtu_server" -I"/home/lekhacvuong/Project_bms_elevator_control/board/step_motor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-board-2f-step_motor

clean-board-2f-step_motor:
	-$(RM) ./board/step_motor/step_motor.cyclo ./board/step_motor/step_motor.d ./board/step_motor/step_motor.o ./board/step_motor/step_motor.su

.PHONY: clean-board-2f-step_motor

