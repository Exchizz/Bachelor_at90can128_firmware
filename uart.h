/*
 * uart.h
 *
 *  Created on: May 10, 2016
 *      Author: Mathias Neerup
 */
#ifndef _UART_H
  #define _UART_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "led.h"


#define FOSC 		8000000	/* oscillator frequency [Hz] */
#define BAUD 		9600		/* baud rate */

extern QueueHandle_t Queue_Uart0_Rx;
extern QueueHandle_t Queue_Uart0_Tx;

extern QueueHandle_t Queue_Uart1_Rx;
extern QueueHandle_t Queue_Uart1_Tx;


#define USART_0 1
#define USART_1 2

void uart0_tx_task(uint8_t my_state);
void uart0_rx_task(uint8_t my_state);

void uart1_tx_task(uint8_t my_state);
void uart1_rx_task(uint8_t my_state);

void uart_init(int uart);

#endif

