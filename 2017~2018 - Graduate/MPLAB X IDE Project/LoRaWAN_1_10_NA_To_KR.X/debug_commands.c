/*
 * File:   debug_commands.c
 * Author: 김진희
 *
 * Created on 2017년 11월 9일 (목), 오후 11:09
 */


#include "mcc_generated_files/mcc.h"
void UART_Put_String(const char* buffer);
#include <stdio.h>



uint32_t g_recent_frequency;
uint8_t g_recent_data_rate;


LorawanError_t debug_get_recent_frequency() {
	char buffer[20];
	
	sprintf(buffer, "%lu\r\n", g_recent_frequency);
	UART_Put_String(buffer);
	
	return GETTER;
}


LorawanError_t debug_get_recent_data_rate() {
	char buffer[5];
	
	sprintf(buffer, "%u\r\n", g_recent_data_rate);
	UART_Put_String(buffer);
	
	return GETTER;
}
