/*
 * pwm.cpp
 *
 *  Created on: Apr 20, 2021
 *      Author: Ayato Yoshida
 */
//#include <Feedback.hpp>
#include <main.h>
#include "General.hpp"



uint8_t PWM::set_motor_number(){
	uint8_t motor_number = 0;

	if (HAL_GPIO_ReadPin(MN_0_GPIO_Port, MN_0_Pin) == 0) motor_number = motor_number|0b1;
	if (HAL_GPIO_ReadPin(MN_1_GPIO_Port, MN_1_Pin) == 0) motor_number = motor_number|(0b1<<1);
	if (HAL_GPIO_ReadPin(MN_2_GPIO_Port, MN_2_Pin) == 0) motor_number = motor_number|(0b1<<2);
	if (HAL_GPIO_ReadPin(MN_3_GPIO_Port, MN_3_Pin) == 0) motor_number = motor_number|(0b1<<3);

	return motor_number;


}
void PWM::control_PWM(void){



    uint8_t motor_number = (0b00111100&Rxdata[0])>>2;
    uint8_t direction = 0b00000011&Rxdata[0];
    uint8_t target = Rxdata[1];
    if(target >= 99){
    	target = 99;
    }
    uint8_t pwm;


    if (motor_number == this -> set_motor_number())
    {
    	pwm = this -> trapezoid_control(PERIOD, target);

        if (direction == CW)
        {
        	this -> cw(pwm);
        }
        else if (direction == CCW)
        {
        	this -> ccw(pwm);
        }
        else if (direction == BRAKE)
        {
        	this -> brake();
        }
    }

    old_pwm = pwm;






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

	this -> old_pwm = 0;

	delete function;
}





