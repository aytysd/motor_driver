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
#include "stdlib.h"
#include "PWM.hpp"


int Feedback::integral_diff = 0;
uint8_t Feedback::PID_pwm  = 0;
int Feedback::current_pwm = 0;


void Feedback::reset_integral_diff(){

	this -> integral_diff = 0;
	return;

}


int Feedback::PID_control(){


	PWM* pwm = new PWM();

	uint16_t target_speed = 0;
	if( (0b00111100&Rxdata[0])>>2 == pwm -> set_motor_number() )
	{
		target_speed = ( Rxdata[2] << 8 ) | ( Rxdata[3] );
	}
	delete pwm;

	uint16_t current_speed = this -> current_speed_calc();

	return this -> P_control(target_speed, current_speed) + this -> I_control(target_speed, current_speed) - this -> D_control(current_speed);


}



int Feedback::P_control(uint16_t target_speed, uint16_t current_speed ){


	int speed_diff = target_speed - current_speed;

	int add_pwm = speed_diff / 23.677;

	return add_pwm;

}

int Feedback::I_control(uint16_t target_speed, uint16_t current_speed){


	this -> integral_diff += ( target_speed - current_speed );

	return this -> integral_diff / 30;

}



int Feedback::D_control(uint16_t current_speed){

	static uint16_t old_speed = current_speed;
	int diff = current_speed - old_speed;

	old_speed = current_speed;

	return diff;
}


uint16_t Feedback::current_speed_calc()
{
	Encoder* encoder = new Encoder();

	static int old_pulse_cnt = encoder -> get_pulse_cnt();
	int current_pulse_cnt = encoder -> get_pulse_cnt();

	uint16_t current_speed = RADIUS * 2 * M_PI * abs( (int)(current_pulse_cnt - old_pulse_cnt) ) / ( PPR * DT );

	delete encoder;
	old_pulse_cnt = current_pulse_cnt;

	return current_speed;

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



