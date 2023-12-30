
#include "main.h"

#include "../User/modbus_rtu_server/modbus_server.h"
#include "../User/step_motor/step_motor.h"
#include "board.h"
#include "TM1637.h"

#define LED_DWN   0
#define LED_UP    1
#define LED_WAIT  3
#define LED_DONE1 4
#define LED_DONE2 5
#define LED_DONE3 6
#define LED_DONE4 7
#define LED_START 8
#define LED_START1 9
#define LED_START2 10
#define LED_START3 11
#define LED_START4 12

#define STEP_MOTOR_SPEED_NOR 130*20

#define BLINK_START 2
#define BLINK_DONE  1

#define WAIT_USER_ODER_TIMEOT 7000

#define LINUX_CMD_CURRENT_LEVEL 'C'

#define LINUX_CMD_CHANGE_LEVEL  'L'

#define LINUX_CMD_FIRE_LEVEL    'F'



nmbs_t nmbs;
nmbs_platform_conf platform_conf;
nmbs_callbacks callbacks = {0};


uint8_t user_char = 0;
STATUS_T status_cabin;

uint8_t mqtt_index = 0;
uint8_t is_new_linux_msg = 0;
uint32_t wait_timeot = 0;

uint8_t is_fire = 0;

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

void show_display(uint8_t _dir, uint8_t _level );
void elevator_process_force(uint32_t _speed);
void elevator_process_once(uint32_t _speed);
void linux_msg_prosess(void);
void modbus_sever_init(void);
void blink_led_delay(uint8_t type);
void send_msg_to_linux(uint8_t _cmd, uint8_t _value);




int main(void)
{
   board_init();
  matrix_init();
  GPIO_sensor_init();
  lkv_stepmotor_gpio_init();
  modbus_sever_init();

	current_level = get_current_level();

   if((current_level % 10) == 0){
	   target_level = current_level;
   }else{
	   target_level = current_level - 5;
   }

      elevator_process_force(STEP_MOTOR_SPEED_NOR);

	    blink_led_delay(BLINK_START);
		status_cabin = WAIT_USER_FIST_CALL;


  while (1)
  {
	  switch (status_cabin) {
	  case EMERGENCY_FIRE:
		  	break;
	  case WAIT_USER_FIST_CALL:
			break;
	  case RUN_TO_TAKE_USER:
			  if(target_level > current_level){
				  show_display(LED_UP, target_level/10);
			  }
			  if(target_level< current_level){
				  show_display(LED_DWN, target_level/10);
			  }
			elevator_process_force(STEP_MOTOR_SPEED_NOR);
			if((current_level == target_level) && (!is_fire)){
				status_cabin = WAIT_USER_ODER_CALL;
				wait_timeot = g_sys_time + WAIT_USER_ODER_TIMEOT;
				  show_display(LED_WAIT, target_level/10);
			}
			break;
	  case WAIT_USER_ODER_CALL:
			  if(wait_timeot < g_sys_time){
					status_cabin = WAIT_USER_FIST_CALL;
					  show_display(LED_START, target_level/10);
					  if(target_level_next_time != 0){
						  target_level = target_level_next_time;
						  target_level_next_time = 0;
					  }
			  }
			break;
	  case RUN_TO_USER_ODER:
			elevator_process_force(STEP_MOTOR_SPEED_NOR);
			if((current_level == target_level) && (!is_fire)){
				status_cabin = DONE_USER_ODER;
			}
			break;
	  case DONE_USER_ODER:
			blink_led_delay(BLINK_DONE);
			  if(target_level_next_time != 0){
				  target_level = target_level_next_time;
				  target_level_next_time = 0;
					status_cabin = RUN_TO_TAKE_USER;
			  }else{
					status_cabin = WAIT_USER_FIST_CALL;
					  show_display(LED_START, target_level/10);
			  }
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
  HAL_SYSTICK_IRQHandler();
  linux_msg_prosess();
  	  current_level = get_current_level();
  		  user_char = get_char_user();


  		  switch(status_cabin){
  		  case EMERGENCY_FIRE:
  			  	break;
		  case WAIT_USER_FIST_CALL:
			  if((user_char >= '1') && (user_char <= '4')){
				  while(get_char_user() != 0);
				  target_level = (user_char - '0') * 10;
				  if(target_level > current_level){
					  status_cabin = RUN_TO_TAKE_USER;
					  show_display(LED_UP, target_level/10);
				  }
				  else if(target_level< current_level){
					  status_cabin = RUN_TO_TAKE_USER;
					  show_display(LED_DWN, target_level/10);
				  }else{
					  status_cabin = RUN_TO_TAKE_USER;
					  show_display(LED_WAIT, target_level/10);
					  status_cabin = WAIT_USER_ODER_CALL;
					  wait_timeot = g_sys_time + WAIT_USER_ODER_TIMEOT;
				  }
			  }
			  break;
		  case RUN_TO_TAKE_USER:
			  if((user_char >= '1') && (user_char <= '4')){
				  if(!target_level_next_time){
					  target_level_next_time = (user_char - '0') * 10;
					  if(target_level > current_level){
						  show_display(LED_UP, target_level/10);
					  }
					  if(target_level< current_level){
						  show_display(LED_DWN, target_level/10);
					  }
				  }
			  }
			  break;
		  case WAIT_USER_ODER_CALL:

			  if((user_char >= '1') && (user_char <= '4')){
				  while(get_char_user() != 0);
				  target_level = (user_char - '0') * 10;

				  if(target_level > current_level){
					  status_cabin = RUN_TO_USER_ODER;
					  show_display(LED_UP, target_level/10);
				  }
				  else if(target_level< current_level){
					  status_cabin = RUN_TO_USER_ODER;
					  show_display(LED_DWN, target_level/10);
				  }else{
					  status_cabin = DONE_USER_ODER;
				  }
			  }
			  break;
		  case RUN_TO_USER_ODER:
			  if((user_char >= '1') && (user_char <= '4')){
				  if(!target_level_next_time){
					  target_level_next_time = (user_char - '0') * 10;
					  if(target_level > current_level){
						  show_display(LED_UP, target_level/10);
					  }
					  if(target_level< current_level){
						  show_display(LED_DWN, target_level/10);
					  }
				  }
			  }
			  break;
		  case DONE_USER_ODER:
			  if((user_char >= '1') && (user_char <= '4')){
				  if(!target_level_next_time){
					  target_level_next_time = (user_char - '0') * 10;
				  }
			  }
			  break;
		  default:
			  break;
		  }

  		  if((g_sys_time % 500) == 0){
  			send_msg_to_linux(LINUX_CMD_CURRENT_LEVEL, current_level);
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

void send_msg_to_linux(uint8_t _cmd, uint8_t _value){
	uint8_t msg_buff[16];
	msg_buff[0] = '*';
	msg_buff[1] = _cmd;
	msg_buff[2] = _value;
	msg_buff[3] = ';';
	msg_buff[4] = '\n';
	HAL_UART_Transmit(&huart4, msg_buff, 5, 1);
}

void blink_led_delay(uint8_t type){
    TM1637_SetBrightness(3);

    switch (type) {
		case BLINK_START:
			for(int i = 0; i < 6; i++){
				  show_display(LED_START1, target_level/10);
				  HAL_Delay(70);
				  show_display(LED_START2, target_level/10);
				  HAL_Delay(70);
				  show_display(LED_START3, target_level/10);
				  HAL_Delay(70);
				  show_display(LED_START4, target_level/10);
				  HAL_Delay(70);
			}
			TM1637_Display_4_char(0, 0, 0, 0, 1);
			HAL_Delay(200);
			TM1637_Display_4_char(20, 20, 20, 20, 0);
			HAL_Delay(200);
			TM1637_Display_4_char(0, 0, 0, 0, 1);
			HAL_Delay(200);
			TM1637_Display_4_char(20, 20, 20, 20, 0);
			HAL_Delay(200);
			TM1637_Display_4_char(0, 0, 0, 0, 1);
			HAL_Delay(200);
			TM1637_Display_4_char(20, 20, 20, 20, 0);
			HAL_Delay(200);
			TM1637_Display_4_char(0, 0, 0, 0, 1);
			HAL_Delay(200);
			TM1637_Display_4_char(20, 20, 20, 20, 0);
			HAL_Delay(200);
			TM1637_Display_4_char(0, 0, 0, 0, 1);
			HAL_Delay(200);
			TM1637_Display_4_char(20, 20, 20, 20, 0);
			HAL_Delay(700);
			show_display(LED_START, target_level/10);
			break;
		case BLINK_DONE:
			for(int i = 0; i < 15; i++){
				  show_display(LED_DONE1, target_level/10);
				  HAL_Delay(70);
				  show_display(LED_DONE2, target_level/10);
				  HAL_Delay(70);
				  show_display(LED_DONE3, target_level/10);
				  HAL_Delay(70);
				  show_display(LED_DONE4, target_level/10);
				  HAL_Delay(70);
			}
			break;
		default:
			break;
	}


}

void modbus_sever_init(void){
	  platform_conf.transport = NMBS_TRANSPORT_RTU;
	  platform_conf.read = read_serial;
	  platform_conf.write = write_serial;
	  platform_conf.arg = NULL;

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
}

void elevator_process_force(uint32_t _speed){
	  while((target_level != current_level)){
		  if(is_fire){
			  return;
		  }
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
		  if(buff_mqtt_slave[0] == LINUX_CMD_CHANGE_LEVEL){
			  if((buff_mqtt_slave[1] >= 1) && (buff_mqtt_slave[1] <= 4)){
				  target_level = buff_mqtt_slave[1] * 10;
				  status_cabin = RUN_TO_USER_ODER;
			  }
		  }
		  if(buff_mqtt_slave[0] == LINUX_CMD_FIRE_LEVEL){
			  is_fire = buff_mqtt_slave[1];
			  if(is_fire){
				  status_cabin = EMERGENCY_FIRE;
			  }else{
				  if(status_cabin == EMERGENCY_FIRE){
					  status_cabin = WAIT_USER_FIST_CALL;
				  }
			  }
		  }
		  is_new_linux_msg = 0;
		  memset(buff_mqtt_slave,0,32);
	  }
}

void show_display(uint8_t _dir, uint8_t _level ){
	uint8_t special_char = 19;
	if(!target_level_next_time){
		special_char = 20;
	}

	switch (_dir) {
		case LED_DWN:
			TM1637_Display_4_char(16, 13, special_char, _level, 1);
			break;
		case LED_UP:
			TM1637_Display_4_char(18, 17, special_char, _level, 1);
			break;
		case LED_WAIT:
			TM1637_Display_4_char(22, 22, special_char, _level, 1);
			break;
		case LED_DONE1:
			TM1637_Display_4_char(24, 23, special_char, _level, 1);
			break;
		case LED_DONE2:
			TM1637_Display_4_char(26, 25, special_char, _level, 1);
			break;
		case LED_DONE3:
			TM1637_Display_4_char(28, 27, special_char, _level, 1);
			break;
		case LED_DONE4:
			TM1637_Display_4_char(30, 29, special_char, _level, 1);
			break;
		case LED_START:
			TM1637_Display_4_char(19, 19, 20, current_level/10, 1);
			break;
		case LED_START1:
			TM1637_Display_4_char(24, 23, 24, 23, 0);
			break;
		case LED_START2:
			TM1637_Display_4_char(26, 25, 26, 25, 0);
			break;
		case LED_START3:
			TM1637_Display_4_char(28, 27, 28, 27, 0);
			break;
		case LED_START4:
			TM1637_Display_4_char(30, 29, 30, 29, 0);
			break;
		default:
			break;
	}
}


