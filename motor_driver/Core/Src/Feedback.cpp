/*
 * Feedback.cpp
 *
 *  Created on: 23 Apr 2021
 *      Author: Ayato Yoshida
 */

#include "main.h"
#include "General.hpp"
#include "math.h"

double pulse_per_pwm = 1.45476;
double pulse_per_speed = 23.677;
double watch0;
double watch1;
double dt;


double Feedback::P_control(double Kp, double target, double input){
	double e = target - input;
	int add_pwm = (int)(floor( e /  pulse_per_pwm ));
	return add_pwm;
}

double Feedback::PID_control(double Kp,double Ki,double Kd,double target,double nowrap)
{

	static double prev_dev = 0;

	double dev=0;
	static double integral = 0;
	double differential = 0;
	double out = 0;

	dev = target - nowrap;
	watch0 = dev;
	integral += (dev + prev_dev) / 2 * dt;
    watch1 = integral;

	differential = (dev - prev_dev) / dt;

	if(integral >= 25)//積分値の上限設定
		integral=25;

    if(abs(dev) <= 10)//目標達成基準の閾値
    	integral = 0;

    out = Kp*dev + Ki*integral - Kd*differential;
    prev_dev = dev;

    return out;
}

double Feedback::speed_calc(int pulse){

	this -> speed = CIRCUMFERENCE * ((double)pulse / PPR );
	return this -> speed;
}
