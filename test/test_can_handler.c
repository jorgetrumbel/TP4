#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include "can_handler.h"

static can_message_w_payload can_msg;
static can_message_data can_msg_data;

void setUp(void){
    can_msg.can_information.data = can_msg.payload;
    can_msg_data.byte_0 = MOTOR_CALIBRATE_DATA_ID;
    can_msg_data.byte_1 = 0x02;
    can_msg_data.byte_2 = 0x03;
    can_msg_data.byte_3 = 0x04;
    can_msg_data.byte_4 = 0x05;
    can_msg_data.byte_5 = 0x06;
    can_msg_data.byte_6 = 0x07;
    can_message_builder(&can_msg.can_information, CAN_MESSAGE_ERROR, CAN_MESSAGE_RX_NODE, DEVICE_CAN_ID, (uint8_t*)&can_msg_data.byte_0, 8);
}

//Se corrobora la correcta inicializacion
void test_CanInit(void){
    TEST_ASSERT_EQUAL_HEX8(0x03, can_msg.can_information.data[2]);
    TEST_ASSERT_EQUAL_HEX8(0x03, can_msg.payload[2]);
}

//Se puede construir un mensaje con la informacion deseada
void test_CanMsgData(void){
    TEST_ASSERT_EQUAL_HEX8(MOTOR_CALIBRATE_DATA_ID, can_msg.can_information.data[0]);
    TEST_ASSERT_EQUAL_HEX8(0x02, can_msg.can_information.data[1]);
    TEST_ASSERT_EQUAL_HEX8(0x03, can_msg.can_information.data[2]);
    TEST_ASSERT_EQUAL_HEX8(0x04, can_msg.can_information.data[3]);
    TEST_ASSERT_EQUAL_HEX8(0x05, can_msg.can_information.data[4]);
    TEST_ASSERT_EQUAL_HEX8(0x06, can_msg.can_information.data[5]);
    TEST_ASSERT_EQUAL_HEX8(0x07, can_msg.can_information.data[6]);
    TEST_ASSERT_EQUAL_HEX8(0x00, can_msg.can_information.data[7]);
}

//Se puede trabajar con varios mensajes en serie (la estructura es reutilizable)
void test_CanMsgMultiple(void){
    TEST_ASSERT_EQUAL_HEX8(MOTOR_CALIBRATE_DATA_ID, can_msg.can_information.data[0]);
    can_msg_data.byte_0 = THRESHOLD_DATA_ID;
    can_message_builder(&can_msg.can_information, CAN_MESSAGE_ERROR, CAN_MESSAGE_RX_NODE, DEVICE_CAN_ID, (uint8_t*)&can_msg_data.byte_0, 8);
    TEST_ASSERT_EQUAL_HEX8(THRESHOLD_DATA_ID, can_msg.can_information.data[0]);
}

//Se puede obtener de un mensaje el estado de error
void test_CanMsgError(void){
    bool msg_error;
    msg_error = check_for_can_message_error(can_msg);
    TEST_ASSERT_EQUAL(CAN_MESSAGE_ERROR, msg_error);
}

//Se puede obtener de un mensaje la direccion (Recepcion o transmision)
void test_CanMsgDirection(void){
    bool msg_error;
    msg_error = check_for_can_message_direction(can_msg);
    TEST_ASSERT_EQUAL(CAN_MESSAGE_RX_NODE, msg_error);
}

//Se puede obtener de un mensaje el CAN ID
void test_CanMsgCanID(void){
    uint16_t can_id;
    can_id = get_message_can_id(can_msg);
    TEST_ASSERT_EQUAL(DEVICE_CAN_ID, can_id);
} 

//Se puede obtener de un mensaje el tipo de mensaje segun un ID
void test_CanMsgCanDataID(void){
    can_data_id_e can_data_id;
    can_data_id =  get_can_message_data_id(can_msg.can_information.data);
    TEST_ASSERT_EQUAL(MOTOR_CALIBRATE_DATA_ID, can_data_id);
} 
