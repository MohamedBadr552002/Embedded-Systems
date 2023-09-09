/*
 * 7_segments.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Mohamed
 */

#ifndef INCLUDES_7_SEGMENTS_H_
#define INCLUDES_7_SEGMENTS_H_

#include "STM32F103C6_DRIVER_GPIO.h"




#define ZERO	(0x01)
#define ONE		(0x79)
#define TWO		(0x24)
#define THREE	(0x30)
#define FOUR	(0x4C)
#define FIVE	(0x12)
#define SIX		(0x02)
#define SEVEN	(0x19)
#define EIGHT	(0x00)
#define NINE	(0x10)



//-----------------------
//=====APIS==============
//-----------------------
void HAL_7SEGMENT_INIT(void);
void HAL_7SEGMENT_OUT(GPIO_typeDef* gpiox ,uint16_t NUM );

#endif /* INCLUDES_7_SEGMENTS_H_ */
