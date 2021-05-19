/*
 * PWM.hpp
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
#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#include "main.h"

class PWM{

private:
	uint8_t set_motor_number();

	int old_pwm;
    uint8_t motor_number;
    uint8_t direction;
    uint8_t target_buff;
    int target;

    uint8_t trapezoid_control(uint8_t period, uint8_t target);
    uint8_t trapezoid_control_2(uint8_t period, uint8_t target);

    void cw(uint8_t pwm);
    void ccw(uint8_t pwm);
    void brake(void);
    void free(void);
public:
    void control_PWM();

	PWM(){
		this -> old_pwm = 0;
	}

};



#endif /* INC_PWM_HPP_ */
