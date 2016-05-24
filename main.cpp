/*
 * main.cpp
 *
 *  Created on: May 10, 2016
 *      Author: Mathias Neerup
 */
#include "scheduler.h"
#include "led.h"
#include "uart.h"
#include "queue.h"
#include "can.h"
#include "AutoQuad.h"
#include "unpack_crc.h"

/* Task defines */
#define TASK_IS_ALIVE    0
#define TASK_UART0_TX    1
#define TASK_UART0_RX    2
#define TASK_UART1_TX    3
#define TASK_UART1_RX    4
#define TASK_CAN_RX		 5
#define TASK_CAN_TX		 6
#define TASK_AQ_NODE	 7 // Rename to sensor instead of node
#define TASK_SLIP_CRC	 8
#define TASK_AQ_SPOOF    9
/* Task defins end*/

#define QUEUE_SIZE_UART 15
#define QUEUE_SIZE_CAN 15 // Enough messages to keep lat, lon, dop, fix, satellites, height
#define QUEUE_SIZE_GPS_POSE 5

QueueHandle_t Queue_Uart0_Rx;
QueueHandle_t Queue_Uart0_Tx;

QueueHandle_t Queue_Uart1_Rx;
QueueHandle_t Queue_Uart1_Tx;

QueueHandle_t Queue_CAN_Rx;
QueueHandle_t Queue_CAN_Tx;

QueueHandle_t Queue_gps_pose;


crc_t crc;

int main(){
	CLKPR = (1 << CLKPCE); // Enable change of CLKPS bits
	CLKPR = (1 << CLKPS0) ; // Set prescaler to 2, system clock to 8 MHz as said in datasheet to at90can128

	/* Initialize queues */
	Queue_Uart0_Rx  = QueueCreate(QUEUE_SIZE_UART, sizeof(uint8_t));
	Queue_Uart0_Tx  = QueueCreate(100, sizeof(uint8_t));

	Queue_Uart1_Rx  = QueueCreate(100, sizeof(uint8_t));
	Queue_Uart1_Tx  = QueueCreate(QUEUE_SIZE_UART, sizeof(uint8_t));

	Queue_CAN_Rx    = QueueCreate(QUEUE_SIZE_CAN, sizeof(CAN_frame));
	Queue_CAN_Tx    = QueueCreate(QUEUE_SIZE_CAN, sizeof(CAN_frame));

	Queue_gps_pose  = QueueCreate(QUEUE_SIZE_GPS_POSE, sizeof(GPS));
	/* Initialize queues end*/

	/* Setup peripherals */
	esp_init(ESP_NORMAL_MODE);
	led_init();
	can_init();
	/* Setup peripherals end*/

	/* Initialize SLIP and crc*/
	slip_init();
	/* Initialize SLIP and crc end*/

	/* Setup Uart */
	uart_init(USART_0);
	uart_init(USART_1);
	/* Setup Uart end */

	scheduler_init();

	/* Create tasks*/
	create_task(TASK_IS_ALIVE, is_alive_task);

	// Uart 0
	create_task(TASK_UART0_TX, uart0_tx_task);
	create_task(TASK_UART0_RX, uart0_rx_task);

	// Uart 1
	create_task(TASK_UART1_TX, uart1_tx_task);
	create_task(TASK_UART1_RX, uart1_rx_task);

	// CAN
	create_task(TASK_CAN_RX, can_rx_task);
	create_task(TASK_CAN_TX, can_tx_task);

	// Autoquad
	create_task(TASK_AQ_NODE, aq_node_task);

	// ESP8266 communication
	create_task(TASK_SLIP_CRC, task_slip_decode_crc_task);


	// AutoQuad spoof
	create_task(TASK_AQ_SPOOF, aq_spoof_task);
	/* Create tasks end*/

	/* Run scheduler */
	char msg_out[] = {"Bootedv2\r\n"};
	for(int i = 0; i < 10; i++ ){
		QueueSend(&Queue_Uart0_Tx, &msg_out[i]);
	}
	schedule();
	/* Run scheduler end*/
	return 0;
}
