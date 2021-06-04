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

	int old_pwm;
    uint8_t direction;
    uint8_t target_buff;
    int target;
    bool PID_Enabled;

    uint8_t trapezoid_control(uint8_t period, uint8_t target);

    void cw(uint8_t pwm);
    void ccw(uint8_t pwm);
    void brake(void);
    void free(void);

    static bool Is_reached;
public:

    uint8_t set_motor_number();
    bool get_Is_reached(void);
    void control_PWM();

	PWM()
    {
		this -> old_pwm = 0;
		this -> direction = FREE;
		this -> target_buff = 0;
		this -> target = 0;
		this -> PID_Enabled = false;
	}

};



#endif /* INC_PWM_HPP_ */
