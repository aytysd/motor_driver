/*
 * pwm.cpp
 *
 *  Created on: Apr 20, 2021
 *      Author: Ayato Yoshida
 */
//#include <Feedback.hpp>
#include <main.h>
#include "math.h"
#include "PWM.hpp"
#include "Feedback.hpp"
#include "Function.hpp"


uint8_t PWM::set_motor_number()
{
	uint8_t motor_number = 0;

	if (HAL_GPIO_ReadPin(MN_0_GPIO_Port, MN_0_Pin) == 0) motor_number = motor_number|0b1;
	if (HAL_GPIO_ReadPin(MN_1_GPIO_Port, MN_1_Pin) == 0) motor_number = motor_number|(0b1<<1);
	if (HAL_GPIO_ReadPin(MN_2_GPIO_Port, MN_2_Pin) == 0) motor_number = motor_number|(0b1<<2);
	if (HAL_GPIO_ReadPin(MN_3_GPIO_Port, MN_3_Pin) == 0) motor_number = motor_number|(0b1<<3);

	return motor_number;


}

void PWM::control_PWM(void)
{


	this -> direction = 0b00000011&Rxdata[0];
	this -> PID_Enabled = Rxdata[0]>>6;

	switch(this -> direction)
	{
	case CW:
		this -> target = (int)Rxdata[1];
		break;
	case CCW:
		this -> target = (-1) * (int)Rxdata[1];
		break;
	default:
		break;
	}


    uint8_t pwm = 0;

	pwm = this -> trapezoid_control(PERIOD, this -> target);

	if (this -> direction == CW)
	{
		this -> cw(pwm);
		this -> old_pwm = pwm;
	}
	else if (this -> direction == CCW)
	{
		this -> ccw(pwm);
		this -> old_pwm = pwm;
	}
	else if (this -> direction == BRAKE)
	{
		this -> brake();
		this -> old_pwm = 0;
	}
	else if (this -> direction == FREE)
	{
		this -> free();

		Feedback* feedback = new Feedback();
		this -> old_pwm = feedback -> get_current_pwm();
		delete feedback;
	}

}

uint8_t PWM::trapezoid_control(uint8_t period, uint8_t target)
{
	switch(this -> direction)
	{
	case CW:

		if(this -> old_pwm < 0)
		{
			this -> free();
			this -> old_pwm = 0;
		}

		if(this -> old_pwm >= this -> target)
		{

			this -> Is_reached = true;
			return this -> target;

		}
		else
		{

			this -> Is_reached = false;

		}
		this -> old_pwm++;
		HAL_Delay(period);

		return (uint8_t)this -> old_pwm;


		break;
	case CCW:

		if(this -> old_pwm > 0)
		{
			this -> free();
			this -> old_pwm = 0;
		}

		if(this -> old_pwm <= this -> target)
		{

			this -> Is_reached = true;
			return (uint8_t)abs( this -> target );

		}
		else
		{

			this -> Is_reached = false;

		}
		this -> old_pwm--;
		HAL_Delay(period);

		return (uint8_t)abs(this -> old_pwm);


		break;
	default:

		return 0;

		break;

	}
}


void PWM::cw(uint8_t pwm)
{

	Function* function = new Function();
	Feedback* feedback = new Feedback();

    if( this -> get_Is_reached() == true && this -> PID_Enabled == true )
    {
    	pwm += Feedback::PID_pwm;
    }


	function -> outputPWM0(pwm);
	function -> outputPWM1(99);

	HAL_TIM_PWM_Init(&htim1);


	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);

	delete function;
	delete feedback;

}
void PWM::ccw(uint8_t pwm)
{

	Function* function = new Function();
	Feedback* feedback = new Feedback();

    if( this -> get_Is_reached() == true && this -> PID_Enabled == true )
    {
    	pwm += Feedback::PID_pwm;
    }


	function -> outputPWM0(1);
	function -> outputPWM1(100-pwm);

	HAL_TIM_PWM_Init(&htim1);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);

	delete function;
	delete feedback;

}
void PWM::brake(void)
{

	Function* function = new Function();

	this -> free();

	function -> outputPWM0(0);
	function -> outputPWM1(100);

	HAL_TIM_PWM_Init(&htim1);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);

	this -> Is_reached = false;

	delete function;

}

void PWM::free(void)
{

	Function* function = new Function();

	function -> outputPWM0(0);
	function -> outputPWM1(0);

	HAL_TIM_PWM_Init(&htim1);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);

	this -> Is_reached = false;

	HAL_Delay(500);

	delete function;
}

bool PWM::get_Is_reached()
{
	return this -> Is_reached;
}


bool PWM::Is_reached = false;


