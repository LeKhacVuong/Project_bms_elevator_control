/*
 *  Master HC05 Project
 *  by Le Khac Vuong
 *
 */
#include <lkv_matrix_button.h>
#include "board.h"
#include "modbus_server.h"
#include "lkv_logger.h"
#include "step_motor.h"
#include "lkv_sch_task.h"
#define TAG "main.c"


uint8_t user_char = 0;
nmbs_t nmbs;
STATUC_T status_cabin = 0;

uint8_t current_level = LEVEL_2;
uint8_t target_level = LEVEL_2;

LEVEL_T get_current_level(void);

uint8_t ss_arr[6];

void lkv_bsp_log_output(const char* data){
//	HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen(data), 100);
//	HAL_UART_Transmit(&huart1, (uint8_t*)'\n', 1, 100);
}


void GPIO_sensor(void){

	 __HAL_RCC_GPIOF_CLK_ENABLE();

	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	  GPIO_InitStruct.Pin = SENSOR_1_PIN;
	  HAL_GPIO_Init(SENSOR_1_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SENSOR_2_PIN;
	  HAL_GPIO_Init(SENSOR_2_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SENSOR_3_PIN;
	  HAL_GPIO_Init(SENSOR_3_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SENSOR_4_PIN;
	  HAL_GPIO_Init(SENSOR_4_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SENSOR_5_PIN;
	  HAL_GPIO_Init(SENSOR_5_PORT, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SENSOR_6_PIN;
	  HAL_GPIO_Init(SENSOR_6_PORT, &GPIO_InitStruct);

}

int main(void)
{

	  board_init();
	  lkv_stepmotor_gpio_init();
	  mqtt_index = 0;

	  nmbs_platform_conf platform_conf;
	  platform_conf.transport = NMBS_TRANSPORT_RTU;
	  platform_conf.read = read_serial;
	  platform_conf.write = write_serial;
	  platform_conf.arg = NULL;

	  nmbs_callbacks callbacks = {0};
	  callbacks.read_coils = handle_read_coils;
	  callbacks.write_multiple_coils = handle_write_multiple_coils;
	  callbacks.read_holding_registers = handler_read_holding_registers;
	  callbacks.write_multiple_registers = handle_write_multiple_registers;
	  callbacks.write_single_register = handle_write_single_registers;
	  callbacks.read_input_registers = handler_read_input_registers;
	  nmbs_error err = nmbs_server_create(&nmbs, RTU_SERVER_ADDRESS, &platform_conf, &callbacks);
	  if (err != NMBS_ERROR_NONE) {
	    onError();
	  }
	  nmbs_set_read_timeout(&nmbs, 50);
	  nmbs_set_byte_timeout(&nmbs, 50);

	  lkv_logger_init(lkv_bsp_log_output, LOG_LEVEL_DEBUG);

	  LOG_INF(TAG, "Start run");
	  is_new_linux_msg =  1;

  while (1)
  {
	  nmbs_server_poll(&nmbs);
	  if(is_new_linux_msg){
		  if(buff_mqtt_slave[0] == 'T'){
			  HAL_UART_Transmit(&huart1, (uint8_t*)"OK\n", strlen("OK\n"), 100);
			  lkv_lcd_process(CLEAR_DIS, 1, 1,(char*)(buff_mqtt_slave+1));
		  }
		  if(buff_mqtt_slave[0] == 'C'){
			  target_level = buff_mqtt_slave[1];
		  }
		  if(buff_mqtt_slave[0] == 'S'){
			  status_cabin = buff_mqtt_slave[1];
		  }
		  is_new_linux_msg = 0;
		  memset(buff_mqtt_slave,0,32);
	  }

	  while(target_level != current_level){
		  while(target_level > current_level){
			  lkv_stepmotor_process(STEP_DIR_UP, 5, 1);
		  }
		  while(target_level < current_level){
			  lkv_stepmotor_process(STEP_DIR_DOWN, 5, 1);
		  }
	  }
  }
}


void SysTick_Handler(void)
{
	g_sys_time++;
  HAL_IncTick();
  current_level = get_current_level();
}


void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}


void USART3_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart3);
	HAL_UART_Receive_IT(&huart3, &buff_rx, 1);
	ring_buffer[front_index] = buff_rx;
	front_index++;
	if(front_index >= 1024){
		front_index = 0;
	}
}



void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
	HAL_UART_Receive_IT(&huart1, &buff_rx_mqtt, 1);

	if(buff_rx_mqtt == '*'){
		mqtt_index = 0;
	} else if(buff_rx_mqtt == ';'){
		buff_mqtt_slave[mqtt_index] = '\0';
		is_new_linux_msg = 1;
	}else{
		buff_mqtt_slave[mqtt_index] = buff_rx_mqtt;
		mqtt_index++;
		if(mqtt_index >= 32){
			mqtt_index = 0;
		}
	}
}


LEVEL_T get_current_level(void){

	ss_arr[0] = SS0;
	ss_arr[1] = SS1_2;
	ss_arr[2] = SS2_3;
	ss_arr[3] = SS3_4;
	ss_arr[4] = SS4_A;
	ss_arr[5] = SS4_B;


	if((SS4_B == ON) || (SS4_A == ON)){
		return LEVEL_4;
	}

	if(SS0 == ON){
		return LEVEL_1;
	}

	if((SS1_2 == ON) && (SS2_3 == OFF) ){
		return LEVEL_1_2;
	}

	if((SS1_2 == ON) && (SS2_3 == ON) ){
		return LEVEL_2;
	}

	if((SS2_3 == ON) && (SS3_4 == OFF) ){
		return LEVEL_2_3;
	}

	if((SS2_3 == ON) && (SS3_4 == ON) ){
		return LEVEL_3;
	}

	if((SS3_4 == ON) && (SS4_A == OFF) ){
		return LEVEL_4;
	}

	if((SS3_4 == ON) && (SS4_B == OFF)){
		return LEVEL_4;
	}

	return LEVEL_ERROR;

}






