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

	uint8_t PID_control(void);
	void reset_integral_diff(void);

	double speed_calc(int pulse);
	void pwm_calc(void);
	static int current_pwm;

private:

	static int integral_diff;

	uint8_t P_control(uint16_t target_speed, uint16_t current_speed);
	uint8_t I_control(uint16_t target_speed, uint16_t current_speed);
	uint8_t D_control(uint16_t target_speed, uint16_t current_speed);
};




#endif /* INC_FEEDBACK_HPP_ */
