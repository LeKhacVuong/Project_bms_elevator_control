/*
 * my_matrix_button.c
 *
 *  Created on: Oct 24, 2023
 *      Author: vypa0
 */

#include <lkv_matrix_button.h>

uint8_t get_row(void){
	if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1 ){
		HAL_Delay(50);
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1) return 1;

	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == 1 ){
		HAL_Delay(50);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == 1) return 2;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == 1 ){
		HAL_Delay(50);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == 1) return 3;
	}


	return 0;

}

void set_colum(uint8_t id){

	switch(id){
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,  0);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,  0);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,  1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,  0);
		break;

	case 4:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,  0);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,  1);
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




