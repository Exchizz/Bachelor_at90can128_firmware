/****************************************************************************
# AVR Serial Line Internet Protocol implementation
#
# Copyright (c) 2015, Kjeld Jensen <kj@kjen.dk>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of the copyright holder nor the names of its
#      contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************
# File: avr_slip.h
# Project: AVR Serial Line Internet Protocol implementation
#          https://www.ietf.org/rfc/rfc1055.txt
# Platform: AVR
# Microcontroller: Atmel AVR
# Author: Kjeld Jensen <kj@kjen.dk>
# Created:  2015-03-30 Kjeld Jensen
#****************************************************************************/

#ifndef _SLIP_H
#define _SLIP_H
#include <stdbool.h>
#include "../crc/crc.h"
/****************************************************************************/
/* SLIP special character codes  */
#define SLIP_END		192    /* indicates end of packet */
#define SLIP_ESC		219    /* indicates byte stuffing */
#define SLIP_ESC_END	220    /* ESC ESC_END means END data byte */
#define SLIP_ESC_ESC	221    /* ESC ESC_ESC means ESC data byte */

#define SLIP_INBUF_LEN	28

#define SLIP_STATE_STD	0
#define SLIP_STATE_ESC	1
/* global variables */
extern unsigned char slip_in[];
extern int slip_in_ptr;

/* function prototypes */
void slip_init (void);
char slip_rx_update (void);
void slip_tx_packet (unsigned char *data, int len);

/* local variables */
//extern static char slip_state;

/* */
/****************************************************************************/
#endif
