/* 
 * File:   meter_protocol.h
 * Author: hkyang
 *
 * Created on 2018년 1월 9일 (화), 오전 10:06
 */

#include "SensorType.h"

#ifndef METER_PROTOCOL_H
#define	METER_PROTOCOL_H


#define METER_COMMAND_BUFFER_LEN 100
//#define METER_COMMAND_BUFFER_LEN 400


typedef struct {    
    uint8_t data[METER_COMMAND_BUFFER_LEN];
	uint8_t length, max_length;
}
MeterReadBuffer_t;


//void meter_request_data(SensorType sensorType);
LorawanError_t meter_request_data(SensorType sensorType);
//void meter_request_data2();
void meter_rs485_enable(void);
void meter_rs485_disable(void);
//void meter_Listen_And_Response();
//void meter_MainLoop(void);


#endif	/* METER_PROTOCOL_H */

