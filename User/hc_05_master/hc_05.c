/*
 * hc_05.c
 *
 *  Created on: Oct 27, 2023
 *      Author: vypa0
 */

#include "hc_05.h"
#include "board.h"
uint32_t hc_05_timeout = 0;


void hc_05_init(void){

	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
	  HAL_Delay(50);

	  hc_05_timeout = g_sys_time + HC_05_TIMEOUT;
	  while((hc_05_master_process() != HC_05_SUCCESS) && (hc_05_timeout >= g_sys_time)){
		  HAL_UART_Transmit(&huart3, (uint8_t*)"AT\r\n", strlen("AT\r\n"), 1000);
		  HAL_Delay(50);
	  }
	  HAL_Delay(50);

	  hc_05_timeout = g_sys_time + HC_05_TIMEOUT;
	  while((hc_05_master_process() != HC_05_SUCCESS) && (hc_05_timeout >= g_sys_time)){
		  HAL_UART_Transmit(&huart3, (uint8_t*)"AT+UART=38400,0,0\r\n", strlen("AT+UART=38400,0,0\r\n"), 1000);
		  HAL_Delay(50);
	  }
	  HAL_Delay(50);

	  hc_05_timeout = g_sys_time + HC_05_TIMEOUT;
	  while((hc_05_master_process() != HC_05_SUCCESS) && (hc_05_timeout >= g_sys_time)){
		  HAL_UART_Transmit(&huart3, (uint8_t*)"AT+ROLE=1\r\n", strlen("AT+ROLE=1\r\n"), 1000);
		  HAL_Delay(50);
	  }
	  HAL_Delay(50);

	  hc_05_timeout = g_sys_time + HC_05_TIMEOUT;
	  while((hc_05_master_process() != HC_05_SUCCESS) && (hc_05_timeout >= g_sys_time)){
		  HAL_UART_Transmit(&huart3, (uint8_t*)"AT+LINK=<address>\r\n", strlen("AT+LINK=<address>\r\n"), 1000);
		  HAL_Delay(50);
	  }
	  HAL_Delay(50);

	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 0);
}


HC_05_STATUS_T hc_05_master_process(void){
	while(rear_index != front_index){
		process_buffer[process_index] = ring_buffer[rear_index];
		rear_index++;
		if(rear_index >= 1024){
			rear_index = 0;
		}
		process_index++;
		if(process_buffer[process_index - 1] == '\n'){
			if(process_buffer[process_index - 2] == '\t'){
				if((process_buffer[0] == 'O') && (process_buffer[1] == 'K')){
					process_index = 0;
					return HC_05_SUCCESS;
				}
			}
			process_index = 0;
			return HC_05_FAIL;
		}
	}
	return HC_05_WAIT;
}




