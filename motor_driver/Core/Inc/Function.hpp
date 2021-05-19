/*
 * Function.hpp
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
#ifndef INC_FUNCTION_HPP_
#define INC_FUNCTION_HPP_

#include "main.h"

class Function{
public:

	static int pulse_cnt;

    void outputPWM0(uint8_t pwm);
    void outputPWM1(uint8_t pwm);
    void EN_1(void);
    void EN_3(void);


};




#endif /* INC_FUNCTION_HPP_ */
