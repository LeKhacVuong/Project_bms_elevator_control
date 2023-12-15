
#include "main.h"

#include "../User/modbus_rtu_server/modbus_server.h"
#include "../User/step_motor/step_motor.h"
#include "board.h"
#include "TM1637.h"



uint8_t user_char = 0;
nmbs_t nmbs;
STATUS_T status_cabin;

uint8_t mqtt_index = 0;
uint8_t is_new_linux_msg = 0;

uint8_t current_level;
uint8_t target_level_next_time;
uint8_t target_level;


uint8_t buff_mqtt_slave[32];

volatile uint32_t g_sys_time = 0;
uint8_t buff_rx = 0;
uint8_t buff_rx_mqtt = 0;
uint8_t ring_buffer[1024] = {0};
volatile uint16_t front_index = 0;
volatile uint16_t rear_index = 0;
uint8_t process_buffer[64] = {0};
uint16_t volatile process_index = 0;
uint8_t buff_tx[32] = {0};

void elevator_process_force(uint32_t _speed){
	  while(target_level != current_level){
		  if(target_level > current_level){
			  lkv_stepmotor_process(STEP_DIR_DOWN, _speed, 1);
		  }
		  if(target_level < current_level){
			  lkv_stepmotor_process(STEP_DIR_UP, _speed, 1);
		  }
		  if(target_level == current_level){
			  return;
		  }
	  }
}

void elevator_process_once(uint32_t _speed){
	  if(target_level != current_level){
		  if(target_level > current_level){
			  lkv_stepmotor_process(STEP_DIR_DOWN, _speed, 1);
		  }
		  if(target_level < current_level){
			  lkv_stepmotor_process(STEP_DIR_UP, _speed, 1);
		  }
		  if(target_level == current_level){
			  return;
		  }
	  }
}

void linux_msg_prosess(void){
	  if(is_new_linux_msg){
		  if(buff_mqtt_slave[0] == 'T'){
			  if((buff_mqtt_slave[1] > '0') && (buff_mqtt_slave[1] < '9')){
				  uint32_t real_time = buff_mqtt_slave[1]*1000 + buff_mqtt_slave[2]*100 + buff_mqtt_slave[4]*10 + buff_mqtt_slave[5];
				  TM1637_DisplayDecimal(real_time, 1);
			  }
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
}

void show_dis_dir(uint8_t _dir, uint8_t _level ){

	if(_dir == 0){
		TM1637_Display_4_char(16, 13, 20, _level, 1);
	}else{
		TM1637_Display_4_char(18, 17, 20, _level, 1);
	}
}

int main(void)
{

   board_init();
  matrix_init();
  GPIO_sensor_init();
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
  nmbs_set_read_timeout(&nmbs, 5);
  nmbs_set_byte_timeout(&nmbs, 50);

	current_level = get_current_level();

   if((current_level % 10) == 0){
	   target_level = current_level;
   }else{
	   target_level = current_level - 5;
   }

      elevator_process_force(130 * 25);
	  is_new_linux_msg = 1;
	  linux_msg_prosess();
	  status_cabin = WAIT_USER_FIST_CALL;

	    TM1637_SetBrightness(2);

		TM1637_Display_4_char(19, 20, 19, 19, 0);


  while (1)
  {
	  switch (status_cabin) {
		case WAIT_USER_FIST_CALL:
			if(target_level != current_level){
				status_cabin = RUN_TO_TAKE_USER;
			}
			break;
		case RUN_TO_TAKE_USER:
			  if(target_level > current_level){
				  status_cabin = RUN_TO_TAKE_USER;
				  show_dis_dir(1, target_level/10);
			  }

			  if(target_level< current_level){
				  status_cabin = RUN_TO_TAKE_USER;
				  show_dis_dir(0, target_level/10);
			  }
			elevator_process_force(130 * 25);
			if(current_level == target_level){
				status_cabin = WAIT_USER_ODER_CALL;
			}
			break;

		case WAIT_USER_ODER_CALL:
			break;
		case RUN_TO_USER_ODER:
			  if(target_level > current_level){
				  status_cabin = RUN_TO_TAKE_USER;
				  show_dis_dir(1, target_level/10);
			  }

			  if(target_level< current_level){
				  status_cabin = RUN_TO_TAKE_USER;
				  show_dis_dir(0, target_level/10);
			  }
			elevator_process_force(130 * 25);
			if(current_level == target_level){
				status_cabin = DONE_USER_ODER;
			}
			break;
		case DONE_USER_ODER:
			HAL_Delay(5000);
			  if(target_level_next_time != 0){
				  target_level = target_level_next_time;
				  target_level_next_time = 0;
			  }
			status_cabin = WAIT_USER_FIST_CALL;
			break;

		default:

			break;
	}
  }
}

void SysTick_Handler(void)
{
	g_sys_time = g_sys_time + 10;
  HAL_IncTick();
  current_level = get_current_level();
  		  user_char = get_char_user();


		  switch(status_cabin){
		  case WAIT_USER_FIST_CALL:
			  if((user_char >= '1') && (user_char <= '4')){
				  while(get_char_user() != 0);
				  target_level = (user_char - '0') * 10;
				  if(target_level > current_level){
					  status_cabin = RUN_TO_TAKE_USER;
					  show_dis_dir(1, target_level/10);
				  }

				  if(target_level< current_level){
					  status_cabin = RUN_TO_TAKE_USER;
					  show_dis_dir(0, target_level/10);
				  }

			  }
			  break;
		  case RUN_TO_TAKE_USER:
			  if((user_char >= '1') && (user_char <= '4')){
				  target_level_next_time = (user_char - '0') * 10;
			  }
			  break;

		  case WAIT_USER_ODER_CALL:
			  if((user_char >= '1') && (user_char <= '4')){
				  while(get_char_user() != 0);
				  target_level = (user_char - '0') * 10;
				  status_cabin = RUN_TO_USER_ODER;
			  }
			  break;
		  case RUN_TO_USER_ODER:
			  if((user_char >= '1') && (user_char <= '4')){
				  target_level_next_time = (user_char - '0') * 10;
			  }
			  break;
		  case DONE_USER_ODER:

			  break;

		  default:
			  break;
		  }



}

void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart2);
	HAL_UART_Receive_IT(&huart2, &buff_rx, 1);
	ring_buffer[front_index] = buff_rx;
	front_index++;
	if(front_index >= 1024){
		front_index = 0;
	}

}

void UART4_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart4);

  HAL_UART_Receive_IT(&huart4, &buff_rx_mqtt, 1);

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



