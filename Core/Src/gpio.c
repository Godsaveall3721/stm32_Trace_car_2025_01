/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  
  HAL_GPIO_WritePin(GPIOC, Tring_Pin|Motor_direction_1_1_Pin|Motor_direction_1_2_Pin|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Motor_direction_4_1_Pin|Motor_direction_4_2_Pin|Motor_direction_3_1_Pin|Motor_direction_3_2_Pin
                          |Motor_direction_2_1_Pin|Motor_direction_2_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Echo_Pin */
  GPIO_InitStruct.Pin = Echo_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Echo_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Tring_Pin */
  GPIO_InitStruct.Pin = Tring_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Tring_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : gray_scale_4_Pin gray_scale_5_Pin gray_scale_7_Pin gray_scale_right_Pin
                           gray_scale_left_Pin */
  GPIO_InitStruct.Pin = gray_scale_4_Pin|gray_scale_5_Pin|gray_scale_7_Pin|gray_scale_right_Pin
                          |gray_scale_left_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : gray_scale_3_Pin gray_scale_6_Pin */
  GPIO_InitStruct.Pin = gray_scale_3_Pin|gray_scale_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : gray_scale_2_Pin gray_scale_1_Pin gray_scale_8_Pin */
  GPIO_InitStruct.Pin = gray_scale_2_Pin|gray_scale_1_Pin|gray_scale_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Motor_direction_4_1_Pin Motor_direction_4_2_Pin Motor_direction_3_1_Pin Motor_direction_3_2_Pin
                           Motor_direction_2_1_Pin Motor_direction_2_2_Pin */
  GPIO_InitStruct.Pin = Motor_direction_4_1_Pin|Motor_direction_4_2_Pin|Motor_direction_3_1_Pin|Motor_direction_3_2_Pin
                          |Motor_direction_2_1_Pin|Motor_direction_2_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Motor_direction_1_1_Pin */
  GPIO_InitStruct.Pin = Motor_direction_1_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Motor_direction_1_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Motor_direction_1_2_Pin */
  GPIO_InitStruct.Pin = Motor_direction_1_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Motor_direction_1_2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
