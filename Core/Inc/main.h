/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


#include "stm32l1xx_hal.h"
#include "../../User/matric_button/lkv_matrix_button.h"

#define ENABLE			1
#define	DISABLE			2

#define DATA_Pin       GPIO_PIN_2
#define DATA_GPIO_Port GPIOC
#define CLK_Pin        GPIO_PIN_3
#define CLK_GPIO_Port  GPIOC


extern volatile uint32_t g_sys_time;

extern uint8_t buff_rx ;
extern uint8_t buff_rx_mqtt ;


extern uint8_t ring_buffer[1024] ;
extern volatile uint16_t front_index;
extern volatile uint16_t rear_index;
extern uint8_t process_buffer[64];
extern uint16_t volatile process_index;
extern uint8_t buff_tx[32];

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart2;




#endif /* __MAIN_H */
