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

uint8_t Function::additional_pwm = 0;

void Function::outputPWM1(uint8_t pwm){

    PWM* pwm = new PWM();

    if( pwm -> get_Is_reached == true ){
    	pwm += this -> additional_pwm;
    }

	sConfigOC.Pulse = (uint32_t)((8)*pwm);

	if( sConfigOC.Pulse >= 799 ){
		sConfigOC.Pulse = 799;
	}


	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Init(&htim1);


    delete pwm;
}

void Function::outputPWM0(uint8_t pwm)
{

    PWM* pwm = new PWM();

    if( pwm -> get_Is_reached() == true ){
    	pwm += this -> additional_pwm;
    }


	sConfigOC.Pulse = (uint32_t)((8)*pwm);

	if( sConfigOC.Pulse >= 799 ){
		sConfigOC.Pulse = 799;
	}

	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Init(&htim1);


    delete pwm;

}


