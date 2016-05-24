#include "MessageCreator.h"

#define SPOOF_VALUE_FIX 	   0
#define SPOOF_VALUE_SATELLITES 1
MessageCreator::MessageCreator() {
	// TODO Auto-generated constructor stub

}


CAN_frame MessageCreator::Create_ReqAddr(uint8_t type, uint8_t canId){
	CAN_frame msg_out;

	msg_out.id = CAN_FID_REQ_ADDR;

	msg_out.data = (((uint64_t)mySession.uuid[3]) << 56) | (((uint64_t)mySession.uuid[2]) << 48) | (((uint64_t)mySession.uuid[1]) << 40) | (((uint64_t)mySession.uuid[0]) << 32);
	msg_out.data |=((uint64_t)type << 24);
	msg_out.data |=((uint64_t)canId << 16);

	msg_out.dlc = 6;

	return msg_out;
}

/*
 * REV 2.0
 */

CAN_frame MessageCreator::Create_Stream_VEL(int16_t velN, int16_t velE, int16_t velD, int16_t speed, uint8_t doc) {

	CAN_frame msg_out;
	msg_out.id = CAN_FID_TELEM  | (((uint64_t)mySession.source_id) << (14-3)) | (((uint64_t)doc) << (19-3));
/*
	msg_out.data[0] = (uint8_t)(velN & 0x00FF);
	msg_out.data[1] = ((velN & 0xFF00) >> 8);

	msg_out.data[2] = (velE & 0x00FF);
	msg_out.data[3] = ((velE & 0xFF00) >> 8);

	msg_out.data[4] = (velD & 0x00FF);
	msg_out.data[5] = ((velD & 0xFF00) >> 8);

	msg_out.data[6] = (speed & 0x00FF);
	msg_out.data[7] = ((speed & 0xFF00) >> 8);
*/
	msg_out.data = velN | ((uint64_t)velE) << 16 | ((uint64_t)velD) << 32 | ((uint64_t)speed) << 48;
	msg_out.dlc = 8;

	return msg_out;
}
CAN_frame MessageCreator::Create_Stream_ACC(uint8_t satellites, uint8_t fix, uint8_t sAcc, uint8_t cAcc, uint8_t hAcc, uint8_t vAcc, int16_t heading, uint8_t doc) {

	CAN_frame msg_out;
	msg_out.id = CAN_FID_TELEM  | (((uint64_t)mySession.source_id) << (14-3)) | (((uint64_t)doc) << (19-3));
	msg_out.data = ((uint64_t)satellites) << 56 |  ((uint64_t)fix) << 48 |  ((uint64_t)sAcc) << 40 |((uint64_t)cAcc)  << 32 | ((uint64_t)hAcc) << 24 | ((uint64_t)vAcc) << 16 | (heading & 0x00FF) << 8 | (heading & 0xFF00) >>8;
	msg_out.dlc = 8;

	return msg_out;
}
CAN_frame MessageCreator::Create_Stream_DOP(uint8_t pDOP, uint8_t hDOP, uint8_t vDOP, uint8_t tDOP, uint8_t nDOP, uint8_t eDOP, uint8_t gDOP, uint8_t doc) {

	CAN_frame msg_out;
	msg_out.id = CAN_FID_TELEM  | (((uint64_t)mySession.source_id) << (14-3)) | (((uint64_t)doc) << (19-3));

	msg_out.data =  ((uint64_t)gDOP) << 8 | ((uint64_t)eDOP) << 16 | ((uint64_t)nDOP) << 24 | ((uint64_t)tDOP)  << 32 | ((uint64_t)vDOP) << 40| ((uint64_t)hDOP) << 48 | ((uint64_t)pDOP) << 56;

	/*
	msg_out.data[1] = hDOP;
	msg_out.data[2] = vDOP;
	msg_out.data[3] = tDOP;
	msg_out.data[4] = nDOP;
	msg_out.data[5] = eDOP;
	msg_out.data[6] = gDOP;
*/
	msg_out.dlc = 7;

	return msg_out;
}

/*
 * REV 2.0 END
 */
 CAN_frame MessageCreator::Create_Stream_double(uint8_t *value, uint8_t doc) {

	CAN_frame msg_out;
	msg_out.data = 0;
	msg_out.id = CAN_FID_TELEM | (((uint64_t)mySession.source_id) << (14-3)) | (((uint64_t)doc) << (19-3));

	for(int i = 0; i< 8; i++){
		msg_out.data |= (((uint64_t)value[7-i]) << i*8);
	}
	msg_out.dlc = 8;

	return msg_out;
 }
 CAN_frame MessageCreator::Create_Stream_int(uint8_t *value, uint8_t doc) {

	 CAN_frame msg_out;
	 msg_out.data = 0;
	 msg_out.id = CAN_FID_TELEM | (((uint64_t)mySession.source_id) << (14-3)) | (((uint64_t)doc) << (19-3));

	 msg_out.data = value[SPOOF_VALUE_FIX] | ((uint16_t)value[SPOOF_VALUE_SATELLITES] << 8);
	 msg_out.dlc = 2;

	 return msg_out;
 }
 CAN_frame MessageCreator::Create_SendACK(){
	 CAN_frame msg_out;

	 msg_out.id = CAN_FID_ACK | mySession.sequence_id;
	 msg_out.dlc = 0;

	 return msg_out;
 }
