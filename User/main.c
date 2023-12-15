
#include "main.h"

#include "../User/modbus_rtu_server/modbus_server.h"
#include "../User/step_motor/step_motor.h"
#include "board.h"



uint8_t user_char = 0;
nmbs_t nmbs;
STATUC_T status_cabin = 0;

uint8_t mqtt_index = 0;
uint8_t is_new_linux_msg = 0;

uint8_t current_level = LEVEL_2;
uint8_t target_level = LEVEL_2;

volatile uint32_t g_sys_time = 0;
uint8_t buff_rx = 0;
uint8_t ring_buffer[1024] = {0};
volatile uint16_t front_index = 0;
volatile uint16_t rear_index = 0;
uint8_t process_buffer[64] = {0};
uint16_t volatile process_index = 0;
uint8_t buff_tx[32] = {0};




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
  nmbs_set_read_timeout(&nmbs, 10);
  nmbs_set_byte_timeout(&nmbs, 50);

  target_level = LEVEL_1;

  while (1)
  {

	  nmbs_server_poll(&nmbs);

	  user_char = get_char_user();
	  if((user_char >= '1') && (user_char <= '4')){
		  target_level = (user_char - '0') * 10;
	  }

	  while(target_level != current_level){
		  if(target_level > current_level){
			  lkv_stepmotor_process(STEP_DIR_DOWN, 130, 1);
		  }
		  if(target_level < current_level){
			  lkv_stepmotor_process(STEP_DIR_UP, 130, 1);
		  }
		  if(target_level == current_level){
			  break;
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
}



