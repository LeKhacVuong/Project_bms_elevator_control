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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/board" -I"/home/lekhacvuong/Desktop/Project_bms_elevator_control/User/TM1637" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-step_motor

clean-User-2f-step_motor:
	-$(RM) ./User/step_motor/step_motor.cyclo ./User/step_motor/step_motor.d ./User/step_motor/step_motor.o ./User/step_motor/step_motor.su

.PHONY: clean-User-2f-step_motor

