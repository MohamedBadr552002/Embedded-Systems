/*
 * buzzer.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Mohamed
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "driver.h"
#include "state.h"
enum{
	led_off,
	led_on
}led_state_id;


extern void (*P_led)();




void state_led_off();
void state_led_on();

#endif /* BUZZER_H_ */
