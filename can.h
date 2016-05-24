/*
 * can.h
 *
 *  Created on: May 9, 2016
 *      Author: exchizz
 */

#ifndef CAN_H_
#define CAN_H_

#include "at90can_def.h"
#include "led.h"
#include <stdlib.h>
#include <stdint.h>

struct CAN_frame {
	uint32_t id; // 29 bits, 32 reserved
	uint64_t data; // 64 bits, 64 bits reserved
	uint8_t dlc; //8 bits data length

	CAN_frame(){
		id = 0;
		data = 0;
		dlc = 0;
	}
};

extern QueueHandle_t Queue_CAN_Rx;
extern QueueHandle_t Queue_CAN_Tx;


void can_init();
void can_rx_task(uint8_t my_state);
void can_tx_task(uint8_t my_state);

#endif /* CAN_H_ */
