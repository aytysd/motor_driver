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

bool PWM::PID_Enabled = false;
uint8_t PWM::direction = BRAKE;

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


	if (this -> direction == CW)
		this -> cw( Rxdata[ 1 ] );
	else if (this -> direction == CCW)
		this -> ccw( Rxdata[ 1 ] );
	else if (this -> direction == BRAKE)
		this -> brake();

}


void PWM::cw(uint8_t pwm)
{

	Function* function = new Function();
	Feedback* feedback = new Feedback();

    if( this -> PID_Enabled == true )
    {
    	pwm += feedback -> PID_control( Feedback::current_speed );
    }



	function -> outputPWM0(pwm);
	function -> outputPWM1(99);

//	HAL_TIM_PWM_Init(&htim1);


	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);


	delete function;
	delete feedback;

}
void PWM::ccw(uint8_t pwm)
{

	Function* function = new Function();
	Feedback* feedback = new Feedback();

    if( this -> PID_Enabled == true )
    {
    	pwm += feedback -> PID_control( Feedback::current_speed );
    }


	function -> outputPWM0(1);
	function -> outputPWM1(99-pwm);

//	HAL_TIM_PWM_Init(&htim1);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);



	delete function;
	delete feedback;

}
void PWM::brake(void)
{

	Function* function = new Function();

	function -> outputPWM0(0);
	function -> outputPWM1(99);

	HAL_TIM_PWM_Init(&htim1);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);

	delete function;

}

/*
void PWM::free(void)
{

	Function* function = new Function();

	function -> outputPWM0(0);
	function -> outputPWM1(0);

	HAL_TIM_PWM_Init(&htim1);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);

	this -> Is_reached = false;

//	HAL_Delay(2000);


	delete function;
}
*/


void PWM::disable_PID()
{
	this -> PID_Enabled = false;
}

void PWM::enable_PID()
{
	this -> PID_Enabled = true;
}

