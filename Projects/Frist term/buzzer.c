/*
 * buzzer.c
 *
 *  Created on: Sep 4, 2022
 *      Author: Mohamed
 */

#include "buzzer.h"

volatile unsigned int alarm =1;


void (*P_led)();

void check_pressure(int signal)
{	
	alarm = signal;

	if(alarm == 1)
	{P_led = state_led_off ; }
	else
	{ P_led = state_led_on ;}
}

void state_led_off()
{
	led_state_id = led_off;

	Set_Alarm_actuator(1);
}

void state_led_on()
{
	led_state_id = led_on;
	
	//start alarm
	Set_Alarm_actuator(0);
	Delay(1000000);
	
	
}

