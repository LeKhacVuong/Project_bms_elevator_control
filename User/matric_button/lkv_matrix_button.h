/*
 * my_matrix_button.h
 *
 *  Created on: Oct 24, 2023
 *      Author: vypa0
 */

#ifndef MATRIC_BUTTON_LKV_MATRIX_BUTTON_H_
#define MATRIC_BUTTON_LKV_MATRIX_BUTTON_H_

#include "stm32f4xx_hal.h"
#include "../../User/board/board.h"



void set_colum(uint8_t id);
uint8_t get_row(void);
uint8_t get_char_user_polling(void);
uint8_t get_char_user(void);







#endif /* MATRIC_BUTTON_LKV_MATRIX_BUTTON_H_ */
