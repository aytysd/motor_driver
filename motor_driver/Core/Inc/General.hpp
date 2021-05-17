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
class Function{
public:

	static int pulse_cnt;

    void outputPWM0(uint8_t pwm);
    void outputPWM1(uint8_t pwm);
    void EN_1(void);
    void EN_3(void);


};
class Feedback{
public:
	double speed;

	double P_control(double Kp, double target, double input);
	double PID_control(double Kp, double Ki, double Kd, double target, double nowrap);
	double speed_calc(int pulse);
	void pwm_calc(void);
	static int current_pwm;
};


#endif /* INC_GENERAL_HPP_ */
