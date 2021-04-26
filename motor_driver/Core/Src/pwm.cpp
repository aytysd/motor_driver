/*
 * pwm.cpp
 *
 *  Created on: Apr 20, 2021
 *      Author: Ayato Yoshida
 */
//#include <Feedback.hpp>
#include <main.h>
#include "General.hpp"

//uint8_t Rxdata[2];
uint8_t data[2];

uint8_t PWM::set_motor_number(){
	uint8_t motor_number = 0;

	if (HAL_GPIO_ReadPin(MN_0_GPIO_Port, MN_0_Pin) == 0) motor_number = motor_number|0b1;
	if (HAL_GPIO_ReadPin(MN_1_GPIO_Port, MN_1_Pin) == 0) motor_number = motor_number|(0b1<<1);
	if (HAL_GPIO_ReadPin(MN_2_GPIO_Port, MN_2_Pin) == 0) motor_number = motor_number|(0b1<<2);
	if (HAL_GPIO_ReadPin(MN_3_GPIO_Port, MN_3_Pin) == 0) motor_number = motor_number|(0b1<<3);

	return motor_number;


}
void PWM::control_PWM(void){

    uint8_t motor_number = (0b00111100&data[0])>>2;
    uint8_t direction = 0b00000011&data[0];
    uint8_t pwm = data[1];
    uint8_t trapezoid = data[0]>>6;

    if (motor_number == set_motor_number())
    {
//        if (trapezoid == 1) pwm = controlTrapezoid(pwm);

        if (direction == CW)
        {
/*
            outputPWM0(pwm);
            outputPWM1(99);
*/
            HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);
        }
        else if (direction == CCW)
        {
/*
            outputPWM0(1);
            outputPWM1(100-pwm);
*/
            HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);
        }
        else if (direction == BRAKE)
        {
/*
            outputPWM0(0);
            outputPWM1(100);
*/
            HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);
        }
    }



}



void PWM::outputPWM_LED(int pwm){

/*
    	void MX_TIM1_Init(void);

//        sConfigOC.Pulse = (uint32_t)((8)*pwm);

        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
*/

}


void PWM::outputPWM1(int pwm){
/*
    static int old_pwm = 0;

    if (old_pwm != pwm)
    {


    	void MX_TIM1_Init(void);

//        sConfigOC.Pulse = (uint32_t)((8)*pwm);

        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
    }
    old_pwm = pwm;
*/
}

void outputPWM0(int pwm)
{
/*
    static int old_pwm = 0;

    if (old_pwm != pwm)
    {
        TIM_OC_InitTypeDef sConfigOC;

        sConfigOC.Pulse = (uint32_t)((8)*pwm);

        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
    }
    old_pwm = pwm;
*/
}




void PWM::LED(void){
    HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);

}

