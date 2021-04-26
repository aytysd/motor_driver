/*
 * General.hpp
 *
 *  Created on: 23 Apr 2021
 *      Author: Ayato Yoshida
 */

#ifndef INC_GENERAL_HPP_
#define INC_GENERAL_HPP_

extern double PID_result;
extern double result;
extern double pulse_per_second;


class Feedback{
private:
	double P_control(double target, double current);
	double pulse_per_pwm;

};

class PWM{
public:
	uint8_t set_motor_number();
    uint8_t motor_number;
    uint8_t direction;
    uint8_t pwm;
    uint8_t trapezoid;

    void outputPWM0(int pwm);
    void outputPWM1(int pwm);
    void outputPWM_LED(int pwm);
    void control_PWM();
    void LED();

};


#endif /* INC_GENERAL_HPP_ */
