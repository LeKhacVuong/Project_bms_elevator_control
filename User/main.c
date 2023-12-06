/*
 *  Master HC05 Project
 *  by Le Khac Vuong
 *
 */

#include <lkv_lcd.h>
#include <lkv_matrix_button.h>
#include "board.h"
#include "modbus_server.h"
#include "lkv_logger.h"
#include "step_motor.h"
#include "lkv_sch_task.h"
#define TAG "main.c"


uint8_t user_char = 0;
nmbs_t nmbs;

/*
    Module Rs485:

    PB10     -> USART3_TX
    PB11     -> USART3_RX
    5V consum


    Module LCD:

    PC0      -> RS
    PC2      -> RW
    PA0      -> EN
    PC1      -> DATA_4
    PC2      -> DATA_5
    PA1      -> DATA_6
    PA3      -> DATA_7
    GND      -> BLK, VO, GND
    3.3V     -> BLA
    5V       -> VDD

    Module StepMotor:

    PH0      -> IN_1
    PC14     -> IN_2
    PE6      -> IN_3
    PE4      -> IN_4
    5V consum


    MQTT_Clien/debug com
    PB6       -> USART1_TX
    PB7       -> USART1_RX


 */

void lkv_bsp_log_output(const char* data){
//	HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen(data), 100);
//	HAL_UART_Transmit(&huart1, (uint8_t*)'\n', 1, 100);
}


int main(void)
{

	  board_init();
	  lkv_stepmotor_gpio_init();
	  lkv_lcd_init();

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
	  // Create the modbus server
	  nmbs_error err = nmbs_server_create(&nmbs, RTU_SERVER_ADDRESS, &platform_conf, &callbacks);
	  if (err != NMBS_ERROR_NONE) {
	    onError();
	  }
	  nmbs_set_read_timeout(&nmbs, 50);
	  nmbs_set_byte_timeout(&nmbs, 50);

	  lkv_logger_init(lkv_bsp_log_output, LOG_LEVEL_DEBUG);

	  LOG_INF(TAG, "Start run");







  while (1)
  {
	  nmbs_server_poll(&nmbs);
	  if(is_new_linux_msg){

		  if(buff_mqtt_slave[0] == 'T'){
			  HAL_UART_Transmit(&huart1, (uint8_t*)"OK\n", strlen("OK\n"), 100);
			  lkv_lcd_process(CLEAR_DIS, 1, 1,(char*)(buff_mqtt_slave+1));
		  }

		  is_new_linux_msg = 0;

	  }

  }
}


void SysTick_Handler(void)
{
	g_sys_time++;
  HAL_IncTick();
//  if(g_sys_time % 5000 == 0){
//	  HAL_UART_Transmit(&huart1, (uint8_t*)"*D2L6C2;\n", strlen("*D2L6C2;\n"), 100);
//  }


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







