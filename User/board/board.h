/*
 * board.h
 *
 *  Created on: Oct 24, 2023
 *      Author: vypa0
 */

#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

#include "stm32f4xx_hal.h"
#include <string.h>

void SystemClock_Config(void);
 void MX_GPIO_Init(void);
 void MX_USART3_UART_Init(void);
 void MX_SPI1_Init(void);
void Error_Handler(void);
void board_init(void);

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;
extern volatile uint32_t g_sys_time;
extern uint8_t buff_rx;


extern uint8_t ring_buffer[1024];
extern volatile uint16_t front_index;
extern volatile uint16_t rear_index;
extern uint8_t process_buffer[64];
extern volatile uint16_t process_index;
extern uint8_t buff_tx[32];


typedef enum{
	HC_05_WAIT,
	HC_05_SUCCESS,
	HC_05_FAIL
}HC_05_STATUS_T;



#endif /* BOARD_BOARD_H_ */
