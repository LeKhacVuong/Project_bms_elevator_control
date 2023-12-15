################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/hc_05_master/hc_05.c 

OBJS += \
./User/hc_05_master/hc_05.o 

C_DEPS += \
./User/hc_05_master/hc_05.d 


# Each subdirectory must supply rules for building sources it contributes
User/hc_05_master/%.o User/hc_05_master/%.su User/hc_05_master/%.cyclo: ../User/hc_05_master/%.c User/hc_05_master/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/board" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/hc_05_master" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/LCD" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/logger" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/matric_button" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/modbus_rtu_server" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/scheduler" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/step_motor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-hc_05_master

clean-User-2f-hc_05_master:
	-$(RM) ./User/hc_05_master/hc_05.cyclo ./User/hc_05_master/hc_05.d ./User/hc_05_master/hc_05.o ./User/hc_05_master/hc_05.su

.PHONY: clean-User-2f-hc_05_master

