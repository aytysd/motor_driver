/*
 * Function.cpp
 *
 *  Created on: 31 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(description_about_thisclass)
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(value)to(where)
 *
 *@Attention_(description)
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */

#include "main.h"
#include "Function.hpp"
#include "PWM.hpp"

void Function::outputPWM0(uint8_t pwm)
{
	static uint8_t old_pwm = 0;

	if( old_pwm != pwm )
	{

		TIM_OC_InitTypeDef sConfigOC;
		sConfigOC.Pulse = (uint32_t)((8)*pwm);

		if( sConfigOC.Pulse >= 799 )
			sConfigOC.Pulse = 799;
		else if ( sConfigOC.Pulse <= 0 )
			sConfigOC.Pulse = 0;



		sConfigOC.OCMode = TIM_OCMODE_ASSYMETRIC_PWM1;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
		sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);

	}

	old_pwm = pwm;




}



void Function::outputPWM1(uint8_t pwm)
{

	static uint8_t old_pwm = 0;

	if( old_pwm != pwm )
	{
		TIM_OC_InitTypeDef sConfigOC;

		sConfigOC.Pulse = (uint32_t)((8)*pwm);

		if( sConfigOC.Pulse >= 799 )
			sConfigOC.Pulse = 799;
		else if ( sConfigOC.Pulse <= 0 )
			sConfigOC.Pulse = 0;



		sConfigOC.OCMode = TIM_OCMODE_ASSYMETRIC_PWM2;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
		sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);

	}


	old_pwm = pwm;
}

