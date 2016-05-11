/*
 * Session.h
 *
 *  Created on: Feb 5, 2016
 *      Author: exchizz
 */

#include "MessageCreator.h"
#ifndef SESSION_H_
#define SESSION_H_

class Session {
public:
	uint8_t target_id;
	uint8_t ttype;
	uint8_t llc;
	uint8_t uuid[4];
	uint8_t sequence_id;
	uint8_t source_id;
	Session();
	uint8_t createSession(uint8_t);
	uint8_t updateSession(uint32_t);
	bool packet_to_me(CAN_frame &frame);
};

#endif /* SESSION_H */
