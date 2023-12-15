/*
 * board.h
 *
 *  Created on: Dec 14, 2023
 *      Author: lekhacvuong
 */

#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

#define BLUE  0
#define RED   1
#define GREEN 2

#include "main.h"

typedef enum{
	LEVEL_1     = 10,
	LEVEL_1_2   = 15,
	LEVEL_2     = 20,
	LEVEL_2_3   = 25,
	LEVEL_3     = 30,
	LEVEL_3_4   = 35,
	LEVEL_4     = 40,
	LEVEL_ERROR = 99
}LEVEL_T;

typedef enum{
	WAIT_USER_FIST_CALL,
	RUN_TO_TAKE_USER,
	WAIT_USER_ODER_CALL,
	RUN_TO_USER_ODER,
	DONE_USER_ODER
}STATUS_T;


void GPIO_sensor_init(void);
LEVEL_T get_current_level(void);
void board_init(void);
void set_rgb_color(uint8_t color);


#endif /* BOARD_BOARD_H_ */
