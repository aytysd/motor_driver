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

	void PID_control(void);
	void reset_PID(void);
	static int PID_pwm;


	int speed_calc(uint16_t target_speed);
	void pwm_calc(void);
	int get_current_pwm(void);

private:

	static int current_pwm;
	static int integral_diff;


	uint16_t current_speed_calc(void);
	int P_control(uint16_t target_speed, uint16_t current_speed);
	int I_control(uint16_t target_speed, uint16_t current_speed);
	int D_control(uint16_t current_speed);
};




#endif /* INC_FEEDBACK_HPP_ */
