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

#define Kp 1 / 23.677
#define Ki 23.677 * 10
#define Kd 10

class Feedback
{
public:

	int PID_control(void);
	void reset_PID(void);
	static int PID_pwm;


	int speed_diff_calc(uint16_t target_speed);
	uint16_t current_speed_calc();
	uint16_t current_speed_calc_2();

	void pwm_calc(void);
	int get_current_pwm(void);

private:

	static int current_pwm;
	static int integral_diff;


	int P_control(uint16_t target_speed, uint16_t current_speed);
	int I_control(uint16_t target_speed, uint16_t current_speed);
	int D_control(uint16_t current_speed);
};




#endif /* INC_FEEDBACK_HPP_ */
