/*
 * Feedback.cpp
 *
 *  Created on: 23 Apr 2021
 *      Author: Ayato Yoshida
 */

#include "main.h"
#include "General.hpp"
#include "math.h"

double pulse_per_pwm = 30;

double Feedback::P_control(double target, double current){
	double e = target - current;
	int add_pwm = (int)(floor( e / this -> pulse_per_pwm ));
	return add_pwm;
}

