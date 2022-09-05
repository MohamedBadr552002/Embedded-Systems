/*
 /*
 * pressure_sensor.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Mohamed
 */


#include "pressure_sensor.h"


//variables

volatile int PS_pressure =0 ;

void (*PS_pointer)();



void SP_PS_busy()
{
	//state name
	PS_state_id= P_busy;
	//get pressure
	PS_pressure = getPressureVal();
	//printf("Press_sensor in busy state : pressure = %d \n",PS_pressure);
	//send signal to next module
	PS_get_pressure(PS_pressure);

	PS_pointer=SP_PS_busy;

}
