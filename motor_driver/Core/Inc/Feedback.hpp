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
#define Ki 1
#define Kd 0.08

class Feedback
{
public:

	int PID_control(uint16_t current_speed);
	static int PID_pwm;
	static uint16_t current_speed;
	static int integral_diff;


	int speed_diff_calc(uint16_t target_speed, uint16_t current_speed );
	uint16_t current_speed_calc();


private:

	static int current_pwm;



	int P_control(uint16_t target_speed, uint16_t current_speed);
	int I_control(uint16_t target_speed, uint16_t current_speed);
	int D_control(uint16_t current_speed, uint16_t target_speed);
};




#endif /* INC_FEEDBACK_HPP_ */
