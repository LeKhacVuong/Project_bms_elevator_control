################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/logger/lkv_logger.c 

OBJS += \
./User/logger/lkv_logger.o 

C_DEPS += \
./User/logger/lkv_logger.d 


# Each subdirectory must supply rules for building sources it contributes
User/logger/%.o User/logger/%.su User/logger/%.cyclo: ../User/logger/%.c User/logger/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/step_motor" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/logger" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/LCD" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/matric_button" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/board" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/modbus_rtu_server" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/scheduler" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-2f-logger

clean-User-2f-logger:
	-$(RM) ./User/logger/lkv_logger.cyclo ./User/logger/lkv_logger.d ./User/logger/lkv_logger.o ./User/logger/lkv_logger.su

.PHONY: clean-User-2f-logger

