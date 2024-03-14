/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define ENCA_Pin GPIO_PIN_0
#define ENCA_GPIO_Port GPIOC
#define ENCB_Pin GPIO_PIN_1
#define ENCB_GPIO_Port GPIOC
#define ENCZ_Pin GPIO_PIN_2
#define ENCZ_GPIO_Port GPIOC
#define BUTTON_MODE_Pin GPIO_PIN_3
#define BUTTON_MODE_GPIO_Port GPIOC
#define BUTTON_MODE_EXTI_IRQn EXTI3_IRQn
#define LPUART1_TX_Pin GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define BUTTON_UP_DOWN_Pin GPIO_PIN_5
#define BUTTON_UP_DOWN_GPIO_Port GPIOC
#define BUTTON_UP_DOWN_EXTI_IRQn EXTI9_5_IRQn
#define LED_M3_Pin GPIO_PIN_10
#define LED_M3_GPIO_Port GPIOB
#define LED_S2_Pin GPIO_PIN_11
#define LED_S2_GPIO_Port GPIOB
#define BUTTON_SPEED_Pin GPIO_PIN_6
#define BUTTON_SPEED_GPIO_Port GPIOC
#define BUTTON_SPEED_EXTI_IRQn EXTI9_5_IRQn
#define BUTTON_START_Pin GPIO_PIN_7
#define BUTTON_START_GPIO_Port GPIOC
#define BUTTON_START_EXTI_IRQn EXTI9_5_IRQn
#define LED_S1_Pin GPIO_PIN_10
#define LED_S1_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define LED_S3_Pin GPIO_PIN_2
#define LED_S3_GPIO_Port GPIOD
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define BUTTON_HALL_Pin GPIO_PIN_4
#define BUTTON_HALL_GPIO_Port GPIOB
#define BUTTON_HALL_EXTI_IRQn EXTI4_IRQn
#define LED_M1_Pin GPIO_PIN_8
#define LED_M1_GPIO_Port GPIOB
#define LED_M2_Pin GPIO_PIN_9
#define LED_M2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
