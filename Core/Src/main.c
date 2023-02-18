/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
unsigned char recive_packet[470];
int i=0;//recived packet index
int hh,mm,ss;//hour //minute//secend
int xkoft,ykoft;

int latitude_decimal[2];

long int latitude_float[7];
int latitude_decimal_number;
char latitude_decimal_char[2];//******

long int latitude_float_number;
uint8_t latitude_float_number_int;

char latitude_float_char[5];//******

// int latitude_float_number_final;

char longitude_decimal[2];
long int longitude_float[7];
int longitude_decimal_number;
char longtitude_decimal_char[2];//******

long int longitude_float_number;
uint8_t longitude_float_number_int;

char longtitude_float_char[5]; //******

char darage='°';
char cot[1]="'";


int neo_flag=0;
int data_omet_flag=0;
int cntlz=0x1a;
int enter=0x0d;
char phone_number[21];
char sms_string[]="https://www.google.com/maps/place/35%C2%B044'49.0%22N+51%C2%B032'29.2%22E/";
char sms_char[50];
char sms_char1[100];

int lot1000,lod1000,lat1000,lad1000;
int sms_sender_flag=0;
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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	phone_number[0]='A';
	phone_number[1]='T';
	phone_number[2]='+';
	phone_number[3]='C';
	phone_number[4]='M';
	phone_number[5]='G';
	phone_number[6]='S';
	phone_number[7]='=';
	phone_number[8]='"';
	phone_number[9]='0';
	phone_number[10]='9';
	phone_number[11]='3';
	phone_number[12]='8';	
	phone_number[13]='2';
	phone_number[14]='0';
	phone_number[15]='3';
	phone_number[16]='5';
	phone_number[17]='1';
	phone_number[18]='2';
	phone_number[19]='1';
	phone_number[20]='"';
	//sprintf(phone_number,'AT+CMGS="%s"','09382035121');
	HAL_UART_Receive_IT(&huart1,(unsigned char*)&recive_packet,470);
	////////////////////////////////////////////////////////////////////////////////////
	
	
	HAL_UART_Transmit(&huart1,(unsigned char*)&("AT+CMGF=1"),9,800);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(enter),1,800);

	HAL_Delay(1000);
	HAL_UART_Transmit(&huart1,(unsigned char*)&(phone_number),21,800);
		HAL_UART_Transmit(&huart1,(uint8_t*)&(enter),1,800);

	HAL_Delay(1000);
	HAL_UART_Transmit(&huart1,(unsigned char*)&("sim800l is here :)"),18,800);
		HAL_UART_Transmit(&huart1,(uint8_t*)&(enter),1,800);

	HAL_Delay(1000);
	HAL_UART_Transmit(&huart1,(uint8_t*)&cntlz,1,800);
	
	
	///////////////////////////////////////////////////////////////////////////////////////////
  while (1)
  {
	//https://www.google.com/maps/place/35%C2%B044'49.0%22N+51%C2%B032'29.2%22E/
	//35°44'48.6"N 51°32'29.4"E 
	
		if (neo_flag==1){
			neo_flag=0;
		for(int i;i<=419;i++)//469
		{
		
			if(recive_packet[i]=='$' && recive_packet[i+1]=='G' &&  recive_packet[i+2]=='P' && recive_packet[i+3]=='R'
						&& recive_packet[i+4]=='M'&& recive_packet[i+5]=='C' && i<350)
						{
							data_omet_flag=1;
								hh=((recive_packet[i+7]-0x30)*10) +recive_packet[i+8]-0x30 ;
								mm=((recive_packet[i+9]-0x30)*10) +recive_packet[i+10]-0x30;
								ss=((recive_packet[i+11]-0x30)*10)+recive_packet[i+12]-0x30;
								xkoft=(recive_packet[i+12]-0x30);
								//ykoft=recive_packet[i+20]-0x30;
							
								latitude_decimal[0]=(recive_packet[i+19]-0x30)*10;
								latitude_decimal[1]=(recive_packet[i+20]-0x30);
								latitude_decimal_number=latitude_decimal[0]+latitude_decimal[1];
							
							latitude_decimal_char[0]=recive_packet[i+19];
							latitude_decimal_char[1]=recive_packet[i+20];
							
							
							
								latitude_float[0]=(recive_packet[i+21]-0x30)*16666;
								latitude_float_char[0]=latitude_float[0];
							
								latitude_float[1]=(recive_packet[i+22]-0x30)*1666;
								latitude_float_char[1]=latitude_float[1];
								
								latitude_float[2]=(recive_packet[i+24]-0x30)*166;		
								latitude_float_char[2]=latitude_float[2];
								
								latitude_float[3]=(recive_packet[i+25]-0x30)*16;
								latitude_float_char[3]=latitude_float[3];
								
								latitude_float[4]=(recive_packet[i+26]-0x30);
								latitude_float_char[4]=latitude_float[4];
								

								latitude_float_number=(latitude_float[0]+latitude_float[1]+latitude_float[2]+latitude_float[3]+latitude_float[4]);//+latitude_float[5]+latitude_float[6]);
								
							
								longitude_decimal[0]=(recive_packet[i+33]-0x30)*10;
								longitude_decimal[1]=(recive_packet[i+34]-0x30);
								longitude_decimal_number=longitude_decimal[0]+longitude_decimal[1];
								longtitude_decimal_char[0]=recive_packet[i+33];
								longtitude_decimal_char[1]=recive_packet[i+34];
							
								longitude_float[0]=(recive_packet[i+35]-0x30)*16666;
								latitude_float_char[0]=longitude_float[0]+0x30;
								
								longitude_float[1]=(recive_packet[i+36]-0x30)*1666;
								latitude_float_char[1]=longitude_float[1]+0x30;

								
								longitude_float[2]=(recive_packet[i+38]-0x30)*166;
								latitude_float_char[2]=longitude_float[2]+0x30;
								
								longitude_float[3]=(recive_packet[i+39]-0x30)*16;
								latitude_float_char[3]=longitude_float[3]+0x30;
								
								longitude_float[4]=(recive_packet[i+40]-0x30);
								latitude_float_char[4]=longitude_float[4]+0x30;
								//longitude_float[5]=(recive_packet[i+41]-0x30)*10/60;
							//	longitude_float[6]=(recive_packet[i+42]-0x30)/60;
							latitude_float_number_int=latitude_float_number;
							longitude_float_number_int=longitude_float_number;



								longitude_float_number=(longitude_float[0]+longitude_float[1]+longitude_float[2]+longitude_float[3]+longitude_float[4]);//+longitude_float[5]+longitude_float[6]);
						}
		}
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		HAL_UART_Receive_IT(&huart1,(unsigned char*)&recive_packet,470);
}
		lat1000=latitude_float_number/1000;
		lad1000=latitude_float_number%1000;
		lot1000=longitude_float_number/1000;
		lod1000=longitude_float_number%1000;
if(mm%29==28){sms_sender_flag=1;}
		if(neo_flag==0 && xkoft!=0 && data_omet_flag==1 &&latitude_decimal_number>0 && longitude_decimal_number>0 &&lat1000>0 &&lot1000>0&& mm%29==0 && sms_sender_flag==1)
		{	sms_sender_flag=0;
			//str=x+y;//("https://www.google.com/maps/place/%d%%C2%%B0%d'49.0%%22N+51%%C2%%B032'29.2%%22E");
			
			HAL_UART_Transmit(&huart1,(unsigned char*)&("AT+CMGF=1"),9,800);
			HAL_UART_Transmit(&huart1,(uint8_t*)&(enter),1,800);

			HAL_Delay(1000);
			HAL_UART_Transmit(&huart1,(unsigned char*)&(phone_number),21,800);
			HAL_UART_Transmit(&huart1,(uint8_t*)&(enter),1,800);

			HAL_Delay(1000);

			sprintf(sms_char,"%d.%d%d,%d.%d%d",latitude_decimal_number,lat1000,lad1000,longitude_decimal_number,lot1000,lod1000);
			HAL_UART_Transmit(&huart1,(uint8_t*)&sms_char,17,800);
	
			HAL_Delay(500);
			HAL_UART_Transmit(&huart1,(uint8_t*)&cntlz,1,800);
			HAL_UART_Transmit(&huart1,(uint8_t*)&(enter),1,800);

			HAL_Delay(500);

			
			data_omet_flag=0;
			HAL_Delay(500);

		}
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
