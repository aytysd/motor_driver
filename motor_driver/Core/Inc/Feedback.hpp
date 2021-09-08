/*
 * Feedback.hpp
 *
 *  Created on: 18 May 2021
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
#ifndef INC_FEEDBACK_HPP_
#define INC_FEEDBACK_HPP_

#include "main.h"


#define Kp 0.05
#define Ki 0.8
#define Kd 0.04


class Feedback
{
public:

	double PID_control(uint16_t current_speed);
	static double PID_pwm;
	static uint16_t current_speed;
	static double integral_diff;


	int speed_diff_calc(uint16_t target_speed, uint16_t current_speed );
	uint16_t current_speed_calc();


private:

	double P_control(uint16_t target_speed, uint16_t current_speed);
	double I_control(uint16_t target_speed, uint16_t current_speed);
	double D_control(uint16_t current_speed, uint16_t target_speed);
};




#endif /* INC_FEEDBACK_HPP_ */
