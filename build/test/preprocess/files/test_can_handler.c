#include "src/can_handler.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




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

    can_message_builder(&can_msg.can_information, 

                                                 1

                                                                  , 

                                                                    1

                                                                                       , 0x005, (uint8_t*)&can_msg_data.byte_0, 8);

}





void test_CanInit(void){

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x03)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[2])), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x03)), (UNITY_INT)(UNITY_INT8 )((can_msg.payload[2])), (

   ((void *)0)

   ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_HEX8);

}





void test_CanMsgData(void){

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((MOTOR_CALIBRATE_DATA_ID)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[0])), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x02)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[1])), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x03)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[2])), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x04)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[3])), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x05)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[4])), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x06)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[5])), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x07)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[6])), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x00)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[7])), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_HEX8);

}





void test_CanMsgMultiple(void){

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((MOTOR_CALIBRATE_DATA_ID)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[0])), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_HEX8);

    can_msg_data.byte_0 = THRESHOLD_DATA_ID;

    can_message_builder(&can_msg.can_information, 

                                                 1

                                                                  , 

                                                                    1

                                                                                       , 0x005, (uint8_t*)&can_msg_data.byte_0, 8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((THRESHOLD_DATA_ID)), (UNITY_INT)(UNITY_INT8 )((can_msg.can_information.data[0])), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_HEX8);

}





void test_CanMsgError(void){

    

   _Bool 

        msg_error;

    msg_error = check_for_can_message_error(can_msg);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((msg_error)), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

}





void test_CanMsgDirection(void){

    

   _Bool 

        msg_error;

    msg_error = check_for_can_message_direction(can_msg);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((msg_error)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT);

}





void test_CanMsgCanID(void){

    uint16_t can_id;

    can_id = get_message_can_id(can_msg);

    UnityAssertEqualNumber((UNITY_INT)((0x005)), (UNITY_INT)((can_id)), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);

}





void test_CanMsgCanDataID(void){

    can_data_id_e can_data_id;

    can_data_id = get_can_message_data_id(can_msg.can_information.data);

    UnityAssertEqualNumber((UNITY_INT)((MOTOR_CALIBRATE_DATA_ID)), (UNITY_INT)((can_data_id)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

}
