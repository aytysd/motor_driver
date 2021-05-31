/*
 * Encoder.hpp
 *
 *  Created on: 31 May 2021
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
#ifndef INC_ENCODER_HPP_
#define INC_ENCODER_HPP_

class Encoder{
public:
    void EN_1(void);
    void EN_3(void);
    int get_pulse_cnt(void);
private:
    static int pulse_cnt;

};



#endif /* INC_ENCODER_HPP_ */
