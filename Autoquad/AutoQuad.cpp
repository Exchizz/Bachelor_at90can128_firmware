#include "AutoQuad.h"

AutoQuad::AutoQuad(int argc, char** argv){

}

void AutoQuad::can_callback(const msgs::can::ConstPtr& can_msg){
	unsigned int id = can_msg->id;
	//auto
	latest_packet = *can_msg;

//	std::cout << "-------------------------------------" << std::endl;
	switch(id & CAN_FID_MASK){
	case CAN_FID_GRANT_ADDR:
//		ROS_WARN("Recv. Grant ADDR");
		//printf("\tFrom AQ to ESC32: UUID: %X %X %X %X\n", latest_data[3], latest_data[2], latest_data[1], latest_data[0]);
		recv_ok_addr_msg(id);
		break;

	case CAN_FID_RESET_BUS:
//		ROS_WARN("Recv. RESET MSG");
		recv_reset_msg();
		break;
	case CAN_FID_CMD:
	{
		switch((id & CAN_DOC_MASK) >> (19-3)){
		case CAN_CMD_TELEM_RATE:
		{
			int rate = latest_packet.data[0]; // rate transmittet as 8 bit
//			ROS_WARN("From AQ to ESC32: %d", rate);
			recv_telem_rate_msg(id);
		}
		break;

		case CAN_CMD_TELEM_VALUE:
			recv_telem_value_msg(id);
			break;
		case CAN_CMD_SETPOINT16:
//			ROS_WARN("Recv. SETPOINT16");
			break;
		case CAN_CMD_DISARM:
//			ROS_WARN("Recv. CAN DISARM");
			break;

		default:
//			ROS_WARN("Recv: Unknown function id command: %X", (id & CAN_DOC_MASK) >> (19 - 3));
		break;
		}
	}
	break;

	case CAN_FID_REQ_ADDR:
//		ROS_WARN("Recv. REQUEST ADDRESS");
//		printf("\tFrom ESC32 to AQ: UUID: %X %X %X %X\n", latest_data[3], latest_data[2], latest_data[1], latest_data[0]);
		break;
	case CAN_FID_GET:
//		ROS_WARN("Recv. GET, %d", (id & CAN_DOC_MASK) >> (19-3));
		switch( (id & CAN_DOC_MASK) >> (19-3) ){
		case CAN_DATA_VERSION:
//			printf("\t CAN_DOC_VERSION");
			break;
		case CAN_DATA_PARAM_NAME1:
//			printf("\t CAN_DOC_PARAM_NAME1");
			break;
		default:
//			printf("\tUnknown latest_data mask(%X, %d)\n", (id & CAN_DOC_MASK) >> (19-3),(id & CAN_DOC_MASK) >> (19-3));
			break;
		}
		break;
		case CAN_FID_ACK:
//			ROS_WARN("Recv. ACK");
			break;
		case CAN_FID_TELEM:
//			ROS_WARN("Recv. Telemetry-value");
		case CAN_FID_REPLY:
//			ROS_WARN("Recv. REPLY");
			switch((id & CAN_DOC_MASK) >> (19-3)){
			case CAN_DATA_VERSION:
//				printf("\tCAN_DOC_VERSION: %s\n", (char*)&latest_data);
				break;
			default:
//				printf("\tUnknown latest_data mask(%X, %d)\n", id & CAN_DOC_MASK >> (19-3),id & CAN_DOC_MASK >> (19-3));
			break;
			}
			break;
			case CAN_FID_SET:
//				ROS_WARN("Recv. SET");
				break;

			default:
//				ROS_WARN("Recv. Received unhandled message %X", (id & CAN_FID_MASK) >> (25-3));
//				ROS_WARN("\t fid: %X", id & CAN_FID_MASK);
				break;
	}


//	printf("\tTarget Id: %d \n", ((id & CAN_TID_MASK) >> (9-3)));
//	printf("\tSource Id: %d \n", (id & CAN_SID_MASK) >> (14-3));
//	printf("\tSequence Id: %d \n", (id & CAN_SEQ_MASK) );
//	printf("\tlatest_data: %X %X %X %X %X %X %X %X\n", latest_data[7], latest_data[6], latest_data[5], latest_data[4],latest_data[3], latest_data[2], latest_data[1], latest_data[0]);

	switch(latest_packet.data[4]){
	case CAN_TYPE_ESC:
//		printf("\tType: CAN_TYPE_ESC\n");
		break;
	}
//	printf("\tCan ID(hardcoded): %d \n", latest_data[5]);
//	std::cout << "\tTarget type: ";
	switch(id & CAN_TT_MASK){
	case CAN_TT_GROUP:
//		std::cout << "Group";
		break;
	case CAN_TT_NODE:
//		std::cout << "Node";
		break;
	}
//	std::cout << std::endl;
//	std::cout << "\tLogic communications channel: ";
	switch(id & CAN_LCC_MASK){
	case CAN_LCC_EXCEPTION:
//		std::cout << "Exception";
		break;
	case CAN_LCC_HIGH:
//		std::cout << "High";
		break;
	case CAN_LCC_NORMAL:
//		std::cout << "Normal";
		break;
	case CAN_LCC_INFO:
//		std::cout << "Info";
		break;
	}
//	std::cout << std::endl;
}
