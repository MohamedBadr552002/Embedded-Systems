/*
 * main.c
 *
 *  Created on: Sep 4, 2022
 *      Author: Mohamed
 */

#include "stdio.h"
#include "stdlib.h"
#include "controller.h"
#include "state.h"
#include "pressure_sensor.h"
#include "buzzer.h"
#include "driver.h"



void setup()
{
	//init blocks
	GPIO_INITIALIZATION();
	

	//set pointer for each block
	PS_pointer = SP_PS_busy;
	P_controller =ST_BUZZZER_off;
	P_led = state_led_off;
}

void main()
{ 	
    setup();

	while(1)
	{
		PS_pointer();
		P_controller();
		P_led();

		
	}
}
