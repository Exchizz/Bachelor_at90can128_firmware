/*
 * SessionHandler.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: exchizz
 */

#include "Session.h"

Session::Session() {
	// TODO Auto-generated constructor stub
	source_id = -1;
	uuid[0] = 0xDE;
	uuid[1] = 0xAD;
	uuid[2] = 0xBe;
	uuid[3] = 0xEF;
}

uint8_t Session::createSession(uint8_t id){
	return 0;
}

bool Session::packet_to_me(CAN_frame &frame){
	uint8_t retval = false;

	uint8_t *frame_data = ( uint8_t * ) &frame.data;
	for(int i = 0; i < 4; i++){
		QueueSend(&Queue_Uart0_Tx,&frame_data[i]);
	}
	char ch = '\r';
	QueueSend(&Queue_Uart0_Tx,&ch);
	ch = '\n';
	QueueSend(&Queue_Uart0_Tx,&ch);

	uint8_t recv_target_id = ((frame.id & CAN_TID_MASK) >> (9-3));
	if( frame_data[2] == uuid[0] || source_id == recv_target_id){
		updateSession(frame.id);
		retval = true;
	}
	return retval;
}

uint8_t Session::updateSession(uint32_t id){
	sequence_id = (id & CAN_SEQ_MASK);
	source_id = ((id & CAN_TID_MASK) >> (9-3)); //We are target_id with respect to the drone, but source when we are sending.. I assume
//	target_id = ((id & CAN_TID_MASK) >> (9-3));
	ttype = (id & CAN_TT_MASK);
	llc = (id & CAN_LCC_MASK);

	return sequence_id;
}
