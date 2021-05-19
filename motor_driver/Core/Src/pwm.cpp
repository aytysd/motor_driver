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


uint8_t PWM::set_motor_number(){
	uint8_t motor_number = 0;

	if (HAL_GPIO_ReadPin(MN_0_GPIO_Port, MN_0_Pin) == 0) motor_number = motor_number|0b1;
	if (HAL_GPIO_ReadPin(MN_1_GPIO_Port, MN_1_Pin) == 0) motor_number = motor_number|(0b1<<1);
	if (HAL_GPIO_ReadPin(MN_2_GPIO_Port, MN_2_Pin) == 0) motor_number = motor_number|(0b1<<2);
	if (HAL_GPIO_ReadPin(MN_3_GPIO_Port, MN_3_Pin) == 0) motor_number = motor_number|(0b1<<3);

	return motor_number;


}
void PWM::control_PWM(void){



    this -> motor_number = (0b00111100&Rxdata[0])>>2;
    this -> direction = 0b00000011&Rxdata[0];
    this -> target_buff = Rxdata[1];

    uint8_t pwm;

    switch(this -> direction){
    case CW:
    	this -> target = (int)this -> target_buff;
    	break;
    case CCW:
    	this -> target = (-1) * (int)this -> target_buff;
    	break;
    default:
    	break;
    }




    if (this -> motor_number == this -> set_motor_number())
    {
    	pwm = this -> trapezoid_control_2(PERIOD, this -> target);

        if (this -> direction == CW)
        {
        	this -> cw(pwm);
        }
        else if (this -> direction == CCW)
        {
        	this -> ccw(pwm);
        }
        else if (this -> direction == BRAKE)
        {
        	this -> brake();
        }
        else if (this -> direction == FREE)
        {
        	this -> free();
        	this -> old_pwm = Feedback::current_pwm;
        }
    }

    this -> old_pwm = pwm;






}

uint8_t PWM::trapezoid_control_2(uint8_t period, uint8_t target){
	switch(this -> direction){
	case CW:

		if(this -> old_pwm < 0){
			this -> free();
			this -> old_pwm = 0;
		}

		if(this -> old_pwm >= target){
			return target;
		}
		this -> old_pwm++;
		HAL_Delay(period);

		return (uint8_t)this -> old_pwm;


		break;
	case CCW:

		if(this -> old_pwm > 0){
			this -> free();
			this -> old_pwm = 0;
		}

		if(this -> old_pwm <= target){
			return abs(target);
		}
		this -> old_pwm--;
		HAL_Delay(period);

		return (uint8_t)abs(this -> old_pwm);


		break;
	default:
		break;

	}
}

uint8_t PWM::trapezoid_control(uint8_t period, uint8_t target){

	if(this -> old_pwm >= target){
		return target;
	}
	this -> old_pwm++;
	HAL_Delay(period);

	return this -> old_pwm;

}

void PWM::cw(uint8_t pwm){

	Function * function = new Function();

	function -> outputPWM0(pwm);
	function -> outputPWM1(99);


	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);

	delete function;

}
void PWM::ccw(uint8_t pwm){

	Function * function = new Function();

	function -> outputPWM0(1);
	function -> outputPWM1(100-pwm);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);

	delete function;

}
void PWM::brake(void){

	Function * function = new Function();

	function -> outputPWM0(0);
	function -> outputPWM1(100);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);

	this -> old_pwm = 0;

	delete function;

}
void PWM::free(void){

	Function * function = new Function();

	function -> outputPWM0(0);
	function -> outputPWM1(100);

	HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);



	delete function;
}





