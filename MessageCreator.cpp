#include "MessageCreator.h"

MessageCreator::MessageCreator() {
	// TODO Auto-generated constructor stub

}


CAN_frame MessageCreator::Create_ReqAddr(uint8_t type, uint8_t canId){
	CAN_frame msg_out;

	msg_out.id = CAN_FID_REQ_ADDR;

	// ?? EF, CD, AB, 89 is uuid in AutoQuad ??
	//std::vector<int> v {'\x01','\xEF','\xCD',mySession.uuid ,type, canId,'\x23','\x01'}; // '\x23','\x01'

//	for(int i = 0; i < v.size(); ++i){
//		msg_out.data[i] = v[i];
//	}
	msg_out.data = (((uint64_t)mySession.uuid[3]) << 56) | (((uint64_t)mySession.uuid[2]) << 48) | (((uint64_t)mySession.uuid[1]) << 40) | (((uint64_t)mySession.uuid[0]) << 32);
	msg_out.data |=((uint64_t)type << 24);
	msg_out.data |=((uint64_t)canId << 16);

	msg_out.dlc = 6;

	return msg_out;
}

CAN_frame MessageCreator::Create_Stream(double value, uint8_t doc) {

	CAN_frame msg_out;
	msg_out.id = CAN_FID_TELEM | (((uint64_t)mySession.source_id) << (14-3)) | (((uint64_t)doc) << (19-3));
/*
	const unsigned char * value_double = reinterpret_cast<const unsigned char*>(&value);

	for(int i = 0; i < sizeof(double); ++i){
		msg_out.data[i] = value_double[i];
	}
	msg_out.dlc = sizeof(double);
*/
	return msg_out;
}

CAN_frame MessageCreator::Create_SendACK(){
	CAN_frame msg_out;

	msg_out.id = CAN_FID_ACK | mySession.sequence_id;
	msg_out.dlc = 0;

	return msg_out;
}
