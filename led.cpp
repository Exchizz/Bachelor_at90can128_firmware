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

/*
	CAN_frame frame;
	if(QueueReceive(&Queue_CAN_Rx, &frame)) {
		char ch;

		for(int i = 3; i >=0; i--){
			ch = ((frame.id >> i*8) & 0x000000FF);
			QueueSend(&Queue_Uart0_Tx,&ch);
		}

		for(int i = (frame.dlc-1); i >=0; i--){
			ch = ((frame.msg >> i*8) & 0x00000000000000FF);
			QueueSend(&Queue_Uart0_Tx,&ch);
		}
		ch = '\r';
		QueueSend(&Queue_Uart0_Tx,&ch);
		ch = '\n';
		QueueSend(&Queue_Uart0_Tx,&ch);

	}
*/
	//CAN_frame frame;
	//frame.id=0x1DEADBEF;
	//frame.data=0xFEDCBA9876543210;

	//QueueSend(&Queue_CAN_Tx, &frame);
/*
	char ch;
	while(QueueReceive(&Queue_Uart1_Rx, &ch)){
		QueueSend(&Queue_Uart0_Tx,&ch);
	}
	*/
	switch(my_state){
	case 0:
		INT_LED_ON_GREEN;
		set_state( 1 );
		break;
	case 1:
		INT_LED_OFF_GREEN;
		set_state( 0 );
		INT_RESET_HIGH;
		break;
	}
	wait( 1000 );
}
