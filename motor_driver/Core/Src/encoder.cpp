/*
 * encoder.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: Ayato Yoshida
 */

#include "main.h"
#include "Encoder.hpp"


void Encoder::EN_1(void)
{



	if(HAL_GPIO_ReadPin(EN_A_GPIO_Port,EN_A_Pin))
	{
		  if(HAL_GPIO_ReadPin(EN_B_GPIO_Port,EN_B_Pin))
		  {
			  this -> pulse_cnt--;
		  }
		  else
		  {
			  this -> pulse_cnt++;
		  }
	  }
	  else
	  {
		  if(HAL_GPIO_ReadPin(EN_B_GPIO_Port,EN_B_Pin))
		  {
			  this -> pulse_cnt++;
		  }
		  else
		  {
			  this -> pulse_cnt--;
		  }
	  }


}

void Encoder::EN_3(void)
{



	if(HAL_GPIO_ReadPin(EN_B_GPIO_Port,EN_B_Pin))
	{
		  if(HAL_GPIO_ReadPin(EN_A_GPIO_Port,EN_A_Pin))
		  {
			  this -> pulse_cnt++;
		  }
		  else
		  {
			  this -> pulse_cnt--;
		  }
	  }
	  else
	  {
		  if(HAL_GPIO_ReadPin(EN_A_GPIO_Port,EN_A_Pin))
		  {
			  this -> pulse_cnt--;
		  }
		  else
	  	  {
			  this -> pulse_cnt++;
	  	  }
	  }


}

int Encoder::get_pulse_cnt()
{
	return this -> pulse_cnt;
}

int Encoder::pulse_cnt = 0;

