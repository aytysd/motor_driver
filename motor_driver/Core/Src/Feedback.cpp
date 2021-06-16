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
int Feedback::PID_pwm  = 0;
int Feedback::current_pwm = 0;
int Feedback::prp_pwm = 0;

uint16_t Feedback::current_speed_calc()
{
	uint16_t current_speed = RADIUS * 2 * M_PI * abs( Encoder::pulse_cnt ) / ( PPR * DT );
	Encoder::pulse_cnt = 0;
	return current_speed;


}


int Feedback::speed_diff_calc(uint16_t target_speed, uint16_t current_speed )
{


	if( target_speed == 0 )
	{
		target_speed++;
	}

	int diff_percent = 100 * (int)(current_speed - target_speed) / (int)target_speed;


	return diff_percent;
}


void Feedback::reset_PID()
{

	this -> integral_diff = 0;
	this -> PID_pwm = 0;

	return;

}


int Feedback::PID_control(uint16_t current_speed)
{

	uint16_t target_speed = (uint16_t)(( Rxdata[2] << 8 ) | ( Rxdata[3] ));

	if( this -> speed_diff_calc( target_speed, current_speed ) == 0)
	{
		this -> prp_pwm = this -> PID_pwm;
		return prp_pwm;
	}

	Feedback::PID_pwm = this -> P_control(target_speed, current_speed) - this -> D_control(current_speed) + this -> I_control(target_speed, current_speed);

	return this -> PID_pwm;
}



int Feedback::P_control(uint16_t target_speed, uint16_t current_speed )
{

	int speed_diff = target_speed - current_speed;

	int add_pwm = speed_diff * Kp;

	return add_pwm;

}

int Feedback::I_control(uint16_t target_speed, uint16_t current_speed)
{


	this -> integral_diff += ( target_speed - current_speed );

	return this -> integral_diff / Ki;

}



int Feedback::D_control(uint16_t current_speed)
{

	static uint16_t old_speed = current_speed;
	int diff = current_speed - old_speed;

	old_speed = current_speed;

	return diff * Kd;
}


void Feedback::pwm_calc()
{
	static int old_pulse_cnt = 0;

	int speed = ( Encoder::pulse_cnt - old_pulse_cnt) * CIRCUMFERENCE / ( DT * PPR );
	if( speed < 0 )
	{
		Feedback::current_pwm = ( speed - 17.242 ) / 23.677;
		return;
	}

	Feedback::current_pwm = ( speed + 17.242 ) / 23.677;


	return;
}

int Feedback::get_current_pwm()
{
	return this -> current_pwm;
}



