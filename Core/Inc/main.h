/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADS_CLK_Pin GPIO_PIN_1
#define ADS_CLK_GPIO_Port GPIOA
#define ADS_CS_Pin GPIO_PIN_2
#define ADS_CS_GPIO_Port GPIOA
#define ADS_DRDY_Pin GPIO_PIN_3
#define ADS_DRDY_GPIO_Port GPIOA
#define ADS_DRDY_EXTI_IRQn EXTI3_IRQn
#define ADS_SCK_Pin GPIO_PIN_5
#define ADS_SCK_GPIO_Port GPIOA
#define ADS_MISO_Pin GPIO_PIN_6
#define ADS_MISO_GPIO_Port GPIOA
#define ADS_MOSI_Pin GPIO_PIN_7
#define ADS_MOSI_GPIO_Port GPIOA
#define ADS_PWDN_Pin GPIO_PIN_4
#define ADS_PWDN_GPIO_Port GPIOC
#define ADS_CLKSEL_Pin GPIO_PIN_5
#define ADS_CLKSEL_GPIO_Port GPIOC
#define LD2_GREEN_Pin GPIO_PIN_14
#define LD2_GREEN_GPIO_Port GPIOB
#define SYS_JTMS_SWDIO_Pin GPIO_PIN_13
#define SYS_JTMS_SWDIO_GPIO_Port GPIOA
#define SYS_JTCK_SWCLK_Pin GPIO_PIN_14
#define SYS_JTCK_SWCLK_GPIO_Port GPIOA
#define SD_SCK_Pin GPIO_PIN_1
#define SD_SCK_GPIO_Port GPIOD
#define SD_MISO_Pin GPIO_PIN_3
#define SD_MISO_GPIO_Port GPIOD
#define SD_MOSI_Pin GPIO_PIN_4
#define SD_MOSI_GPIO_Port GPIOD
#define SD_CS_Pin GPIO_PIN_5
#define SD_CS_GPIO_Port GPIOD
#define ST_LINK_UART1_TX_Pin GPIO_PIN_6
#define ST_LINK_UART1_TX_GPIO_Port GPIOB
#define ST_LINK_UART1_RX_Pin GPIO_PIN_7
#define ST_LINK_UART1_RX_GPIO_Port GPIOB
#define ADS_START_Pin GPIO_PIN_8
#define ADS_START_GPIO_Port GPIOB
#define ADS_RESET_Pin GPIO_PIN_9
#define ADS_RESET_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
