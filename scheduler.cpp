/*
 * scheduler.cpp
 *
 *  Created on: May 10, 2016
 *      Author: Mathias Neerup
 */
#include "scheduler.h"

Task tasks[MAX_TASKS];
uint8_t task_counter = 0;
uint8_t current_task = 0;

void scheduler_init(){
	for(int i = 0; i <  MAX_TASKS; i++){
		Task task;
		tasks[i] = task;
		tasks[i].task_state = ST_TASK_NOT_INITIALIZED;
	}
	init_systick();
	sei();
}

void create_task(uint8_t task_id, void (*task_ptr)(uint8_t my_state)){
	//If valid task_id
	if (task_id < MAX_TASKS){
		tasks[task_counter].task_state = ST_TASK_RUN;
		tasks[task_counter].task_id = task_id;
		tasks[task_counter].task_ptr = task_ptr;
		tasks[task_counter].wait_counter = 1;
		tasks[task_counter].my_state = 0;

		//Increment task_counter
		task_counter++;
	}
}

void set_state(uint8_t my_next_state){
	tasks[current_task].my_state = my_next_state;
}

void wait(uint16_t wait_counter){
	tasks[current_task].wait_counter = wait_counter;
	tasks[current_task].task_state = ST_TASK_WAIT;
}
void schedule(){
	while(true){
		//Wait for tick
		while(!ticks);
		ticks--;

		// Run through each tasks
		for(current_task = 0; current_task < task_counter; current_task++){

			// If tasks' state is running, run the task, else decrement the wait_counter;
			if(tasks[current_task].task_state == ST_TASK_RUN || (tasks[current_task].wait_counter == 0 && tasks[current_task].task_state == ST_TASK_WAIT)){
				tasks[current_task].task_state = ST_TASK_RUN;
				uint8_t my_state = tasks[current_task].my_state;
				tasks[current_task].task_ptr(my_state);
			} else {
				tasks[current_task].wait_counter--;
			}
		}
	}
}
