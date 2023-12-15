################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/matric_button/lkv_matrix_button.c 

OBJS += \
./board/matric_button/lkv_matrix_button.o 

C_DEPS += \
./board/matric_button/lkv_matrix_button.d 


# Each subdirectory must supply rules for building sources it contributes
board/matric_button/%.o board/matric_button/%.su board/matric_button/%.cyclo: ../board/matric_button/%.c board/matric_button/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"/home/lekhacvuong/Project_bms_elevator_control/Core/Inc" -I"/home/lekhacvuong/Project_bms_elevator_control/board/matric_button" -I"/home/lekhacvuong/Project_bms_elevator_control/board/modbus_rtu_server" -I"/home/lekhacvuong/Project_bms_elevator_control/board/step_motor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-board-2f-matric_button

clean-board-2f-matric_button:
	-$(RM) ./board/matric_button/lkv_matrix_button.cyclo ./board/matric_button/lkv_matrix_button.d ./board/matric_button/lkv_matrix_button.o ./board/matric_button/lkv_matrix_button.su

.PHONY: clean-board-2f-matric_button

