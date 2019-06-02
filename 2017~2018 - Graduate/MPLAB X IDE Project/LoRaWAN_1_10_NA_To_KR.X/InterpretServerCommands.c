/*
 * File:   InterpretServerCommands.c
 * Author: 김진희
 *
 * Created on 2018년 6월 18일 (월), 오후 3:07
 */


#define AUTO_SENDING			1
#define LED						2
#define SKT_COMMANDS			0xDF



//#include <xc.h>
#include <stdio.h>
#include <stdint.h>
//#include "mcc_generated_files/mcc.h"



char* rx_data_to_string (uint8_t* pData, uint8_t dataLength);


char* SendingControl (uint8_t* pData, uint8_t data_length);
char* LedControl(uint8_t* pData, uint8_t data_length);
void InterpretSktJoinMessage (uint8_t *message);


char* InterpretServerCommands (uint8_t* pData, uint8_t data_length)
{
	uint8_t fPort = pData[0];
	pData++;
	data_length--;
	
	switch (fPort)
	{
		case AUTO_SENDING:
			return SendingControl (pData, data_length);
		case LED:
			return LedControl (pData, data_length);
		case SKT_COMMANDS:
			InterpretSktJoinMessage(pData);
			return "skt data received";
		default:
			return rx_data_to_string (pData, data_length);
	}	
}


char* rx_data_to_string(uint8_t* pData, uint8_t dataLength)
{
	static char buffer[50];
	uint8_t len;
	char* data_start_ptr;	
	
	len = sprintf(buffer, "mac_rx %d", pData[0]);
	data_start_ptr = buffer + len;
	//띄어쓰기 포함
	for (uint8_t i=1; i<dataLength; i++) {
		len = sprintf(data_start_ptr, " %02X", pData[i]);
		data_start_ptr+=len;
		//data_start_ptr[i] = pData[i];
	}	
	return buffer;
}