/*
 * step_motor.h
 *
 * author: le khac vuong
 *
 */

#ifndef STEP_MOTOR_STEP_MOTOR_H_
#define STEP_MOTOR_STEP_MOTOR_H_
#include "stm32l1xx_hal.h"
#define STEP_DIR_UP     0
#define STEP_DIR_DOWN   1
#define FULL_CYCLE_STEP 512


void lkv_stepmotor_gpio_init(void);
void lkv_stepmotor_process(uint8_t _direction, uint32_t _speed, uint32_t _number_step);


#endif /* STEP_MOTOR_STEP_MOTOR_H_ */
