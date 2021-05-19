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

class Feedback{
public:
	double speed;

	double P_control(double Kp, double target, double input);
	double PID_control(double Kp, double Ki, double Kd, double target, double nowrap);
	double speed_calc(int pulse);
	void pwm_calc(void);
	static int current_pwm;
};




#endif /* INC_FEEDBACK_HPP_ */
