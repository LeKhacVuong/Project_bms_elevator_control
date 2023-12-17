/*
 * natrix_button.h
 *
 * author: le khac vuong
 *
 */

#ifndef MATRIC_BUTTON_LKV_MATRIX_BUTTON_H_
#define MATRIC_BUTTON_LKV_MATRIX_BUTTON_H_

#include "stm32l1xx_hal.h"


void matrix_init(void);
void set_colum(uint8_t id);
uint8_t get_row(void);
uint8_t get_char_user_polling(void);
uint8_t get_char_user(void);

#endif /* MATRIC_BUTTON_LKV_MATRIX_BUTTON_H_ */
