/*
 * task.c
 *
 *  Created on: Apr 15, 2016
 *      Author: exchizz
 */


#include "task.h"

extern void counter_task(uint8_t my_id, uint8_t my_state, uint8_t event, uint8_t data){
/*
	static uint8_t counter = 0;
	char string[] = "number: \n\r";
	string[7] = counter++ + '0';
	for(int i = 0; i < 10; i++){
		put_queue( Q_UART_TX, string[i], WAIT_FOREVER );
	}
	wait(500);
*/
	//CAN_frame *frame;
	//char temp = 0;
	/*
	if(get_can_frame_buffer(frame) == 1){

		for(int i = 0; i < 8; i++){
			temp = ( frame->msg >> i*8 ) & 0xFF;
			//put_queue( Q_UART_TX, temp-'0', WAIT_FOREVER );
		}
		//put_queue( Q_UART_TX, '\r', WAIT_FOREVER );
		//put_queue( Q_UART_TX, '\n', WAIT_FOREVER );
	} else {
	}
*/
}
