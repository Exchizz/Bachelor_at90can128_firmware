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

#ifndef AUTOQUAD_H_
#define AUTOQUAD_H_

extern MessageCreator messageCreater;

void aq_node_task(uint8_t my_state);

#endif /* AUTOQUAD_H_ */
