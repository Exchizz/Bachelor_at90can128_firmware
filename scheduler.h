/*
 * scheduler.hpp
 *
 *  Created on: May 10, 2016
 *      Author: Mathias Neerup
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>
#include "systick.h"
#include "led.h"

void schedule();

#define ST_TASK_NOT_INITIALIZED 0
#define ST_TASK_RUN				1
#define ST_TASK_WAIT            2

#define MAX_TASKS				10

void create_task(uint8_t task_id, void (*task_ptr)(uint8_t my_state));
void set_state(uint8_t my_next_state);
void wait(uint16_t wait_counter);
void scheduler_init();

struct Task {
	uint8_t task_id;
	uint8_t task_state;
	void (*task_ptr)(uint8_t my_state);
	uint16_t wait_counter;
	uint8_t my_state;
};

extern Task tasks[MAX_TASKS];
extern uint8_t task_counter;
extern uint8_t current_task;

#endif /* SCHEDULER_H_ */
