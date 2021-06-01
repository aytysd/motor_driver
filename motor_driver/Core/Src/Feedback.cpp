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


double pulse_per_pwm = 1.45476;
double pulse_per_speed = 23.677;
double watch0;
double watch1;

int Feedback::integral_diff = 0;

int Feedback::current_pwm = 0;

void Feedback::reset_integral_diff(){

	this -> integral_diff = 0;
	return;

}


uint8_t Feedback::PID_control(){

	Encoder* encoder = new Encoder();

	uint16_t target_speed = ( Rxdata[2] << 8 ) | (Rxdata[3]);

	static int old_pulse_cnt = encoder -> get_pulse_cnt();
	int current_pulse_cnt = encoder -> get_pulse_cnt();

	uint16_t current_speed = RADIUS * 2 * M_PI * abs( (int)(current_pulse_cnt - old_pulse_cnt) ) / ( PPR * DT );

	delete encoder;
	old_pulse_cnt = current_pulse_cnt;


	return this -> P_control(target_speed, current_speed) + this -> I_control(target_speed, current_speed) - this -> D_control(target_speed, current_speed);


}



uint8_t Feedback::P_control(uint16_t target_speed, uint16_t current_speed ){


	uint16_t speed_diff = abs( target_speed - current_speed );

	uint8_t add_pwm = speed_diff / 23.677;

	return add_pwm;

}

uint8_t Feedback::D_control(uint16_t target_speed, uint16_t current_speed){

	static uint16_t old_speed = current_speed;
	uint8_t diff = current_speed - old_speed;

	old_speed = current_speed;

	return diff;
}

uint8_t Feedback::I_control(uint16_t target_speed, uint16_t current_speed){


	this -> integral_diff += ( target_speed - current_speed );

	return this -> integral_diff / 30;

}




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



