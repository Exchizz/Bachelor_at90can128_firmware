/*
 * led.h
 *
 *  Created on: Apr 14, 2016
 *      Author: exchizz
 */
#include "at90can_def.h"
#include "scheduler.h"
#include "ESP8266.h"
#include "queue.h"
#include "uart.h"
#ifndef LED_H_
#define LED_H_

//extern QueueHandle_t Queue_Uart_Tx;
//extern QueueHandle_t Queue_Uart_Rx;

void led_init();
void is_alive_task(uint8_t my_state);

#endif /* LED_H_ */
