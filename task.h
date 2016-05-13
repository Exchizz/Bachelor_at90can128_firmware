/*
 * task.h
 *
 *  Created on: Apr 15, 2016
 *      Author: exchizz
 */

#ifndef TASK_H_
#define TASK_H_
#include "can.h"

void task_slip_decode_src_task(uint8_t my_state);

extern QueueHandle_t Queue_msg_valid;
#endif /* TASK_H_ */
