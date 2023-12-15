/*
 * my_matrix_button.c
 *
 *  Created on: Oct 24, 2023
 *      Author: vypa0
 */

#include "../../User/matric_button/lkv_matrix_button.h"

void matrix_init(void){
	 __HAL_RCC_GPIOC_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	  GPIO_InitStruct.Pin = GPIO_PIN_6;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_7;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_6;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_7;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;


	  GPIO_InitStruct.Pin = GPIO_PIN_9;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_8;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_10;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


uint8_t get_row(void){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 1 ){
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 1) return 1;
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 1 ){
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 1) return 2;
	}
	else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 1 ){
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 1) return 3;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) == 1 ){
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) == 1) return 4;
	}


	return 0;

}

void set_colum(uint8_t id){
	switch(id){
	case 1:
		for(int i = 0; i < 50; i++);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);
		for(int i = 0; i < 50; i++);
		break;

	case 2:
		for(int i = 0; i < 50; i++);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);
		for(int i = 0; i < 50; i++);
		break;

	case 3:
		for(int i = 0; i < 50; i++);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
		for(int i = 0; i < 50; i++);
		break;

	default:
		break;
	}
}



 uint8_t get_char_user_polling(void){

	 uint8_t num = 0;

	 while(num == 0){
		 set_colum(1);
			 if(get_row() == 1){
				 num = '1';
				 return num;
			 }
			 if(get_row() == 2){
				 num = '4';
				 return num;
			 }
			 if(get_row() == 3){
				 num = '7';
				 return num;
			 }
			 if(get_row() == 4){
				 num = '*';
				 return num;
			 }

		 set_colum(2);
			 if(get_row() == 1){
				 num = '2';
				 return num;
			 }
			 if(get_row() == 2){
				 num = '5';
				 return num;
			 }
			 if(get_row() == 3){
				 num = '8';
				 return num;
			 }
			 if(get_row() == 4){
				 num = '0';
				 return num;
			 }


		 set_colum(3);
			 if(get_row() == 1){
				 num = '3';
				 return num;
			 }
			 if(get_row() == 2){
				 num = '6';
				 return num;
			 }
			 if(get_row() == 3){
				 num = '9';
				 return num;
			 }
			 if(get_row() == 4){
				 num = '#';
				 return num;
			 }

	 }

	 return num;
}


 uint8_t get_char_user(void){

	 uint8_t num = 0;

	        set_colum(1);
	 			 if(get_row() == 1){
	 				 num = '1';
	 				 return num;
	 			 }
	 			 if(get_row() == 2){
	 				 num = '4';
	 				 return num;
	 			 }
	 			 if(get_row() == 3){
	 				 num = '7';
	 				 return num;
	 			 }


	 		 set_colum(2);
	 			 if(get_row() == 1){
	 				 num = '2';
	 				 return num;
	 			 }
	 			 if(get_row() == 2){
	 				 num = '5';
	 				 return num;
	 			 }
	 			 if(get_row() == 3){
	 				 num = '8';
	 				 return num;
	 			 }


	 		 set_colum(3);
	 			 if(get_row() == 1){
	 				 num = '3';
	 				 return num;
	 			 }
	 			 if(get_row() == 2){
	 				 num = '6';
	 				 return num;
	 			 }
	 			 if(get_row() == 3){
	 				 num = '9';
	 				 return num;
	 			 }


	 		 set_colum(4);
	 			 if(get_row() == 1){
	 				 num = 'A';
	 				 return num;
	 			 }
	 			 if(get_row() == 2){
	 				 num = 'B';
	 				 return num;
	 			 }
	 			 if(get_row() == 3){
	 				 num = '0';
	 				 return num;
	 			 }


	 		return 0;

 }




