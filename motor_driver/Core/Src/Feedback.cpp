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
uint16_t Feedback::current_speed  = 0;

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




int Feedback::PID_control(uint16_t current_speed)
{

	uint16_t target_speed = (uint16_t)(( Rxdata[2] << 8 ) | ( Rxdata[3] ));

	if( !( 3 > this -> speed_diff_calc( target_speed, current_speed ) && -3 < this -> speed_diff_calc( target_speed, current_speed ) ))
	{
		this -> PID_pwm = this -> P_control(target_speed, current_speed) - this -> D_control(current_speed, target_speed) + this -> I_control(target_speed, current_speed);
	}

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

	static int old_diff = 0;
	this -> integral_diff += ( (target_speed - current_speed) + old_diff ) / 2 * DT;

	if( this -> integral_diff >= 25 )
	{
		this -> integral_diff = 25;
	}
	if( abs( target_speed - current_speed ) <= 10 )
	{
		this -> integral_diff = 0;
	}

	old_diff = target_speed - current_speed;

	return this -> integral_diff * Ki;

}



int Feedback::D_control(uint16_t current_speed, uint16_t target_speed)
{

	static uint16_t old_speed = current_speed;
	int diff = current_speed - old_speed;

	old_speed = current_speed;

	return diff * Kd;
}





