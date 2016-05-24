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


void aq_spoof_task(uint8_t my_state){
	GPS pose;
	uint8_t satellites = 10;
	uint8_t fix = 1; // Single point solution
	if(QueueReceive(&Queue_gps_pose,&pose)){
		CAN_frame tx_frame;

        // Latitude
		tx_frame = messageCreater.Create_Stream_double(pose.lat, CAN_DOC_LAT);
        QueueSend(&Queue_CAN_Tx, &tx_frame);
        // Longitude
        tx_frame = messageCreater.Create_Stream_double(pose.lon, CAN_DOC_LON);
        QueueSend(&Queue_CAN_Tx, &tx_frame);


		// pDOP, hDOP, vDOP, tDOP, nDOP, eDOP, gDOP
        // pose.vDOP = 1.5*pose.hDOP;
        // pose.tDOP = 1.5*pose.hDOP;
        // pose.nDOP = 0.7*pose.hDOP;
        // pose.eDOP = 0.7*pose.hDOP;
        //char ch = pose.vDOP;
        //QueueSend(&Queue_Uart0_Tx, &ch);

		tx_frame = messageCreater.Create_Stream_DOP(0, 0, pose.vDOP, pose.tDOP, pose.nDOP, pose.eDOP, 0, CAN_DOC_DOP);
        QueueSend(&Queue_CAN_Tx, &tx_frame);

        // sAcc = 0
        // hAcc = 1 (0.1 in Aq)
        // vAcc = 1 (0.1 in Aq)
        tx_frame = messageCreater.Create_Stream_ACC(satellites, fix, 30, 30, 20, 25, pose.heading, CAN_DOC_ACC);
        QueueSend(&Queue_CAN_Tx, &tx_frame);

        tx_frame = messageCreater.Create_Stream_double(pose.height, CAN_DOC_ALT);
        QueueSend(&Queue_CAN_Tx, &tx_frame);


/*
		// Latitude
		tx_frame = messageCreater.Create_Stream_double(pose.lat, LATITUDE_DOC);
		QueueSend(&Queue_CAN_Tx, &tx_frame);

		// Longitude
		tx_frame = messageCreater.Create_Stream_double(pose.lon, LONGITUDE_DOC);
		QueueSend(&Queue_CAN_Tx, &tx_frame);

		// FIX
		uint8_t values[2];
		values[0] = 1; //fix
		values[1] = 10; //satellites
		tx_frame = messageCreater.Create_Stream_int(values, FIX_HDOP);
		QueueSend(&Queue_CAN_Tx, &tx_frame);

		// HDOP
		tx_frame = messageCreater.Create_Stream_double(pose.dop, HDOP_DOC);
		QueueSend(&Queue_CAN_Tx, &tx_frame);

		// Altitude
		tx_frame = messageCreater.Create_Stream_double(pose.height, ALTITUDE_DOC);
		QueueSend(&Queue_CAN_Tx, &tx_frame);
*/
	}

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

