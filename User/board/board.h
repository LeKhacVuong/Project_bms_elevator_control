/*
 * board.h
 *
 *  Created on: Oct 24, 2023
 *      Author: vypa0
 */

#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

#include "stm32l1xx_hal.h"
#include <string.h>

#define SENSOR_1_PIN   GPIO_PIN_1
#define SENSOR_1_PORT  GPIOH


#define SENSOR_2_PIN   GPIO_PIN_15
#define SENSOR_2_PORT  GPIOC

#define SENSOR_3_PIN   GPIO_PIN_13
#define SENSOR_3_PORT  GPIOC

#define SENSOR_4_PIN   GPIO_PIN_5
#define SENSOR_4_PORT  GPIOE

#define SENSOR_5_PIN   GPIO_PIN_3
#define SENSOR_5_PORT  GPIOE


#define SENSOR_6_PIN   GPIO_PIN_1
#define SENSOR_6_PORT  GPIOE


#define SS0     HAL_GPIO_ReadPin(SENSOR_1_PORT, SENSOR_1_PIN)
#define SS1_2   HAL_GPIO_ReadPin(SENSOR_2_PORT, SENSOR_2_PIN)
#define SS2_3   HAL_GPIO_ReadPin(SENSOR_3_PORT, SENSOR_3_PIN)
#define SS3_4   HAL_GPIO_ReadPin(SENSOR_4_PORT, SENSOR_4_PIN)
#define SS4_A   HAL_GPIO_ReadPin(SENSOR_5_PORT, SENSOR_5_PIN)
#define SS4_B   HAL_GPIO_ReadPin(SENSOR_6_PORT, SENSOR_6_PIN)


#define ON  1
#define OFF 0


void Error_Handler(void);
void board_init(void);

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;
extern volatile uint32_t g_sys_time;
extern uint8_t buff_rx;

extern uint8_t buff_mqtt_slave[32];
extern uint8_t mqtt_index;
extern uint8_t buff_rx_mqtt;
extern uint8_t is_new_linux_msg;


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

typedef enum{
	PROCESS,
	STOP,
	WAIT_USER,
	ERROR_SST
}STATUC_T;

typedef enum{
	LEVEL_1     = 10,
	LEVEL_1_2   = 15,
	LEVEL_2     = 20,
	LEVEL_2_3   = 25,
	LEVEL_3     = 30,
	LEVEL_3_4   = 35,
	LEVEL_4     = 40,
	LEVEL_ERROR = 0
}LEVEL_T;


#endif /* BOARD_BOARD_H_ */
