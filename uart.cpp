/*
 * uart.cpp
 *
 *  Created on: May 10, 2016
 *      Author: Mathias Neerup
 */
#include "uart.h"


void uart0_rx_task(uint8_t my_state){
	//If data available in uart0-buffer
	if( UCSR0A & (1 << RXC0) ){
		char ch = UDR0;
		QueueSend(&Queue_Uart0_Rx, &ch);
	}
}
void uart0_tx_task(uint8_t my_state){
	uint8_t ch;
	//Check if any characters in buffer
	if( QueueReceive(&Queue_Uart0_Tx, &ch)){
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = ch;
	}
}
/*
ISR (USART0_RX_vect){
	char ch = UDR0;
	QueueSend(&Queue_Uart0_Rx, &ch);
}

ISR (USART1_RX_vect){
	if( UCSR1A & (1 << RXC1) ){
		char ch = UDR1;
		QueueSend(&Queue_Uart1_Rx, &ch);
	}
}
*/

void uart1_rx_task(uint8_t my_state){

	//If data available in uart0-buffer
	while( UCSR1A & (1 << RXC1) ){
		char ch = UDR1;
		QueueSend(&Queue_Uart1_Rx, &ch);
	}
}

void uart1_tx_task(uint8_t my_state){
	uint8_t ch;
	//Check if any characters in buffer
	if( QueueReceive(&Queue_Uart1_Tx, &ch)){
		while(!(UCSR1A & (1 << UDRE0)));
		UDR1 = ch;
	}
}


extern void uart_init(int uart){
	switch(uart){
	case USART_0:
		UCSR0B = (1<<TXEN0)|(1<<RXEN0);     /* enable tx and rx */
		UBRR0H = (unsigned char) ((8)>>8);  /* 8 is from AT90can128 table, page 202. 8 mhz, 57600 bps */
		UBRR0L = (unsigned char) (8);       /* 8 is from AT90can128 table, page 202. 8 mhz, 57600 bps */
		UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); 	/* asynchronous 8N1 */
		//UCSR0B |= (1 << RXCIE0); 			/* Enable Rx interrupt */
		break;
	case USART_1:
		UCSR1B = (1<<TXEN0)|(1<<RXEN0);     /* enable tx and rx */
		UBRR1H = (unsigned char) ((51)>>8);  /* 8 is from AT90can128 table, page 202. 8 mhz, 57600 bps */
		UBRR1L = (unsigned char) (51);       /* 8 is from AT90can128 table, page 202. 8 mhz, 57600 bps */
		UCSR1C = (1<<UCSZ00)|(1<<UCSZ01); 	/* asynchronous 8N1 */
		//UCSR1B |= (1 << RXCIE1); 			/* Enable Rx interrupt */
		break;
	}

	/* enable tx and rx */
//	UCSRB_REG = (1<<TXEN_BIT)|(1<<RXEN_BIT);
	/* set baud rate */
//	UBRRH_REG = (unsigned char) ((8)>>8);
//	UBRRL_REG = (unsigned char) (8); /* 8 is from AT90can128 table, page 202. 8 mhz, 57600 bps */

	/* asynchronous 8N1 */
//	UCSRC_REG = (1<<UCSZ0_BIT)|(1<<UCSZ1_BIT);

	/* enable double speed mode if #DOUBLE_SPEED_MODE is set */
#ifdef DOUBLE_SPEED_MODE
	UCSRA_REG |= U2X_BIT;
#endif

	/* init rx  */
	//UCSRB_REG |= (1 << RXCIE_BIT);

}
/****************************** End Of Module *******************************/












