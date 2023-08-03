/*
/*
 * controller.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Mohamed
 */


#include "controller.h"


volatile int con_pressure =0 ;
volatile int threshold=20;
volatile int send_led=1;//HIGH for turnning led off , LOW for turnning it on

void (*P_controller)();


void PS_get_pressure(int p)
{
	con_pressure = p;
	//checking
	(con_pressure <= threshold) ? (P_controller=ST_BUZZZER_off):(P_controller=ST_BUZZZER_on);
	//printf("PS-------pressure=%d-------->Controller \n",con_pressure);
}

void ST_BUZZZER_on()
{
	//state name
	con_state_id=buzzer_on;

	//set signal send to buzzer
	send_led=0;
	//printf("Controller in ON state: pressure= %d   buzzer=%d \n",con_pressure,send_led);

	//send to buzzer
	check_pressure(send_led);

}

void ST_BUZZZER_off()
{
	//state name
	con_state_id=buzzer_off;

	//set signal send to buzzer
	send_led=1;
	//printf("Controller in OFF state: pressure= %d   buzzer=%d \n",con_pressure,send_led);
    check_pressure(send_led);

	

}






