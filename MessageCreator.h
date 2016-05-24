/*
 * MessageCreator.h
 *
 *  Created on: Feb 4, 2016
 *      Author: exchizz
 */


#ifndef MESSAGECREATOR_H_
#define MESSAGECREATOR_H_

#include "can.h"
#include "Session.h"
#include <stdint.h>
#include "AutoQuad.h"
// Function ID (Substract 3 due to ARM's way of prepending status flags)
#define CAN_FID_MASK        (((uint32_t)0xf) << (25-3 ))

#define CAN_FID_REQ_ADDR    (((uint32_t)0x7) << (25-3))
#define CAN_FID_GRANT_ADDR  (((uint32_t)0x8) << (25-3))
#define CAN_FID_RESET_BUS   (((uint32_t)0x0) << (25-3))
#define CAN_FID_CMD         (((uint32_t)0x3) << (25-3))
#define CAN_FID_GET         (((uint32_t)0x4) << (25-3))
#define CAN_FID_REPLY       (((uint32_t)0x6) << (25-3))
#define CAN_FID_ACK         (((uint32_t)0x1) << (25-3))
#define CAN_FID_TELEM       (((uint32_t)0xb) << (25-3))
#define CAN_FID_SET         (((uint32_t)0x5) << (25-3))

#define CAN_TID_MASK        (0x1f<< (9-3))

#define CAN_TT_MASK         (((uint32_t)0x1) << (29-3))
#define CAN_TT_GROUP        (((uint32_t)0x0) << (29-3))
#define CAN_TT_NODE         (((uint32_t)0x1) << (29-3))

#define CAN_LCC_MASK        (((uint32_t)0x3) << (30-3))
#define CAN_LCC_EXCEPTION   (((uint32_t)0x0) << (30-3))
#define CAN_LCC_HIGH        (((uint32_t)0x1) << (30-3))
#define CAN_LCC_NORMAL      (((uint32_t)0x2) << (30-3))
#define CAN_LCC_INFO        (((uint32_t)0x3) << (30-3))

#define CAN_SEQ_MASK        (((uint32_t)0x3f)<< (3-3))

// Source ID
#define CAN_SID_MASK        (((uint32_t)0x1f)<< (14-3))

// commands
enum {
    CAN_CMD_DISARM = 1,
    CAN_CMD_ARM,
    CAN_CMD_START,
    CAN_CMD_STOP,
    CAN_CMD_SETPOINT10,
    CAN_CMD_SETPOINT12,
    CAN_CMD_SETPOINT16,
    CAN_CMD_RPM,
    CAN_CMD_CFG_READ,
    CAN_CMD_CFG_WRITE,
    CAN_CMD_CFG_DEFAULT,
    CAN_CMD_TELEM_RATE,
    CAN_CMD_TELEM_VALUE,
    CAN_CMD_BEEP,
    CAN_CMD_POS,
    CAN_CMD_USER_DEFINED,
    CAN_CMD_RESET,
    CAN_CMD_STREAM,
    CAN_CMD_ON,
    CAN_CMD_OFF
};
// sensor types
enum {
    CAN_SENSORS_PDB_BATV = 0,
    CAN_SENSORS_PDB_BATA,
    CAN_SENSORS_PDB_TEMP,
    CAN_SENSORS_GIMBAL_ACCX,
    CAN_SENSORS_GIMBAL_ACCY,
    CAN_SENSORS_GIMBAL_ACCZ,
    CAN_SENSORS_GIMBAL_GYOX,
    CAN_SENSORS_GIMBAL_GYOY,
    CAN_SENSORS_GIMBAL_GYOZ,
    CAN_SENSORS_GPS_LAT, // Added by Mathias 08.02.15
    CAN_SENSORS_GPS_LON, // Added by Mathias 08.02.15
    CAN_SENSORS_NUM
};
// Custom
//#define CAN_EFF             (((uint32_t)0x1 << 31) // Set can Extended bit(needed in can_interface my molar)
#define CAN_DOC_MASK        (((uint32_t)0x3f)<< (19-3))
//Can types
enum {
    CAN_TYPE_ESC = 1,
    CAN_TYPE_SERVO,
    CAN_TYPE_SENSOR,
    CAN_TYPE_SWITCH,
    CAN_TYPE_OSD,
    CAN_TYPE_UART,
    CAN_TYPE_HUB,
    CAN_TYPE_NUM
};
// data types
enum {
    CAN_DATA_GROUP = 1,
    CAN_DATA_TYPE,
    CAN_DATA_ID,
    CAN_DATA_INPUT_MODE,
    CAN_DATA_RUN_MODE,
    CAN_DATA_STATE,
    CAN_DATA_PARAM_ID,
    CAN_DATA_TELEM,
    CAN_DATA_VERSION,
    CAN_DATA_VALUE,
    CAN_DATA_PARAM_NAME1,
    CAN_DATA_PARAM_NAME2
};
typedef struct CAN_frame CAN_frame;

class MessageCreator {
public:
	MessageCreator();
	CAN_frame Create_ReqAddr(uint8_t,uint8_t);
	CAN_frame Create_SendACK();
	Session mySession;
	CAN_frame Create_Stream_double(uint8_t* value, uint8_t doc);
	CAN_frame Create_Stream_VEL(int16_t velN, int16_t velE, int16_t velD, int16_t speed, uint8_t doc);
	CAN_frame Create_Stream_DOP(uint8_t pDOP, uint8_t hDOP, uint8_t vDOP, uint8_t tDOP, uint8_t nDOP, uint8_t eDOP, uint8_t gDOP, uint8_t doc);
	CAN_frame Create_Stream_ACC(uint8_t satellites, uint8_t fix, uint8_t sAcc, uint8_t cAcc, uint8_t hAcc, uint8_t vAcc, int16_t heading, uint8_t doc);
	CAN_frame Create_Stream_int(uint8_t *value, uint8_t doc);
private:
	uint8_t uuid[4];
};

#endif /* MESSAGECREATOR_H_ */
