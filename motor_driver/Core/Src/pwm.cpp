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

	Function * function = new Function();

    uint8_t motor_number = (0b00111100&data[0])>>2;
    uint8_t direction = 0b00000011&data[0];
    uint8_t pwm = data[1];
    if(pwm >= 99){
    	pwm = 99;
    }
    uint8_t trapezoid = data[0]>>6;
    static uint8_t old_pwm = 0;


    if (motor_number == this -> set_motor_number())
    {
    	pwm = this -> trapezoid_control(100, 0 , pwm);

        if (direction == CW)
        {

/*
            function -> outputPWM0(pwm);
            function -> outputPWM1(99);
*/

            HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);
        }
        else if (direction == CCW)
        {
/*
            function -> outputPWM0(1);
            function -> outputPWM1(100-pwm);
*/
            HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);
        }
        else if (direction == BRAKE)
        {
/*
            function -> outputPWM0(0);
            function -> outputPWM1(100);
*/
            HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);
        }
    }

    old_pwm = pwm;


    delete function;



}

uint8_t PWM::trapezoid_control(uint8_t period, uint8_t target){

	if(old_pwm >= target){
		return target;
	}
	old_pwm++;
	HAL_Delay(period);

	return old_pwm;

}









void PWM::LED(void){

	HAL_GPIO_TogglePin(LD_0_GPIO_Port, LD_0_Pin);

/*
    HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(LD_0_GPIO_Port, LD_0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD_1_GPIO_Port, LD_1_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);
*/


}

