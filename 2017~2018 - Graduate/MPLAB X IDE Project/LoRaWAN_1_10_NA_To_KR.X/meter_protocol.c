/* 
 * File:   meter_protocol.h
 * Author: hkyang
 *
 * Created on 2018년 1월 9일 (화), 오전 10:06
 */

//#include <xc.h>
//#include "mcc_generated_files/tmr1.h"
//#include "mcc_generated_files/eusart1.h"
//#include "mcc_generated_files/pin_manager.h"
//#include "mcc_generated_files/LoRaWAN/lorawan.h"
#include "mcc_generated_files/mcc.h"
#include "meter_protocol.h"
#include "led.h"
//#include "interrupt.h"
//#include "Interpret_UART_Command.h"


#define METER_READ_INTERVAL      5000 //ms

#define METER_COMMAND_BUFFER_LEN 100


#define WATT_REQUEST_LEN		8
#define OTHER_REQUEST_LEN		5



typedef struct {
    uint8_t water[OTHER_REQUEST_LEN];
    uint8_t hotwater[OTHER_REQUEST_LEN];
    uint8_t gas[OTHER_REQUEST_LEN];
    uint8_t CALORIE[OTHER_REQUEST_LEN];
	uint8_t watt[WATT_REQUEST_LEN];
} SensorRequestCommand;


typedef struct {
    uint8_t meter_msg_lenth;
    uint8_t meter_buffer[METER_COMMAND_BUFFER_LEN];
}
MeterReadBuffer_t;


extern void RxData(uint8_t* pData, uint8_t dataLength, OpStatus_t status);
extern void RxJoinResponse(bool status);
static uint8_t get_request_length(SensorType sensor_type);
//extern uint8_t sending;
//extern uint8_t receiving;

static MeterReadBuffer_t meterReadBuffer;

static SensorRequestCommand sensor_request_command = {
    {0xA5,0x02,0x05,0x5D,0xA6}, //water
    {0xA5,0x03,0x05,0x5C,0xA6}, //hotwater
    {0xA5,0x04,0x05,0x5B,0xA6}, //gas
    {0xA5,0x05,0x05,0x5A,0xA6}, //calorie
	{0x07,0x04,0x75,0x31,0x00,0x2C,0xBA,0x72} // watt
};


void meter_rs485_enable(void) {
    LATD6 = 1; // TX 
    //LATD5 = 1;	
}

void meter_rs485_disable(void) {
    LATD6 = 0; // RX
    //LATD5 = 0;
}


LorawanError_t meter_request_data(SensorType type)
{
    uint8_t request_len;
	uint8_t* pointer;
	
	// 8bit unit operation
	static const uint8_t* array_of_byte_pointer[] = {
		NULL, NULL, // type is not 0 or 1.
		sensor_request_command.water,
		sensor_request_command.hotwater,
		sensor_request_command.gas,
		sensor_request_command.CALORIE,
		sensor_request_command.watt
	};
	
	pointer = array_of_byte_pointer[ type ];
	request_len = get_request_length( type );

	for ( uint8_t i = 0; i < request_len; i++ )
	{
		LORAWAN_Mainloop();
        EUSART1_Write(pointer[i]);
    }
}


uint8_t get_length(SensorType sensor_type)
{
	switch (sensor_type)
	{
		case CALORIE:
			return CALORIE_METER_RESPONSE_SIZE;
		case WATT:
			return WATT_METER_RESPONSE_SIZE;
		default:
			return OTHER_METER_RESPONSE_SIZE;
	}
}


static uint8_t get_request_length(SensorType sensor_type)
{
	switch (sensor_type)
	{
		case WATT:
			return WATT_REQUEST_LEN;
		default:
			return OTHER_REQUEST_LEN;
	}
}