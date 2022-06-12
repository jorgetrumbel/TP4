/***************************************************************************//**
 @file     
 @brief	   
 @author   AV
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "can_handler.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define ID_9_BIT_POSITION	0x3FE

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static can_tx_sent_status_e tx_message_sent;							//Boolean indicator for sent CAN message

/*******************************************************************************
 *******************************************************************************
 GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void can_message_builder(struct can_message* message, bool error_bit, bool dir_bit, uint16_t message_9_bit_id, uint8_t * message_data, uint8_t data_length){
	message->id = (message_9_bit_id << 1) & ID_9_BIT_POSITION;
	message->id |= error_bit << 10;
	message->id |= dir_bit;
	message->fmt  = CAN_FMT_STDID;
	
	message->type = CAN_TYPE_DATA;
	message->data = message_data;
	message->len  = data_length;
}

can_tx_sent_status_e can_message_send(struct can_message message){
	can_tx_sent_status_e ret_val = CAN_TX_MESSAGE_NOT_SENT;
	if(CAN_TX_MESSAGE_SENT == tx_message_sent){
		//can_async_write(&CAN_Servo_bus, &message);
		tx_message_sent = CAN_TX_MESSAGE_NOT_SENT;
		ret_val = CAN_TX_MESSAGE_SENT;
	}
	return ret_val;
}

can_tx_sent_status_e can_force_send(struct can_message message){
	can_tx_sent_status_e ret_val = CAN_TX_MESSAGE_NOT_SENT;
	while(CAN_TX_MESSAGE_NOT_SENT == tx_message_sent){
	}
	tx_message_sent = CAN_TX_MESSAGE_NOT_SENT;
	ret_val = CAN_TX_MESSAGE_SENT;
	//can_async_write(&CAN_Servo_bus, &message);
	return ret_val;
}

bool check_for_can_message_error(can_message_w_payload rx_msg){
	return (rx_msg.can_information.id & 0x400);
}

bool check_for_can_message_direction(can_message_w_payload rx_msg){
	return (rx_msg.can_information.id & 0x001);
}

uint16_t get_message_can_id(can_message_w_payload msg){
	return (msg.can_information.id & 0x3FE);
}

can_data_id_e get_can_message_data_id(uint8_t* data_to_check){
	return (can_data_id_e)*(data_to_check);
}

uint8_t get_can_message_data_byte(struct can_message message, uint8_t byte_num){
	if(byte_num > 7)
		byte_num = 7; 
	return *(message.data + byte_num);
}
/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/

