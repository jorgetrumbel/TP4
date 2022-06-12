/***************************************************************************//**
 @file	   
 @brief	   
 @author   AV
 ******************************************************************************/

#ifndef CAN_HANDLER_H_
#define CAN_HANDLER_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define DEVICE_CAN_ID													0x005

#define BROADCAST_CAN_ID												0x1FF

#define DEVICE_CAN_DIRECTION											CAN_MESSAGE_TX_NODE
#define DEVICE_CAN_DIRECTION_RECEPTION									CAN_MESSAGE_RX_NODE

#define CAN_RX_BUFFER_SIZE	                                            100

#define DATA_TYPE_BYTE_POS												0


#define CAN_MESSAGE_TX_MASTER true
#define CAN_MESSAGE_RX_MASTER false
#define CAN_MESSAGE_TX_NODE CAN_MESSAGE_RX_MASTER
#define CAN_MESSAGE_RX_NODE CAN_MESSAGE_TX_MASTER

#define CAN_MESSAGE_ERROR		true
#define CAN_MESSAGE_NO_ERROR	false

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

//CAN MESSAGE DATA IDs DEFINITIONS
typedef enum{
	COMMAND_TYPE_DATA_ID = 0x00,
	CONTROL_TORQUE_LIMIT_DATA_ID,
	CONTROL_MODE_DATA_ID,
	SET_POINT_DATA_ID,
	THRESHOLD_DATA_ID,
	HOLD_TIME_DATA_ID,
	TIMEOUT_DATA_ID,
	POSITION_MANUAL_CALIBRATION_DATA_ID,
	PID_CONSTANT_DATA_ID,
	ZERO_MODE_DATA_ID,
	DISCRETE_OUTPUT_DATA_ID,
	DISCRETE_INPUT_DATA_ID,
	MOTOR_CALIBRATE_DATA_ID,
	MOTOR_MANUAL_POWER_DATA_ID,
	MOTOR_MANUAL_SAVE_ACTUAL_POS_DATA_ID,
	MOTOR_MANUAL_MOVE_DATA_ID,
	MOTOR_MANUAL_MOVE_ABSOLUTE_DATA_ID,
	MOTOR_MANUAL_ROTATE_DATA_ID,
	MOTOR_MANUAL_TORQUE_DATA_ID,
	MOTOR_MANUAL_TORQUE_LIMIT_DATA_ID,
	MOTOR_MANUAL_FORCE_OUTPUT_DATA_ID,
	MOTOR_MANUAL_CHECK_CONFIG_DATA_ID,
	MOTOR_MANUAL_RUN_INSTRUCTION_DATA_ID,
	MONITOR_CURRENT_INSTRUCTION_DATA_ID,
	MONITOR_CURRENT_ENCODER_POSITION_DATA_ID,
	MONITOR_ERROR_DATA_ID,
	MESSAGE_CHANGE_OPERATION_MODE_DATA_ID,
	MESSAGE_SERVO_CAN_ID_DATA_ID
} can_data_id_e;

enum can_type {
	CAN_TYPE_DATA,  /*!< A DATA FRAME carries data from a transmitter to the
	                    receivers.*/
	CAN_TYPE_REMOTE /*!< A REMOTE FRAME is transmitted by a bus unit to request
	                     the transmission of the DATA FRAME with the same
	                     IDENTIFIER */
};

enum can_format {
	CAN_FMT_STDID, /*!< Standard Format, 11 bits identifier */
	CAN_FMT_EXTID  /*!< Extended Format, 29 bits identifier */
};

struct can_message {
	uint32_t        id;   /* Message identifier */
	enum can_type   type; /* Message Type */
	uint8_t *       data; /* Pointer to Message Data */
	uint8_t         len;  /* Message Length */
	enum can_format fmt;  /* Identifier format, CAN_STD, CAN_EXT */
};

typedef struct {
	struct can_message can_information;
	uint8_t payload[8];
}can_message_w_payload;

typedef enum{
    CAN_TX_MESSAGE_NOT_SENT,
	CAN_TX_MESSAGE_SENT} can_tx_sent_status_e;

typedef struct{
	uint8_t byte_0;
	uint8_t byte_1;
	uint8_t byte_2;
	uint8_t byte_3;
	uint8_t byte_4;
	uint8_t byte_5;
	uint8_t byte_6;
	uint8_t byte_7;
} can_message_data;
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 * @param message 
 * @param error_bit 
 * @param dir_bit 
 * @param message_9_bit_id 
 * @param message_data 
 * @param data_length 
 */
void can_message_builder(struct can_message* message, bool error_bit, bool dir_bit, uint16_t message_9_bit_id, uint8_t * message_data, uint8_t data_length);

/**
 * @brief 
 * 
 * @param message 
 * @return can_tx_sent_status_e 
 */
can_tx_sent_status_e can_message_send(struct can_message message);

/**
 * @brief 
 * 
 * @param message 
 * @return can_tx_sent_status_e 
 */
can_tx_sent_status_e can_force_send(struct can_message message);

/**
 * @brief 
 * 
 * @param rx_msg 
 * @return true 
 * @return false 
 */
bool check_for_can_message_error(can_message_w_payload rx_msg);

/**
 * @brief 
 * 
 * @param rx_msg 
 * @return true 
 * @return false 
 */
bool check_for_can_message_direction(can_message_w_payload rx_msg);

/**
 * @brief Get the message can id object
 * 
 * @param msg 
 * @return uint16_t 
 */
uint16_t get_message_can_id(can_message_w_payload msg);

/**
 * @brief Get the can message data id object
 * 
 * @param data_to_check 
 * @return can_data_id_e 
 */
can_data_id_e get_can_message_data_id(uint8_t* data_to_check);

/**
 * @brief Get the can message data byte object
 * 
 * @param message 
 * @param byte_num 
 * @return uint8_t 
 */
uint8_t get_can_message_data_byte(struct can_message message, uint8_t byte_num);

/*******************************************************************************
 ******************************************************************************/

#endif // CAN_HANDLER_H_
