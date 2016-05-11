/*
 * led.c
 *
 *  Created on: Apr 14, 2016
 *      Author: exchizz
 */
#include "at90can_def.h"
#include "led.h"
#include "can.h"

void led_init(){
#ifdef FMCTRL
	INT_LED_INIT;
	INT_LED_OFF;

#elif WIFI_BOARD
	INT_LED_INIT_GREEN;
	INT_LED_OFF_GREEN;

	INT_LED_INIT_RED;
	INT_LED_OFF_RED;

	INT_LED_INIT_BLUE;
	INT_LED_OFF_BLUE;
#endif
}


void is_alive_task(uint8_t my_state){
	//UDR0 = my_state+'0';

	//char msg_out[] = {"Alive\r\n"};
	//for(int i = 0; i < 7; i++ ){
	//	QueueSend(&Queue_Uart0_Tx, &msg_out[i]);
	//}
	//UDR0 = Queue_Uart0_Tx.elements+'0';
/*
	char ch;
	if(QueueReceive(&Queue_Uart0_Rx, &ch)){
		//INT_LED_ON_BLUE;
		QueueSend(&Queue_Uart0_Tx,&ch);
		//UDR0 = ch;
	}
	*/

	CAN_frame frame;
	if(QueueReceive(&Queue_CAN_Rx, &frame)) {
		char ch;
		/* MSG out uart0 */
		/*
		for(int i = 7; i >=0; i--){
			ch = ((frame.msg >> i*8) & 0x00000000000000FF);
			QueueSend(&Queue_Uart0_Tx,&ch);
		}
		*/
		/* MSG end */

		/* ID out uart0 */
		for(int i = 3; i >=0; i--){
			ch = ((frame.id >> i*8) & 0x000000FF);
			QueueSend(&Queue_Uart0_Tx,&ch);
		}
		/* ID end*/
		ch = '\r';
		QueueSend(&Queue_Uart0_Tx,&ch);
		ch = '\n';
		QueueSend(&Queue_Uart0_Tx,&ch);

	}

	switch(my_state){
	case 0:
		INT_LED_ON_GREEN;
		//INT_LED_OFF_RED;
		//INT_LED_OFF_BLUE;
		set_state( 1 );
		break;
	case 1:
		INT_LED_OFF_GREEN;
		//INT_LED_ON_RED;
		//INT_LED_OFF_BLUE;
		set_state( 0 );
		INT_RESET_HIGH;
		break;
	case 2:
		INT_LED_OFF_GREEN;
		INT_LED_OFF_RED;
		INT_LED_ON_BLUE;
		set_state( 0 );

		INT_RESET_HIGH;

		break;
	}
	wait( 1000 );
}
