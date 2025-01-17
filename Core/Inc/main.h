/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

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
#define Echo_Pin GPIO_PIN_0
#define Echo_GPIO_Port GPIOC
#define Echo_EXTI_IRQn EXTI0_IRQn
#define Tring_Pin GPIO_PIN_1
#define Tring_GPIO_Port GPIOC
#define LED_ON_Pin GPIO_PIN_13
#define LED_ON_GPIO_Port GPIOC
#define gray_scale_4_Pin GPIO_PIN_2
#define gray_scale_4_GPIO_Port GPIOC
#define gray_scale_5_Pin GPIO_PIN_3
#define gray_scale_5_GPIO_Port GPIOC
#define gray_scale_3_Pin GPIO_PIN_3
#define gray_scale_3_GPIO_Port GPIOA
#define gray_scale_6_Pin GPIO_PIN_4
#define gray_scale_6_GPIO_Port GPIOA
#define gray_scale_7_Pin GPIO_PIN_5
#define gray_scale_7_GPIO_Port GPIOC
#define gray_scale_2_Pin GPIO_PIN_0
#define gray_scale_2_GPIO_Port GPIOB
#define gray_scale_1_Pin GPIO_PIN_1
#define gray_scale_1_GPIO_Port GPIOB
#define gray_scale_8_Pin GPIO_PIN_2
#define gray_scale_8_GPIO_Port GPIOB
#define Motor_direction_4_1_Pin GPIO_PIN_10
#define Motor_direction_4_1_GPIO_Port GPIOB
#define Motor_direction_4_2_Pin GPIO_PIN_11
#define Motor_direction_4_2_GPIO_Port GPIOB
#define Motor_direction_3_1_Pin GPIO_PIN_12
#define Motor_direction_3_1_GPIO_Port GPIOB
#define Motor_direction_3_2_Pin GPIO_PIN_13
#define Motor_direction_3_2_GPIO_Port GPIOB
#define Motor_direction_2_1_Pin GPIO_PIN_14
#define Motor_direction_2_1_GPIO_Port GPIOB
#define Motor_direction_2_2_Pin GPIO_PIN_15
#define Motor_direction_2_2_GPIO_Port GPIOB
#define Motor_direction_1_1_Pin GPIO_PIN_8
#define Motor_direction_1_1_GPIO_Port GPIOC
#define Motor_direction_1_2_Pin GPIO_PIN_9
#define Motor_direction_1_2_GPIO_Port GPIOC
#define gray_scale_right_Pin GPIO_PIN_10
#define gray_scale_right_GPIO_Port GPIOC
#define gray_scale_left_Pin GPIO_PIN_11
#define gray_scale_left_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
