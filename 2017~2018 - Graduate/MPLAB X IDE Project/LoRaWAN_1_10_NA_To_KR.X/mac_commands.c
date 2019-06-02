/*
 * File:   mac_commands.c
 * Author: 김진희
 *
 * Created on November 8, 2017, 2:45 PM
 */


#include "mcc_generated_files/mcc.h"
#include "tokenize_string.h"
#include "translate_enum_parameter_and_excute_function.h"
#define BUFFER_SIZE 100
uint8_t LORAWAN_GetMaxPayloadSize (void);
void str_hex_to_value(char* buffer, char* param, uint8_t len);
uint8_t getBufferLengthForTX();



LorawanError_t mac_tx(TransmissionType_t confirmed, char* param) {
	uint8_t port;
	uint8_t buffer[BUFFER_SIZE];
	uint8_t size;	
	char* token, *next;	
	
	
	token = param;
    next = tokenize_string(token);	
	
	port = atoi(token);	
	size = strlen(next)/2 + strlen(next)%2; //(uint8_t) ceil(strlen(next)/2.0);	
	
	if ( size <= LORAWAN_GetMaxPayloadSize() ) {
		str_hex_to_value(buffer, next, size);	
		return LORAWAN_Send(confirmed, port, buffer, size);
	} else {
		return INVALID_BUFFER_LENGTH;
	}
}


uint8_t getBufferLengthForTX() {
	const uint8_t max_size = LORAWAN_GetMaxPayloadSize ();
	if ( BUFFER_SIZE < max_size ) {
		return BUFFER_SIZE;
	} else {
		return max_size;
	}
}



LorawanError_t mac_tx_cnf(char* param) {
	UART_Put_String("mac_tx_cnf\r\n");
	return mac_tx(CNF, param);
}


LorawanError_t mac_tx_uncnf(char* param) {
	return mac_tx(UNCNF, param);
}

LorawanError_t mac_join(char* param){
	StringAndValue table[] = {
		{ "abp", (ActivationType_t)ABP },
		{ "otaa", (ActivationType_t)OTAA },
		{NULL}
	};
	
	return translate_enum_parameter_and_excute_function(param, table, LORAWAN_Join);
}


LorawanError_t mac_save(char* param){
	return OK;
}