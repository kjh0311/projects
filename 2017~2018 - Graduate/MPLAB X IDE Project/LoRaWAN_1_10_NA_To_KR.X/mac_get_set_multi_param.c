/*
 * File:   mac_get_set_multi_param.c
 * Author: 김진희
 *
 * Created on 2017년 10월 30일 (월), 오후 12:53
 * 
 * mac_set_get의 함수 중에서 라이브러리 함수의 파라미터가 2개 이상이어서,
 * 라이브러리 함수를 직접 호출하지 않을 때 진입하는 부분
 */

#include "UART_Print_Functions.h"
#include "tokenize_string.h"
#include "mcc_generated_files/mcc.h"
#include "StringAndFunction.h"
#include "StrChannelGetterSetter.h"



LorawanError_t mac_set_rx2(char* param) {
	//UART_Put_String(param);
	char *token = param;
	char *next = tokenize_string(token);
	uint8_t dr = atoi(token);
	//uint8_t dr = strtoul(token, &token, 10);
	// 2바이트 넘는 것들은 다 이렇게
	uint32_t freq = strtoul(next, &token, 10);
	
	/*
	char buffer[20];
	sprintf(buffer, "dr: %d freq: %ld\r\n", dr, freq);
	UART_Put_String(buffer);
	*/
	// 위 테스트코드 실행하면 망가짐.
	
	return LORAWAN_SetReceiveWindow2Parameters(freq, dr);	
}


void mac_get_rx2(char* buffer) {
	uint8_t dr;
	uint32_t freq;
	
	LORAWAN_GetReceiveWindow2Parameters(&freq, &dr);
	sprintf(buffer, "%d %ld", dr, freq);
}



#define NUMBER_OF_PROPERTY 4


void mac_get_freq(uint8_t ch, char* buffer);
void mac_get_drrange(uint8_t ch, char* buffer);
void mac_get_status(uint8_t ch, char* buffer);
void mac_get_dcycle(uint8_t ch, char* buffer);


LorawanError_t mac_set_freq(uint8_t ch, char* param);
LorawanError_t mac_set_drrange(uint8_t ch, char* param);
LorawanError_t mac_set_status(uint8_t ch, char* param);
LorawanError_t mac_set_dcycle(uint8_t ch, char* param);



static StrChannelGetterSetter str_channel_getter_setter[NUMBER_OF_PROPERTY] = {
	{"freq", mac_get_freq, mac_set_freq},
	{"drrange", mac_get_drrange, mac_set_drrange},
	{"status", mac_get_status, mac_set_status},
	//{"dcycle", mac_get_dcycle, mac_set_dcycle}
};


LorawanError_t mac_get_or_set_ch(char* buffer, char* param);


LorawanError_t mac_set_ch(char* param) {
	return mac_get_or_set_ch(NULL, param);
}

void mac_get_ch(char* buffer, char* param) {
	mac_get_or_set_ch(buffer, param);
}

// buffer가 NULL이면 Setter
LorawanError_t mac_get_or_set_ch(char* buffer, char* param) {
	uint8_t ch;	
	char* str_prop = param;
	char* str_channel = tokenize_string(str_prop);
	param = tokenize_string(str_channel);
	
	ch = atoi(str_channel);
	
	for (int8_t i=0; i<NUMBER_OF_PROPERTY; i++) {
		if (str_equals(str_prop, str_channel_getter_setter[i].string)) {
			if (buffer == NULL) {
				return str_channel_getter_setter[i].setter(ch, param);
			} else {
				str_channel_getter_setter[i].getter(ch, buffer);
				return OK;
			}			
		}
	}
}


// 프로토콜에 이런 함수는 없음
LorawanError_t mac_set_freq(uint8_t ch, char* param) {
	//uint32_t freq = atoi(param);
	return OK;
}

// lorawan_private.h의 300줄과 동일함
typedef union {
	uint8_t value;
	struct {
		unsigned min :4;
		unsigned max :4; // MSB
	};
}DataRange;

// max가 더 작은 수임
// The first four bits, MSB, are representing the maximum value and the last four bits, LSB, are the minimum value.
LorawanError_t mac_set_drrange(uint8_t ch, char* param) {
	char* str_min = param;
	char* str_max = tokenize_string(str_min);
	DataRange dr;
	
	dr.min = atoi(str_min);
	dr.max = atoi(str_max);
	
	/*
	char buffer[20];
	sprintf(buffer, "min: %d max: %d\r\n", dr.min, dr.max);
	UART_Put_String(buffer);
	*/
	
	return LORAWAN_SetDataRange(ch, dr.value);
}


LorawanError_t mac_set_status(uint8_t ch, char* param) {
	bool value;
	
	if (str_equals(param, "on")) {
		value = true;
	} else {
		value = false;
	}
	
	return LORAWAN_SetChannelIdStatus(ch, value);
}


void mac_get_freq(uint8_t ch, char* buffer) {
	uint32_t freq;
	freq = LORAWAN_GetFrequency(ch);
	sprintf(buffer, "%ld", freq);
}

// The first four bits, MSB, are representing the maximum value and the last four bits, LSB, are the minimum value.
void mac_get_drrange(uint8_t ch, char* buffer) {
	DataRange dr;
	
	dr.value = LORAWAN_GetDataRange(ch);
	sprintf(buffer, "%d %d", dr.min, dr.max );
}


void mac_get_status(uint8_t ch, char* buffer) {
	bool value;
	
	value = LORAWAN_GetChannelIdStatus(ch);
	if (value == true) {
		sprintf(buffer, "on");
	} else {
		sprintf(buffer, "off");
	}
}


/*
void mac_get_dcycle(uint8_t ch, char* buffer) {
	uint16_t rv = LORAWAN_GetDutyCycle(ch);
	sprintf(buffer, "%d", rv);
}


LorawanError_t mac_set_dcycle(uint8_t ch, char* param) {
	uint16_t value = atoi(param);
	return LORAWAN_SetDutyCycle(ch, value);
}
*/

