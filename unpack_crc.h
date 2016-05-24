/*
 * task.h
 *
 *  Created on: Apr 15, 2016
 *      Author: exchizz
 */

#ifndef UNPACK_CRC_H_
#define UNPACK_CRC_H_
#include "can.h"

#include <stdbool.h>
#include "AutoQuad.h"
//#include "crc/crc_kjen.h"
#include "crc/crc.h"
/****************************************************************************/
/* SLIP special character codes  */
#define SLIP_END		192    /* indicates end of packet */
#define SLIP_ESC		219    /* indicates byte stuffing */
#define SLIP_ESC_END	220    /* ESC ESC_END means END data byte */
#define SLIP_ESC_ESC	221    /* ESC ESC_ESC means ESC data byte */

#define SLIP_INBUF_LEN	34

#define SLIP_STATE_STD	0
#define SLIP_STATE_ESC	1
/* global variables */
//static extern  unsigned char slip_in[];
extern int slip_in_ptr;

/* function prototypes */
void slip_init (void);

void task_slip_decode_crc_task(uint8_t my_state);
extern crc_t crc;

extern QueueHandle_t Queue_msg_valid;
#endif /* UNPACK_CRC_H_ */
