/*
 * File:   validate_head_data.c
 * Author: 김진희
 *
 * Created on 2018년 2월 16일 (금), 오후 2:49
 */


#include "SensorType.h"
#include <stdint.h>
#include "mcc_generated_files/mcc.h"

#define METER_READ_COUNT	100000

uint8_t EUSART1_Read(void);
void EUSART1_Write(uint8_t txData);

uint8_t read_byte();
static uint8_t* get_head_sequence(SensorType sensor_type);
extern uint8_t receiving;


uint8_t validate_head_data(SensorType sensor_type)
{	
	uint8_t byte;
	uint8_t* head_sequence = get_head_sequence(sensor_type);
	uint8_t received_data[3];
	uint32_t j=0;	
	
	//EUSART1_Write(0x03);
	for (uint8_t i=0; i<HEADER_LENGTH; i++)
	{
		uint8_t received = 0;
		for (uint32_t j=0; j<METER_READ_COUNT; j++)
		//for (uint32_t j=0;  j<1000; j++)
		//while( 1 )
		{			
			//__delay_ms(1);
			LORAWAN_Mainloop();
			if ( eusart1RxCount )
			{				
				received_data[i] = EUSART1_Read();
				received = 1;
				break;
			}			
		}
		
		if (received)
		{
			received = 0;
		}
		else
		{
			return 0;
		}
	}
	
	//EUSART1_Write(0x04);
	return 1;
}



static uint8_t* get_head_sequence(SensorType sensor_type)
{
	static const uint8_t watt_head[HEADER_LENGTH] = { 0x07, 0x04, 0x75 };
	// 0x00 must be replaced
	static uint8_t other_head[HEADER_LENGTH] = { 0xB5, 0x00, 0x12 };
	
	switch (sensor_type)
	{
		case WATT:
			return watt_head;
		default:			
			other_head[1] = sensor_type;
			return other_head;
	}
}
