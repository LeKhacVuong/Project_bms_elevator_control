/*
 * board.c
 *
 *  Created on: Dec 14, 2023
 *      Author: lekhacvuong
 */

#include "board.h"
#include "main.h"
#include "stm32l1xx_hal.h"

#define SENSOR_1_PIN   GPIO_PIN_0
#define SENSOR_1_PORT  GPIOC


#define SENSOR_2_PIN   GPIO_PIN_1
#define SENSOR_2_PORT  GPIOC

#define SENSOR_3_PIN   GPIO_PIN_0
#define SENSOR_3_PORT  GPIOB

#define SENSOR_4_PIN   GPIO_PIN_4
#define SENSOR_4_PORT  GPIOA

#define SENSOR_5_PIN   GPIO_PIN_1
#define SENSOR_5_PORT  GPIOA


#define SENSOR_6_PIN   GPIO_PIN_0
#define SENSOR_6_PORT  GPIOA


#define SS0     HAL_GPIO_ReadPin(SENSOR_1_PORT, SENSOR_1_PIN)
#define SS1_2   HAL_GPIO_ReadPin(SENSOR_2_PORT, SENSOR_2_PIN)
#define SS2_3   HAL_GPIO_ReadPin(SENSOR_3_PORT, SENSOR_3_PIN)
#define SS3_4   HAL_GPIO_ReadPin(SENSOR_4_PORT, SENSOR_4_PIN)
#define SS4_A   HAL_GPIO_ReadPin(SENSOR_5_PORT, SENSOR_5_PIN)
#define SS4_B   HAL_GPIO_ReadPin(SENSOR_6_PORT, SENSOR_6_PIN)


#define ON  0
#define OFF 1


UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;

uint8_t ss_arr[6];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART4_Init(void);
static void MX_USART2_UART_Init(void);
void Error_Handler(void);
void led_7_segment_init(void);

void led_7_segment_init(void){
	  __HAL_RCC_GPIOB_CLK_ENABLE();


	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	  GPIO_InitStruct.Pin = DATA_Pin;
	  HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = CLK_Pin;
	  HAL_GPIO_Init(CLK_GPIO_Port, &GPIO_InitStruct);


	  HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}


void GPIO_sensor_init(void){

	 __HAL_RCC_GPIOC_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();

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
		return LEVEL_3_4;
	}

	if((SS3_4 == ON) && (SS4_B == OFF)){
		return LEVEL_4;
	}

	return LEVEL_ERROR;

}

void board_init(void){
	  HAL_Init();
	  SystemClock_Config();
	  MX_GPIO_Init();
	  MX_UART4_Init();
	  MX_USART2_UART_Init();
	  HAL_UART_Receive_IT(&huart2, &buff_rx, 1);
	  HAL_UART_Receive_IT(&huart4, &buff_rx_mqtt, 1);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_UART4_Init(void)
{


  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }


}


static void MX_USART2_UART_Init(void)
{


  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }


}


static void MX_GPIO_Init(void)
{

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();


  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }

}
