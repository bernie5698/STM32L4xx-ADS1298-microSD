/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "fatfs.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "fatfs_sd.h"
#include "ff_gen_drv.h"
#include "ADS1298.h"
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
uint8_t ADS_TX_Buffer[27000] = {0};	// dummy data
uint8_t ADS_RX_Buffer[54000] = {0};
uint8_t *ADS_head = ADS_RX_Buffer;
uint8_t *ADS_mid = ADS_RX_Buffer + 27000;
uint8_t *ADS_tail = ADS_RX_Buffer + 54000;
extern uint16_t sample_cnt;
volatile uint8_t SD_WRITE_STATE = 0;  // 0: idle, 1: write first half buffer, 2: write second half buffer

RTC_TimeTypeDef TimeInfo;
RTC_DateTypeDef DateInfo;

FRESULT fres;
FATFS fs;	// file system object
FIL fil;	// pointer to file object
UINT bw;	// pointer to the variable to return number of bytes written
char FileName[20];
char FolderName[20];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void send_uart(char* str){
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void SD_ErrorMessage(FRESULT fres) {
	switch(fres) {
		case FR_OK:
			send_uart("Success");
		case FR_DISK_ERR:
			send_uart("A hard error occurred in the low level disk I/O layer");
			break;
		case FR_INT_ERR:
			send_uart("Assertion failed");
			break;
		case FR_NOT_READY:
			send_uart("The physical drive cannot work");
			break;
		case FR_NO_FILE:
			send_uart("Could not find the file");
			break;
		case FR_NO_PATH:
			send_uart("Could not find the path");
			break;
		case FR_INVALID_NAME:
			send_uart("The path name format is invalid");
			break;
		case FR_DENIED:
			send_uart("Access denied due to prohibited access or directory full");
			break;
		case FR_EXIST:
			send_uart("Access denied due to prohibited access");
			break;
		case FR_INVALID_OBJECT:
			send_uart("The file/directory object is invalid");
			break;
		case FR_WRITE_PROTECTED:
			send_uart("The physical drive is write protected");
			break;
		case FR_INVALID_DRIVE:
			send_uart("The logical drive number is invalid");
			break;
		case FR_NOT_ENABLED:
			send_uart("The volume has no work area");
			break;
		case FR_NO_FILESYSTEM:
			send_uart("There is no valid FAT volume");
			break;
		case FR_MKFS_ABORTED:
			send_uart("The f_mkfs() aborted due to any problem");
			break;
		case FR_TIMEOUT:
			send_uart("Could not get a grant to access the volume within defined period");
			break;
		case FR_LOCKED:
			send_uart("The operation is rejected according to the file sharing policy");
			break;
		case FR_NOT_ENOUGH_CORE:
			send_uart("LFN working buffer could not be allocated");
			break;
		case FR_TOO_MANY_OPEN_FILES:
			send_uart("Number of open files > _FS_LOCK");
			break;
		case FR_INVALID_PARAMETER:
			send_uart("Given parameter is invalid");
			break;
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
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	
	/****************************** MicroSD ******************************/
	/* Mount File System */
	fres = f_mount(&fs, "", 1);
//	if(fres != FR_OK) SD_ErrorMessage(fres);
//	else send_uart("SD CARD mounted successfully...\r\n");
	
	/* Make Directory */
	sprintf(FolderName, "20%02d.%02d.%02d", DateInfo.Year, DateInfo.Month, DateInfo.Date);
	fres = f_mkdir(FolderName);
//	if (fres != FR_OK) SD_ErrorMessage(fres);
//	else send_uart("Make Directory: Done...\n");

	/* Change Directory */
	fres = f_chdir(FolderName);
//	if (fres != FR_OK) SD_ErrorMessage(fres);
//	else send_uart("Change Path: Done...\n");
	/*********************************************************************/
	
	/*************** ADS1298 ***************/
	ADS_Init();
	ADS_Data_Receive();
	/***************************************/
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if (SD_WRITE_STATE == 1) {
			HAL_RTC_GetTime(&hrtc, &TimeInfo, RTC_FORMAT_BIN);
			sprintf(FileName, "ECGPCG_%02d%02d.%02d.txt", TimeInfo.Hours, TimeInfo.Minutes, TimeInfo.Seconds);
			fres = f_open(&fil, FileName, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			fres = f_lseek(&fil, f_size(&fil));
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			fres = f_write(&fil, ADS_RX_Buffer, 27000, &bw);
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			fres = f_close(&fil);
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			
			SD_WRITE_STATE = 0;
		}
		if (SD_WRITE_STATE == 2) {
			fres = f_open(&fil, FileName, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			fres = f_lseek(&fil, f_size(&fil));
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			fres = f_write(&fil, ADS_mid, 27000, &bw);
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			fres = f_close(&fil);
//			if (fres != FR_OK) SD_ErrorMessage(fres);
			
			SD_WRITE_STATE = 0;
		}
		if (sample_cnt == 5000) {
			send_uart("Done");
			ADS_Start(LOW);
			ADS_ChipSelect(HIGH);
			sample_cnt--;
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
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
