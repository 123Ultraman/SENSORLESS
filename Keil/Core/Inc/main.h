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
#define KEY_Pin GPIO_PIN_13
#define KEY_GPIO_Port GPIOC
#define KEY_EXTI_IRQn EXTI15_10_IRQn
#define CURRENT_C_Pin GPIO_PIN_0
#define CURRENT_C_GPIO_Port GPIOC
#define CURRENT_B_Pin GPIO_PIN_1
#define CURRENT_B_GPIO_Port GPIOC
#define TEMP_Pin GPIO_PIN_2
#define TEMP_GPIO_Port GPIOC
#define CURRENT_A_Pin GPIO_PIN_0
#define CURRENT_A_GPIO_Port GPIOA
#define VBUS_Pin GPIO_PIN_1
#define VBUS_GPIO_Port GPIOA
#define L6230_EN_Pin GPIO_PIN_6
#define L6230_EN_GPIO_Port GPIOA
#define SPEED_Pin GPIO_PIN_1
#define SPEED_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define HALL_C_Pin GPIO_PIN_10
#define HALL_C_GPIO_Port GPIOB
#define PWM_A_Pin GPIO_PIN_8
#define PWM_A_GPIO_Port GPIOA
#define PWM_B_Pin GPIO_PIN_9
#define PWM_B_GPIO_Port GPIOA
#define PWM_C_Pin GPIO_PIN_10
#define PWM_C_GPIO_Port GPIOA
#define Fault_Pin GPIO_PIN_11
#define Fault_GPIO_Port GPIOA
#define HALL_A_Pin GPIO_PIN_15
#define HALL_A_GPIO_Port GPIOA
#define PWM_EN_A_Pin GPIO_PIN_10
#define PWM_EN_A_GPIO_Port GPIOC
#define PWM_EN_B_Pin GPIO_PIN_11
#define PWM_EN_B_GPIO_Port GPIOC
#define PWM_EN_C_Pin GPIO_PIN_12
#define PWM_EN_C_GPIO_Port GPIOC
#define HALL_B_Pin GPIO_PIN_3
#define HALL_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
