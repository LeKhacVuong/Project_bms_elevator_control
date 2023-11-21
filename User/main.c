/*
 *  Master HC05 Project
 *  by Le Khac Vuong
 *
 */

#include <lkv_lcd.h>
#include <lkv_matrix_button.h>
#include "board.h"
#include "modbus_server.h"
#include "sm_logger.h"
#include "step_motor.h"



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
    PC2     -> DATA_5
    PA1     -> DATA_6
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



 */

void sm_bsp_log_output(const char* data){



}


int main(void)
{

	  board_init();
	  lkv_stepmotor_gpio_init();
	  lkv_lcd_init();

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
	  nmbs_set_read_timeout(&nmbs, 1000);
	  nmbs_set_byte_timeout(&nmbs, 100);

	  sm_logger_init(sm_bsp_log_output, LOG_LEVEL_DEBUG);



  while (1)
  {
	  nmbs_server_poll(&nmbs);
	  lkv_lcd_process(CLEAR_DIS, 1, 1, "LE KHAC VUONG");
  }
}


void SysTick_Handler(void)
{
	g_sys_time++;
  HAL_IncTick();
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











