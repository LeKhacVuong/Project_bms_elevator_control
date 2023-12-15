################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/scheduler/lkv_sch_task.c 

OBJS += \
./User/scheduler/lkv_sch_task.o 

C_DEPS += \
./User/scheduler/lkv_sch_task.d 


# Each subdirectory must supply rules for building sources it contributes
User/scheduler/%.o User/scheduler/%.su User/scheduler/%.cyclo: ../User/scheduler/%.c User/scheduler/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/board" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/hc_05_master" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/LCD" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/logger" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/matric_button" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/modbus_rtu_server" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/scheduler" -I"C:/Users/vypa0/STM32CubeIDE/do_an_wp/bms_l152/User/step_motor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-scheduler

clean-User-2f-scheduler:
	-$(RM) ./User/scheduler/lkv_sch_task.cyclo ./User/scheduler/lkv_sch_task.d ./User/scheduler/lkv_sch_task.o ./User/scheduler/lkv_sch_task.su

.PHONY: clean-User-2f-scheduler

