/*
 * step_motor.c
 *
 * author: le khac vuong
 *
 */

#include "../../User/step_motor/step_motor.h"

#define DRIVER_PIN_1_PORT    GPIOA
#define DRIVER_PIN_1         GPIO_PIN_10

#define DRIVER_PIN_2_PORT    GPIOB
#define DRIVER_PIN_2         GPIO_PIN_3

#define DRIVER_PIN_3_PORT    GPIOB
#define DRIVER_PIN_3         GPIO_PIN_5

#define DRIVER_PIN_4_PORT    GPIOB
#define DRIVER_PIN_4         GPIO_PIN_4


void lkv_stepmotor_coil_setval(uint8_t _valin1, uint8_t _valin2, uint8_t _valin3, uint8_t _valin4){
	HAL_GPIO_WritePin(DRIVER_PIN_1_PORT, DRIVER_PIN_1, _valin1);
	HAL_GPIO_WritePin(DRIVER_PIN_2_PORT, DRIVER_PIN_2, _valin2);
	HAL_GPIO_WritePin(DRIVER_PIN_3_PORT, DRIVER_PIN_3, _valin3);
	HAL_GPIO_WritePin(DRIVER_PIN_4_PORT, DRIVER_PIN_4, _valin4);
}


void lkv_stepmotor_run_up(uint32_t _speed){
	lkv_stepmotor_coil_setval(1,0,0,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(1,1,0,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,1,0,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,1,1,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,0,1,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,0,1,1);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,0,0,1);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(1,0,0,1);
}


void lkv_stepmotor_run_down(uint32_t _speed){
	lkv_stepmotor_coil_setval(0,0,0,1);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,0,1,1);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,0,1,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,1,1,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(0,1,0,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(1,1,0,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(1,0,0,0);
	for(int i = 0; i < _speed; i ++);
	lkv_stepmotor_coil_setval(1,0,0,1);
}




void lkv_stepmotor_gpio_init(void){

	/* enable GPIO LCD PORTs clock */

	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();

	/* enable GPIO LCD PINs */

	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	  GPIO_InitStruct.Pin = DRIVER_PIN_1;
	  HAL_GPIO_Init(DRIVER_PIN_1_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = DRIVER_PIN_2;
	  HAL_GPIO_Init(DRIVER_PIN_2_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = DRIVER_PIN_3;
	  HAL_GPIO_Init(DRIVER_PIN_3_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = DRIVER_PIN_4;
	  HAL_GPIO_Init(DRIVER_PIN_4_PORT, &GPIO_InitStruct);

}




void lkv_stepmotor_process(uint8_t _direction, uint32_t _speed, uint32_t _number_step){

	if(_direction == STEP_DIR_DOWN){

		for(int i = 0; i < _number_step; i++){
			lkv_stepmotor_run_down(_speed);
		}

		return;
	}

	if(_direction == STEP_DIR_UP){
		for(int i = 0; i < _number_step; i++){
			lkv_stepmotor_run_up(_speed);
		}
		return;
	}

	if(_direction == STEP_STOP){
		lkv_stepmotor_coil_setval(0,0,0,0);
	}


return;
}






