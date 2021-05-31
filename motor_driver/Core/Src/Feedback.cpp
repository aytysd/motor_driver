/*
 * Feedback.cpp
 *
 *  Created on: 23 Apr 2021
 *      Author: Ayato Yoshida
 */

#include "main.h"
#include "Feedback.hpp"
#include "Function.hpp"
#include "math.h"
#include "Encoder.hpp"

double pulse_per_pwm = 1.45476;
double pulse_per_speed = 23.677;
double watch0;
double watch1;


uint8_t Feedback::PID_control( uint16_t target_speed ){
	Encoder* encoder = new Encoder();
	uint16_t current_speed = RADIUS * 2 * M_PI * encoder -> get_pulse_cnt() / ( PPR * DT );

	return this -> P_control(target_speed, current_speed) + this -> I_control(target_speed, current_speed) + this -> D_control(target_speed, current_speed);

	delete encoder;
}



uint8_t Feedback::P_control(uint16_t target_speed, uint16_t current_speed ){


	uint16_t speed_diff = abs( target_speed - current_speed );

	uint8_t add_pwm = speed_diff / 17.244;

	return add_pwm;

}

uint8_t Feedback::I_control(uint16_t target_speed, uint16_t current_speed){

	uint8_t diff = target_speed - current_speed;
	return diff;
}

uint8_t Feedback::D_control(uint16_t target_speed, uint16_t current_speed){

	static int old_speed = current_speed;
	static int integral_diff = 0;

	integral_diff += ( current_speed - old_speed );

	old_speed = current_speed;

	return integral_diff;

}



/*
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
*/

double Feedback::speed_calc(int pulse){

	this -> speed = CIRCUMFERENCE * ((double)pulse / PPR );
	return this -> speed;
}

void Feedback::pwm_calc(){
	Encoder* encoder = new Encoder();
	static int old_pulse_cnt = 0;

	int speed = (encoder -> get_pulse_cnt() - old_pulse_cnt) * CIRCUMFERENCE / ( DT * PPR );
	if( speed < 0 ){
		Feedback::current_pwm = ( speed - 17.242 ) / 23.677;
		return;
	}

	Feedback::current_pwm = ( speed + 17.242 ) / 23.677;

	delete encoder;

	return;
}

int Feedback::current_pwm = 0;

