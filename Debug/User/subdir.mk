################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/main.c 

OBJS += \
./User/main.o 

C_DEPS += \
./User/main.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o User/%.su User/%.cyclo: ../User/%.c User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/step_motor" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/logger" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/LCD" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/matric_button" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/board" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/modbus_rtu_server" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/main.cyclo ./User/main.d ./User/main.o ./User/main.su

.PHONY: clean-User

