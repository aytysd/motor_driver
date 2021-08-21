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

    void cw(uint8_t pwm);
    void ccw(uint8_t pwm);
    void brake(void);
    void free(void);

public:
    void disable_PID();
    void enable_PID();

    uint8_t set_motor_number();
    bool get_Is_reached(void);
    void control_PWM();

    static bool PID_Enabled;
    static uint8_t direction;


};



#endif /* INC_PWM_HPP_ */
