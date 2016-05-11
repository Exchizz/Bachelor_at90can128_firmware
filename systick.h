/*
 * scheduler.h
 *
 *  Created on: Apr 14, 2016
 *      Author: exchizz
 */
#include <avr/interrupt.h>
#include "at90can_def.h"


#ifndef SYSTICK_H_
	#define SYSTICK_H_

	extern volatile uint8_t ticks;
	void init_systick();
#endif /* SYSTICK_H_ */
