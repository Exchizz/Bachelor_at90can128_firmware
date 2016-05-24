/*
 * AutoQuad.hpp
 *
 *  Created on: May 11, 2016
 *      Author: Mathias Neerup
 */
#include <stdint.h>
#include "can.h"
#include "led.h"
#include "MessageCreator.h"

#define CAN_DOC_LAT 0x01
#define CAN_DOC_LON 0x02
#define CAN_DOC_DOP 0x03
#define CAN_DOC_ACC 0x04
#define CAN_DOC_VEL 0x05
#define CAN_DOC_ALT 0x06


#ifndef AUTOQUAD_H_
#define AUTOQUAD_H_

typedef struct MessageCreator MessageCreater;
extern MessageCreater messageCreater;

void aq_node_task(uint8_t my_state);
void aq_spoof_task(uint8_t my_state);


extern QueueHandle_t Queue_gps_pose;
struct GPS {
	uint8_t lat[8];
	uint8_t lon[8];
	uint8_t height[8];
//	uint8_t dop[8];
	uint8_t vDOP;
	uint8_t nDOP;
	uint8_t eDOP;
	uint8_t tDOP;
	uint8_t hDOP;
	uint16_t heading;

	GPS(){
		vDOP = 0;
		nDOP = 0;
		eDOP = 0;
		tDOP = 0;
		heading = 0;
		hDOP = 0;
	}
};
#endif /* AUTOQUAD_H_ */
