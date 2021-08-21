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


double Feedback::integral_diff = 0;
double Feedback::PID_pwm  = 0;
uint16_t Feedback::current_speed  = 0;

uint16_t Feedback::current_speed_calc()
{
	if( Encoder::pulse_cnt == 0 )
	{
		PWM* pwm = new PWM();
		pwm -> disable_PID();
		delete pwm;
	}
	else
	{
		PWM* pwm = new PWM();
		pwm -> enable_PID();
		delete pwm;
	}

	uint16_t current_speed = RADIUS * 2 * M_PI * abs( Encoder::pulse_cnt ) / ( PPR * DT );
	Encoder::pulse_cnt = 0;
	return current_speed;

}


int Feedback::speed_diff_calc(uint16_t target_speed, uint16_t current_speed )
{


	if( target_speed == 0 )
		target_speed++;

	int diff_percent = 100 * (int)(current_speed - target_speed) / (int)target_speed;


	return diff_percent;
}



double Feedback::PID_control(uint16_t current_speed)
{

	uint16_t target_speed = (uint16_t)( ( Rxdata[2] << 8 ) | ( Rxdata[3] ) );

	if( !( 30 > abs(target_speed - current_speed)) )
		this -> PID_pwm = Kp * this -> P_control(target_speed, current_speed) + Ki * this -> I_control(target_speed, current_speed) - Kd * this -> D_control(current_speed, target_speed);

	if( PID_pwm >= 30 )
		PID_pwm = 30;
	if( PID_pwm <= -30 )
		PID_pwm = -30;

	return this -> PID_pwm;
}



double Feedback::P_control(uint16_t target_speed, uint16_t current_speed )
{
	return ( double )target_speed - ( double )current_speed;

}

double Feedback::I_control(uint16_t target_speed, uint16_t current_speed)
{

	static int old_diff = 0;
	this -> integral_diff += ( ( double )(target_speed - current_speed) + old_diff ) / 2 * DT;

	if( this -> integral_diff >= 25 )
		this -> integral_diff = 25;
	else if( this -> integral_diff <= -25 )
		this -> integral_diff = -25;

	if( abs( target_speed - current_speed ) <= 10 )
		this -> integral_diff = 0;


	old_diff = ( double )target_speed - ( double )current_speed;

	return this -> integral_diff;

}



double Feedback::D_control(uint16_t current_speed, uint16_t target_speed)
{
	static uint16_t old_speed;
	static int old_speed_diff;
	int diff = ( double )current_speed - ( double )old_speed;

	double differential = ( diff - old_speed_diff ) / DT;

	if( differential > 25 )
		differential = 25;
	if( differential < -25 )
		differential = -25;

	old_speed_diff = ( double )current_speed - ( double )old_speed;
	old_speed = current_speed;

	return differential;
}





