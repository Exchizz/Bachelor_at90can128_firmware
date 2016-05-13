/*
 * task.c
 *
 *  Created on: Apr 15, 2016
 *      Author: exchizz
 */

#include "task.h"
#include "slip/slip.h"
#include "crc/crc.h"

/* global variables */
unsigned char slip_in[SLIP_INBUF_LEN];
int slip_in_ptr;

/* local variables */
static char slip_state;
void task_slip_decode_src_task(uint8_t my_state){
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

			case SLIP_ESC_END:
				slip_in[++slip_in_ptr] = SLIP_END;
				break;

			case SLIP_ESC_ESC:
				slip_in[++slip_in_ptr] = SLIP_ESC;
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
		unsigned short crc_val, crc_check;
		crc_val = (slip_in[slip_in_ptr-1] << 8) | slip_in[slip_in_ptr];
		crc_check = crcFast(slip_in, slip_in_ptr-1);
		//char crc_ok[] = "CRC OK\r\n";
		for(int i = 0; i < slip_in_ptr; i++){
			QueueSend(&Queue_Uart0_Tx,&slip_in[i]);
		}
		slip_state = SLIP_STATE_STD;
		slip_in_ptr = -1;
		char ch = '\n';
		QueueSend(&Queue_Uart0_Tx,&ch);


		if (crc_val == crc_check){
			char crc_ok[] = "CRC OK\r\n";
			for(int i = 0; i < 8; i++){
				QueueSend(&Queue_Uart0_Tx,&crc_ok[i]);
			}
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

