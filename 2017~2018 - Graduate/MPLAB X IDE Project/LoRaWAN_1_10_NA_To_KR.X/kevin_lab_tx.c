/*
 * File:   kevin_lab_tx.c
 * Author: 김진희
 *
 * Created on 2018년 1월 9일 (화), 오후 5:40
 */


#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "kevin_lab_data_format.h"


void UART_Put_String(const char* buffer);



LorawanError_t kevin_lab_tx_sample(char* param)
{
	const char info[100];	
	const static char* sample_data
	// 1121234567890223456789012345678902234112345678123456781234123412121111
	= "a01201700000000000000002017120701020321234567898765432135724681500001b";
	uint8_t prev_dr, port;
	LorawanError_t result;
	
	
	prev_dr = LORAWAN_GetCurrentDataRate();
	LORAWAN_SetCurrentDataRate(4);
	
	sprintf(info, "Sending: %s\r\n", sample_data);	
	UART_Put_String(info);	
	
	port = rand()%223 +1;
	result = LORAWAN_Send(UNCNF, port, sample_data, 70);
	
	LORAWAN_SetCurrentDataRate(prev_dr);	
	return result;
}