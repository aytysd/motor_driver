/*
 * General.hpp
 *
 *  Created on: 23 Apr 2021
 *      Author: Ayato Yoshida
 */

#ifndef INC_GENERAL_HPP_
#define INC_GENERAL_HPP_

#include "main.h"


class PWM{
public:
	uint8_t set_motor_number();
    uint8_t motor_number;
    uint8_t direction;
    uint8_t pwm;
    uint8_t trapezoid;

    uint8_t trapezoid_control(uint8_t period, uint8_t divider, uint8_t target);
    void control_PWM();
    void LED();

};
class Function{
public:
	Function();
	~Function();

	int pulse_cnt;
    void outputPWM_LED(int pwm);
    void outputPWM0(int pwm);
    void outputPWM1(int pwm);
    int EN_1(void);
    int EN_3(void);


};
class Feedback{
public:
	double speed;

	double P_control(double Kp, double target, double input);
	double PID_control(double Kp, double Ki, double Kd, double target, double nowrap);
	double speed_calc(int pulse);
};


#endif /* INC_GENERAL_HPP_ */
