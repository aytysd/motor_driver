/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart2;
extern TIM_OC_InitTypeDef sConfigOC;
extern TIM_HandleTypeDef htim1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint8_t Rxdata[2];
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define EN_A_Pin GPIO_PIN_1
#define EN_A_GPIO_Port GPIOA
#define EN_A_EXTI_IRQn EXTI1_IRQn
#define EN_B_Pin GPIO_PIN_3
#define EN_B_GPIO_Port GPIOA
#define EN_B_EXTI_IRQn EXTI3_IRQn
#define MN_0_Pin GPIO_PIN_4
#define MN_0_GPIO_Port GPIOA
#define MN_1_Pin GPIO_PIN_5
#define MN_1_GPIO_Port GPIOA
#define MN_2_Pin GPIO_PIN_6
#define MN_2_GPIO_Port GPIOA
#define MN_3_Pin GPIO_PIN_7
#define MN_3_GPIO_Port GPIOA
#define LD_0_Pin GPIO_PIN_11
#define LD_0_GPIO_Port GPIOA
#define LD_1_Pin GPIO_PIN_12
#define LD_1_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define CW 1
#define CCW 2
#define BRAKE 3
#define FREE 0

#define PPR 2048
#define RADIUS 53.5 //mm
#define CIRCUMFERENCE 336.150413
#define DT 1 / (64*10^6 / (( htim1.Init.Prescaler + 1) * ( htim1.Init.Period + 1 )))

#define PERIOD 50
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
