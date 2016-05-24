/*
 * task.c
 *
 *  Created on: Apr 15, 2016
 *      Author: exchizz
 */

#include "unpack_crc.h"

/* global variables */
uint8_t slip_in[SLIP_INBUF_LEN];
int slip_in_ptr;

/* local variables */
static char slip_state;
void task_slip_decode_crc_task(uint8_t my_state){
	char ch;
	bool new_packet = false;
	while(QueueReceive(&Queue_Uart1_Rx, &ch)) /* handle RX buffer */{
		if (slip_state == SLIP_STATE_STD){
			switch (ch){
			case SLIP_END:
				if (slip_in_ptr > -1)
					new_packet = true;
				break;

			case SLIP_ESC:
				slip_state = SLIP_STATE_ESC;
				break;

			default:
				slip_in[++slip_in_ptr] = ch;
				break;
			}
		} else{
			/* handle ESC state */
			switch(ch){
			case SLIP_ESC_END:
				slip_in[++slip_in_ptr] = SLIP_END;
				break;
			case SLIP_ESC_ESC:
				slip_in[++slip_in_ptr] = SLIP_ESC;
				break;
			}

			slip_state = SLIP_STATE_STD;
		}
	}

	/* handle buffer overflow */
	if (slip_in_ptr == SLIP_INBUF_LEN){
		slip_in_ptr = -1;
		new_packet = false;
	}

	if(new_packet){
		unsigned short crc_val;
		crc_val = (slip_in[slip_in_ptr-1] << 8) | slip_in[slip_in_ptr];

		crc = crc_init();
		crc = crc_update(crc, slip_in, slip_in_ptr-1);
		crc = crc_finalize(crc);

		//for(int i = 0; i < 34; i++){
		//	ch = slip_in[i];
		//	QueueSend(&Queue_Uart0_Tx,&ch);
		//}

		//ch = (crc >> 8 ) & 0x00FF;
		//QueueSend(&Queue_Uart0_Tx,&ch);
		//ch = (crc ) & 0x00FF;
		//QueueSend(&Queue_Uart0_Tx,&ch);

		slip_state = SLIP_STATE_STD;
		slip_in_ptr = -1;
		if (crc_val == crc){

			char crc_ok[] = "CRC OK\r\n";
			for(int i = 0; i < 8; i++){
				QueueSend(&Queue_Uart0_Tx,&crc_ok[i]);
			}

			GPS pose = GPS();

			for(int i = 0; i < 8; i++){
				pose.lat[i] = slip_in[i];
			}
			for(int i = 0; i < 8; i++){
				pose.lon[i] = slip_in[8+i];
			}
			for(int i = 0; i < 8; i++){
				pose.height[i] = slip_in[16+i];
			}
//			for(int i = 0; i < 8; i++){
//				pose.hDOP[i] = slip_in[24+i];
//			}
			pose.vDOP = slip_in[24];
			pose.tDOP = slip_in[25];
			pose.nDOP = slip_in[26];
			pose.eDOP = slip_in[27];

			QueueSend(&Queue_gps_pose,&pose);
		} else {

			char crc_no[] = "CRC NO\r\n";
			for(int i = 0; i < 8; i++){
				QueueSend(&Queue_Uart0_Tx,&crc_no[i]);
			}

		}
	}
	//return new_packet;
}

/***************************************************************************/
void slip_init (void)
{
	slip_state = SLIP_STATE_STD;
	slip_in_ptr = -1;
}
/***************************************************************************/

