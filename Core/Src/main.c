/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MW_Control.h"
#include "bt_control.h"
#include "string.h"
#include "stdio.h"
#include "simpwm.h"
#include "pid.h"
#include "encoder.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char msg,temp[100];
Bt_Data_Typedef rx_data;
PWM_Typedef motorA1,motorA2,motorB1,motorB2;
int encoder;
ENC_Typedef encoderA1,encoderA2,encoderB1,encoderB2;
PID_Typedef pidA1,pidA2,pidB1,pidB2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	
	if(huart == BT_UART){
		if(BT_Read(msg, &rx_data)){
		//	char buffer[50];
		//	sprintf(buffer,"X%d,Y%d,Turn%d",rx_data.x,rx_data.y,rx_data.turn);
		//	HAL_UART_Transmit(&huart4,(uint8_t *)buffer,strlen(buffer),HAL_MAX_DELAY);
//			BT_Compute(&rx_data);
//			sprintf(temp,"%d,%d\n",rx_data.x,rx_data.y);
//			HAL_UART_Transmit_DMA(&huart4,(uint8_t *)temp,strlen(temp));
			MW_Control(rx_data);
		}
		HAL_UART_Receive_DMA(BT_UART,(uint8_t *)&msg,1);

	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim7){
		ENC_Get(&encoderA1);
		ENC_Get(&encoderA2);
		ENC_Get(&encoderB1);
		ENC_Get(&encoderB2);
		if(encoderA1.encoder > 30000) encoderA1.encoder = encoderA1.encoder - 65535;
		if(encoderA2.encoder > 30000) encoderA2.encoder = encoderA2.encoder - 65535;
		if(encoderB1.encoder > 30000) encoderB1.encoder = encoderB1.encoder - 65535;
		if(encoderB2.encoder > 30000) encoderB2.encoder = encoderB2.encoder - 65535;
		__HAL_TIM_SET_COUNTER(encoderA1.enc_tim,0);
		__HAL_TIM_SET_COUNTER(encoderA2.enc_tim,0);
		__HAL_TIM_SET_COUNTER(encoderB1.enc_tim,0);
		__HAL_TIM_SET_COUNTER(encoderB2.enc_tim,0);
		encoderA1.speed = encoderA1.encoder * 100.0f * 60 /1560.0f;
		encoderA2.speed = encoderA2.encoder * 100.0f * 60 /1560.0f;
		encoderB1.speed = encoderB1.encoder * 100.0f * 60 /1560.0f;
		encoderB2.speed = encoderB2.encoder * 100.0f * 60 /1560.0f;
		encoderA1.encoder = 0;
		encoderA2.encoder = 0;
		encoderB1.encoder = 0;
		encoderB2.encoder = 0;
		PID_Compute(&pidA1,encoderA1.speed);
		PID_Compute(&pidA2,encoderA2.speed);
		PID_Compute(&pidB1,encoderB1.speed);
		PID_Compute(&pidB2,encoderB2.speed);
		
		if(pidA1.output > 0) SIMPWM_SET_CRR(&motorA1,pidA1.output,0);
		else SIMPWM_SET_CRR(&motorA1,0,-pidA1.output);
		
		if(pidA2.output >= 0) SIMPWM_SET_CRR(&motorA2,pidA2.output,0);
		else SIMPWM_SET_CRR(&motorA2,0,-pidA2.output);
		
		if(pidB1.output >= 0) SIMPWM_SET_CRR(&motorB1,pidB1.output,0);
		else SIMPWM_SET_CRR(&motorB1,0,-pidB1.output);
		
		if(pidB2.output >= 0) SIMPWM_SET_CRR(&motorB2,pidB2.output,0);
		else SIMPWM_SET_CRR(&motorB2,0,-pidB2.output);
		
		sprintf(temp,"%.2f,%.2f,%.2f\n",encoderA1.speed,pidA1.setpoint,pidA2.integral);
		HAL_UART_Transmit_DMA(&huart4,(uint8_t *)temp,strlen(temp));
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM15_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM17_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	//MW_Init();
	char a[] = "Hello"; 
	HAL_UART_Transmit(&huart4,(uint8_t *)a,strlen(a),HAL_MAX_DELAY);
	BT_Init();
	ENC_Init(&encoderA1,&htim1);
	ENC_Init(&encoderA2,&htim4);
	ENC_Init(&encoderB1,&htim3);
	ENC_Init(&encoderB2,&htim2);
	PID_Init(&pidA1,27.f,0.f,0.f,0.01f,1000.f,999.f);
	PID_Init(&pidA2,10.f,0.f,0.f,0.01f,700.f,999.f);
	PID_Init(&pidB1,0.f,0.f,0.f,0.01f,700.f,999.f);
	PID_Init(&pidB2,0.f,0.f,0.f,0.01f,700.f,999.f);
	HAL_TIM_Base_Start_IT(&htim7);
	SIMPWM_Init(&motorA1,0,0,GPIOB,GPIO_PIN_14,GPIOB,GPIO_PIN_15);
	SIMPWM_Init(&motorA2,0,0,GPIOB,GPIO_PIN_9,GPIOB,GPIO_PIN_8);
	SIMPWM_Init(&motorB1,0,0,GPIOB,GPIO_PIN_0,GPIOB,GPIO_PIN_1);
	SIMPWM_Init(&motorB2,0,0,GPIOA,GPIO_PIN_2,GPIOA,GPIO_PIN_3);
//	__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN1,50);
//	__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN2,50);
	HAL_UART_Receive_DMA(BT_UART,(uint8_t *)&msg,1);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		SIMPWM_Run(&motorA1,__HAL_TIM_GET_COUNTER(&htim6));
		SIMPWM_Run(&motorA2,__HAL_TIM_GET_COUNTER(&htim6));
		SIMPWM_Run(&motorB1,__HAL_TIM_GET_COUNTER(&htim6));
		SIMPWM_Run(&motorB2,__HAL_TIM_GET_COUNTER(&htim6));
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
