################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/modbus_rtu_server/modbus_server.c \
../board/modbus_rtu_server/nanomodbus.c 

OBJS += \
./board/modbus_rtu_server/modbus_server.o \
./board/modbus_rtu_server/nanomodbus.o 

C_DEPS += \
./board/modbus_rtu_server/modbus_server.d \
./board/modbus_rtu_server/nanomodbus.d 


# Each subdirectory must supply rules for building sources it contributes
board/modbus_rtu_server/%.o board/modbus_rtu_server/%.su board/modbus_rtu_server/%.cyclo: ../board/modbus_rtu_server/%.c board/modbus_rtu_server/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"/home/lekhacvuong/Project_bms_elevator_control/Core/Inc" -I"/home/lekhacvuong/Project_bms_elevator_control/board/matric_button" -I"/home/lekhacvuong/Project_bms_elevator_control/board/modbus_rtu_server" -I"/home/lekhacvuong/Project_bms_elevator_control/board/step_motor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-board-2f-modbus_rtu_server

clean-board-2f-modbus_rtu_server:
	-$(RM) ./board/modbus_rtu_server/modbus_server.cyclo ./board/modbus_rtu_server/modbus_server.d ./board/modbus_rtu_server/modbus_server.o ./board/modbus_rtu_server/modbus_server.su ./board/modbus_rtu_server/nanomodbus.cyclo ./board/modbus_rtu_server/nanomodbus.d ./board/modbus_rtu_server/nanomodbus.o ./board/modbus_rtu_server/nanomodbus.su

.PHONY: clean-board-2f-modbus_rtu_server

