################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/matric_button/lkv_matrix_button.c 

OBJS += \
./User/matric_button/lkv_matrix_button.o 

C_DEPS += \
./User/matric_button/lkv_matrix_button.d 


# Each subdirectory must supply rules for building sources it contributes
User/matric_button/%.o User/matric_button/%.su User/matric_button/%.cyclo: ../User/matric_button/%.c User/matric_button/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/step_motor" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/logger" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/LCD" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/matric_button" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/board" -I"C:/Users/vypa0/Desktop/lkv_github/Project_bms_elevator_control/User/modbus_rtu_server" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-2f-matric_button

clean-User-2f-matric_button:
	-$(RM) ./User/matric_button/lkv_matrix_button.cyclo ./User/matric_button/lkv_matrix_button.d ./User/matric_button/lkv_matrix_button.o ./User/matric_button/lkv_matrix_button.su

.PHONY: clean-User-2f-matric_button

