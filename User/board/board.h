/*
 * board.h
 *
 *  Created on: Dec 14, 2023
 *      Author: lekhacvuong
 */

#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

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



void GPIO_sensor_init(void);
LEVEL_T get_current_level(void);
void board_init(void);



#endif /* BOARD_BOARD_H_ */
