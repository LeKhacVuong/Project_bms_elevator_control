################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/step_motor/step_motor.c 

OBJS += \
./User/step_motor/step_motor.o 

C_DEPS += \
./User/step_motor/step_motor.d 


# Each subdirectory must supply rules for building sources it contributes
User/step_motor/%.o User/step_motor/%.su User/step_motor/%.cyclo: ../User/step_motor/%.c User/step_motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/last_try/User/board" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/last_try/User/matric_button" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/last_try/User/LCD" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/last_try/User/modbus_rtu_server" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/last_try/User/step_motor" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/last_try/User/logger" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-2f-step_motor

clean-User-2f-step_motor:
	-$(RM) ./User/step_motor/step_motor.cyclo ./User/step_motor/step_motor.d ./User/step_motor/step_motor.o ./User/step_motor/step_motor.su

.PHONY: clean-User-2f-step_motor

