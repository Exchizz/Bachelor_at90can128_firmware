/*
 * AutoQuad.cpp
 *
 *  Created on: May 11, 2016
 *      Author: Mathias Neerup
 */
#include "AutoQuad.h"
MessageCreator messageCreater;
CAN_frame can_cmd(CAN_frame & recv_frame){
	CAN_frame ret_frame;
	switch( (recv_frame.id & CAN_DOC_MASK)  >> (19-3) ){
	case CAN_CMD_TELEM_RATE:
		ret_frame = messageCreater.Create_SendACK();
		break;
	case CAN_CMD_TELEM_VALUE:
		ret_frame = messageCreater.Create_SendACK();
		break;
	}

	return ret_frame;
}
void aq_node_task(uint8_t my_state){
	CAN_frame recv_frame;
	CAN_frame tx_frame;
	tx_frame.id = 0;
	tx_frame.data = 0;
	tx_frame.dlc = 0;

	if(QueueReceive(&Queue_CAN_Rx, &recv_frame)){
		// Switch on function id
		switch(recv_frame.id & CAN_FID_MASK){
		case CAN_FID_RESET_BUS:
			//INT_LED_ON_RED;
			tx_frame = messageCreater.Create_ReqAddr(CAN_TYPE_SENSOR, CAN_SENSORS_GPS_LAT);
			QueueSend(&Queue_CAN_Tx, &tx_frame);
			break;
		case CAN_FID_GRANT_ADDR:
			if(messageCreater.mySession.packet_to_me(recv_frame)){
				INT_LED_OFF_RED;
			}

			break;
		case CAN_FID_CMD:
			if(messageCreater.mySession.packet_to_me(recv_frame)){
				tx_frame = can_cmd(recv_frame);
				QueueSend(&Queue_CAN_Tx, &tx_frame);
			}

			break;

		default:
			break;
		}
	}
}

