#include "can.h"

char data, canpage_bkp;

void can_rx_task(uint8_t my_state){
	/* backup the current MOb page */
	char canpage_bkp = (CANPAGE & 0xF0);

	/* select MOb 0 (RX) */
	CANPAGE = (0<<MOBNB0);

	if( CANSTMOB & (1 << RXOK) ){ //CANSTMOB & (1 << RXOK)
		// set to zero - from datasheet
		CANSTMOB = 0;

		CAN_frame frame;
		frame.id = 0;
		frame.data = 0;
		frame.dlc = 0;

		frame.dlc = (CANCDMOB & 0x0F);
		frame.id = ((uint32_t)CANIDT4 >> 3) |  ((uint32_t)CANIDT3 << 5) | ((uint32_t)CANIDT2 << 13) | ((uint32_t)CANIDT1 << 21);


		uint64_t temp = 0;
		for(int i = (frame.dlc - 1); i >= 0; i--){
			temp = CANMSG;
			frame.data |= (temp << i*8);
		}

		QueueSend(&Queue_CAN_Rx, &frame);
		//INT_LED_ON_BLUE;
	} else {
		//INT_LED_OFF_BLUE;
	}
	CANCDMOB = 8 | (1<<CONMOB1) | (1 << IDE); /* enable rx, max data length */
	/* restore the current MOb page */
	CANPAGE = (CANPAGE & 0xF0)| canpage_bkp;
}
void can_tx_task(uint8_t my_state){
	CAN_frame frame;
	if(QueueReceive(&Queue_CAN_Tx, &frame)){
		CANPAGE = (1<<MOBNB0);  /* select MOb 1 */
		/* Unpack ID */
		CANIDT1 = ( (((uint32_t)frame.id) & 0x1FE00000) >> 21);
		CANIDT2 = ( (((uint32_t)frame.id) & 0x001FE000) >> 13);
		CANIDT3 = ( (((uint32_t)frame.id) & 0x00001FE0) >> 5);
		CANIDT4 = ( (((uint32_t)frame.id) & 0x0000001F) << 3);
		/* Unpack ID end */

		/* Unpack data */
		CANMSG = ( (((uint64_t)frame.data) & 0xFF00000000000000) >> 56);
		CANMSG = ( (((uint64_t)frame.data) & 0x00FF000000000000) >> 48);
		CANMSG = ( (((uint64_t)frame.data) & 0x0000FF0000000000) >> 40);
		CANMSG = ( (((uint64_t)frame.data) & 0x000000FF00000000) >> 32);
		CANMSG = ( (((uint64_t)frame.data) & 0x00000000FF000000) >> 24);
		CANMSG = ( (((uint64_t)frame.data) & 0x0000000000FF0000) >> 16);
		CANMSG = ( (((uint64_t)frame.data) & 0x000000000000FF00) >> 8);
		CANMSG = ( (((uint64_t)frame.data) & 0x00000000000000FF));
		/* Unpack data end */

		CANSTMOB = 0x00; /* clear all status flags */

		/* set data length & enable transmission in MOb ctrl & DLC register */
		CANCDMOB = 8 | (0<<CONMOB1) | (1<<CONMOB0) | (1 << IDE);
	}
}

void can_tx_msg(CAN_frame * frame){

	CANPAGE = (1<<MOBNB0);  /* select MOb 1 */
	/* CANIDT is identifier tag */
	CANIDT1 = (char)(frame->id >> 3); /* 3 bits in byte above, move 3 left, still id=4 */
	CANIDT2 = (char)(frame->id <<5); /* 3 left bits, shift 5 , id = 4 */
	CANIDT3 = 0x00 ;/* Part B V2 */
	CANIDT4 = 0x00 ;

	CANMSG = 0x01;
	CANMSG = 0x02;
	CANMSG = 0x03;
	CANMSG = 0x04;
	CANMSG = 0x05;
	CANMSG = 0x06;
	CANMSG = 0x07;
	CANMSG = 0x08;

	CANSTMOB = 0x00; /* clear all status flags */

	/* set data length & enable transmission in MOb ctrl & DLC register */
	CANCDMOB = 8 | (0<<CONMOB1) | (1<<CONMOB0) | (1 << IDE);
}

ISR(CANIT_vect){

	/* backup the current MOb page */
	canpage_bkp = (CANPAGE & 0xF0);

	/* select MOb 0 (RX) */
	CANPAGE = (0<<MOBNB0);

	/* if received interrupt is RXOK */
	if(CANSTMOB & (1 << RXOK)){
		/*		data_buff[head].id = (((int)(CANIDT2))>>5) + (((int)(CANIDT1))<<3); // V2.0 part A */
		data = CANMSG;
		data = CANMSG;
		data = CANMSG;
		data = CANMSG;
		data = CANMSG;
		data = CANMSG;
		data = CANMSG;
		data = CANMSG;

		if(data & 0x01){
			INT_LED_ON_GREEN;
		} else {
			INT_LED_OFF_GREEN;
		}
	}

	CANSTMOB = 0; /* clear all interrupt flags */
	CANCDMOB = 8 | (1<<CONMOB1); /* enable rx, max data length */

	/* restore the current MOb page */
	CANPAGE = (CANPAGE & 0xF0)|canpage_bkp;
}


void can_init(){
	CANGCON = (1<<SWRES); /* Reset CAN controller */

	while((CANGSTA & (1<<ENFG)) != 0); /*wait for CAN controller to be enabled */

	/* 250 kbits pr. sek */
	//CANBT1  = 0x06;
	//CANBT2  = 0x04;
	//CANBT3  = 0x13; // Page 368 http://www.atmel.com/images/doc7679.pdf

	CANBT1  = 0x00;
	CANBT2  = 0x04;
	CANBT3  = 0x12; // Page 368 http://www.atmel.com/images/doc7679.pdf


	/* MOb 0 is used for Rx */
	CANPAGE = (0<<MOBNB0);
	CANCDMOB = 8 | (1<<CONMOB1) | (1 << IDE); /* enable rx, max data length */
	CANSTMOB = 0; /* Can Mob status */
	CANIDT1  = 0; /* Disable auto reply mode */
	CANIDT2  = 0;
	CANIDT3  = 0;
	CANIDT4  = 0;
	CANIDM1  = 0; /* accept all ID's */
	CANIDM2  = 0;
	CANIDM3  = 0;
	CANIDM4  = 0;

	/* MOb 1 is used for Tx */
	CANPAGE  = (1<<MOBNB0); /* select MOb 1 */
	CANCDMOB = 0;
	CANSTMOB = 0;
	CANIDT1  = 0;
	CANIDT2  = 0;
	CANIDT3  = 0;
	CANIDT4  = 0;
	CANIDM1  = 0;
	CANIDM2  = 0;
	CANIDM3  = 0;
	CANIDM4  = 0;

	int num_mob, num_data;

	/* reset all other MOb's */
	for (num_mob=2; num_mob<15; num_mob++){
		CANPAGE  = (num_mob<<MOBNB0);
		CANCDMOB = 0;
		CANSTMOB = 0;
		CANIDT1  = 0;
		CANIDT2  = 0;
		CANIDT3  = 0;
		CANIDT4  = 0;
		CANIDM1  = 0;
		CANIDM2  = 0;
		CANIDM3  = 0;
		CANIDM4  = 0;

		for (num_data = 0; num_data < 8; num_data++){
			CANMSG = 0;
		}
	}

	/* configure the MOb 0 interrupt */
	CANIE1 = 0;
	//CANIE2 = (1<<IEMOB0); /*<- interrupt on mob0 (rx)*/

	/* enable CAN (ENA/STB bit) */
	CANGCON |= (1 << ENASTB);

	/* wait until CAN is enabled */
	while(!(CANGSTA & (1<<ENFG)))

		/* CAN general & Rx interrupt enable */
		CANGIE = (1<<ENRX)|(1<<ENIT);
	//CANGIE = (1<<ENRX);

	//sei();
}
