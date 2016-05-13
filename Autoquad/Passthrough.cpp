/*
 I will write something important here at some point..
 MMN - Mathias Mikkel Neerup manee12@student.sdu.dk
 */

#include <sstream>
#include <iostream>

#include "AutoQuad.h"
#include "Session.h"
#include "gps_conv.h"
#include "msgs/nmea.h"

#include <sstream>

#define LATITUDE_DOC   0x01
#define LONGITUDE_DOC  0x02
#define HDOP_DOC       0x03
#define FIX_DOC        0x04
#define SATTELITES_DOC 0x05
#define ALTITUDE_DOC   0x06


#define LOOP_RATE 10


#define MSG_RESET       1
#define MSG_OK_ADDR     2
#define MSG_TELEM_VALUE 3
#define MSG_TELEM_RATE  4

#define ST_ACKNOWLEDGED 1


class RegisterNode_node : public AutoQuad {
private:
	MessageCreator messageCreator;
	int last_msg;
	int state = 0;

	ros::Subscriber nmea_sub;
	msgs::nmea last_gps_msg;
	std::string topic_nmea_from_gps_sub;
public:
	RegisterNode_node(int argc, char** argv): AutoQuad(argc, argv){
		// UUID of this CAN node
		messageCreator.mySession.uuid = 0xAB;
		ros::NodeHandle nh("~");
		nh.param<std::string> ("nmea_from_device_sub", topic_nmea_from_gps_sub, "/fmData/nmea_from_gps");
		nmea_sub = nh.subscribe(topic_nmea_from_gps_sub, 1000, &RegisterNode_node::nmea_callback, this);
	}

	void onTimer(const ros::TimerEvent& event){
	}

	void spin(){
		ros::spin();
	}

	bool packet_to_me(int id = 0){
		int retval = false;
		// data packet: 1 EF CD AB 0 0 0 0   AB is uuid sent by this node
		int target_id = ((id & CAN_TID_MASK) >> (9-3));
		if( latest_packet.data[3] == messageCreator.mySession.getUuid() || messageCreator.mySession.source_id == target_id){
			retval = true;
		}
		return retval;
	}

	void recv_reset_msg() {
		ROS_WARN("Reset msg received");
		canMSG canMessage = messageCreator.Create_ReqAddr(CAN_TYPE_SENSOR, CAN_SENSORS_GPS_LAT);
		pub_recv.publish(canMessage);
		last_msg = MSG_RESET;
	}

	void recv_ok_addr_msg(int id) {
		if( packet_to_me() ){
			if(last_msg == MSG_RESET){
				ROS_INFO("Node got ack");
				messageCreator.mySession.updateSession(id);
				last_msg = MSG_OK_ADDR;
			}
		}
	}

	void recv_telem_value_msg(int id){
		if (packet_to_me(id)){
			if(last_msg == MSG_OK_ADDR){
				ROS_WARN("TELEM_VALUE");
				canMSG canMessage = messageCreator.Create_SendACK();
				pub_recv.publish(canMessage);
				last_msg = MSG_TELEM_VALUE;
			}
		}
	}
	void recv_telem_rate_msg(int id){
		if (packet_to_me(id)){
			if(last_msg == MSG_TELEM_VALUE){
				ROS_WARN("TELEM_RATE");
				canMSG canMessage = messageCreator.Create_SendACK();
				pub_recv.publish(canMessage);
				last_msg = MSG_TELEM_RATE;
				state = ST_ACKNOWLEDGED;
			}
		}
	}

	void nmea_callback(const msgs::nmea::ConstPtr& nmea_msg){
		// Latitude
		if(!nmea_msg->type.compare("GPGGA") && nmea_msg->valid == true) {

			double latitude = 0;
			double longitude = 0;
                        double altitude = 0;
			double hdop = 0;
			double fix = 0;
			double sattelites = 0;

			if(nmea_msg->data[1] != ""){
				latitude =  nmea_latlon( (char* ) nmea_msg->data[1].c_str() );
			}

			if(nmea_msg->data[3] != ""){
				 longitude = nmea_latlon( (char* ) nmea_msg->data[3].c_str() );
			}

			if(nmea_msg->data[8] != ""){
	                         altitude = atof( nmea_msg->data[8].c_str() );
			}

			if(nmea_msg->data[7] != ""){
				 hdop = atof( nmea_msg->data[7].c_str() );
			}

			if(nmea_msg->data[5] != ""){
				 fix = atof(nmea_msg->data[5].c_str() );
			}

			if(nmea_msg->data[6] != ""){
				 sattelites = atof( nmea_msg->data[6].c_str() );
			}


                        ROS_INFO("POS in lat: %f long: %f altitude: %f ", latitude ,longitude, altitude);

			if(state == ST_ACKNOWLEDGED){
				ROS_INFO("POS out");

				// Latitude
				canMSG canMessage = messageCreator.Create_Stream(latitude, LATITUDE_DOC);
				pub_recv.publish(canMessage);

				// Longitude
				canMessage = messageCreator.Create_Stream(longitude, LONGITUDE_DOC);
				pub_recv.publish(canMessage);

				 // HDOP
				canMessage = messageCreator.Create_Stream(hdop, HDOP_DOC);
				pub_recv.publish(canMessage);

				// FIX
				canMessage = messageCreator.Create_Stream(fix, FIX_DOC);
				pub_recv.publish(canMessage);

				// Sattelites
				canMessage = messageCreator.Create_Stream(sattelites, SATTELITES_DOC);
				pub_recv.publish(canMessage);

				// Altitude
				canMessage = messageCreator.Create_Stream(altitude, ALTITUDE_DOC);
				pub_recv.publish(canMessage);
			} else {
				ROS_WARN("Node not acknowledged");
			}
		 }
	}

};
int main(int argc, char **argv){
	AutoQuad* autoquad = new RegisterNode_node(argc, argv);


	autoquad->spin();
	return 0;
}
