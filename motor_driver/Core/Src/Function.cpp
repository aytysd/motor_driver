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

    static uint8_t old_pwm = 0;
    PWM* pwm = new PWM();

    if( pwm -> get_Is_reached == true ){
    	pwm += this -> additional_pwm;
    }



	sConfigOC.Pulse = (uint32_t)((8)*pwm);

	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Init(&htim1);

    old_pwm = pwm;

    delete pwm;
}

void Function::outputPWM0(uint8_t pwm)
{

    static uint8_t old_pwm = 0;

    if (old_pwm != pwm)
    {

        sConfigOC.Pulse = (uint32_t)((8)*pwm);

        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
        HAL_TIM_PWM_Init(&htim1);
    }

    old_pwm = pwm;

}


