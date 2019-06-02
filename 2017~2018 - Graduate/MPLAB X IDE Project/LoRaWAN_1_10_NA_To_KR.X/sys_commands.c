/*
 * File:   sys_commands.c
 * Author: 김진희
 *
 * Created on November 8, 2017, 12:50 PM
 */


#include "mcc_generated_files/mcc.h"
#include <stdio.h>




LorawanError_t sys_sleep(char* param) {
	
}
LorawanError_t sys_reset(char* param) {
	
}
LorawanError_t sys_eraseFW(char* param) {
	
}
LorawanError_t sys_factoryRESET(char* param) {
	
}

LorawanError_t sys_set(char* param) {
	
}



void UART_Put_String(const char* buffer);
LorawanError_t sys_get_ver(char* param) {
	char buffer [80];
	// 2903을 2483으로 바꿔서도 컴파일 해볼 것
    sprintf(buffer, "RN2483 0.9.8 %s %s\r\n", __DATE__, __TIME__);
    UART_Put_String(buffer);
	return GETTER;
}