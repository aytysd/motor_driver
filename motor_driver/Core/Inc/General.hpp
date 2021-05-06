/*
 * General.hpp
 *
 *  Created on: 23 Apr 2021
 *      Author: Ayato Yoshida
 */

#ifndef INC_GENERAL_HPP_
#define INC_GENERAL_HPP_

#include "main.h"

extern uint8_t Rxdata[2];

class PWM{

private:
	uint8_t set_motor_number();
    uint8_t old_pwm;
    uint8_t trapezoid_control(uint8_t period, uint8_t target);
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
class Function{
public:
	Function();
	~Function();

	int pulse_cnt;
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
