/*
 * File:   converter_with_excuter.c
 * Author: 김진희
 *
 * Created on 2017년 11월 9일 (목), 오후 5:03
 */


#include "mac_get_set.h"
#include <stdio.h>


void excute_getter_function(void* getter, Buffer *pBuffer, uint8_t len, char* param);


void get_mac_property_and_print(NameLenGetterSetter* pNameLenGetterSetter, ValueType type, char* param)
{
    Buffer buffer;
    char converted[200];
    uint8_t len;
    void* getter;
        
    len = pNameLenGetterSetter->len;
    getter = pNameLenGetterSetter->getter;
    
    excute_getter_function(getter, &buffer, len, param);
    switch (type)
	{
        case HEX:
            //UART_Put_String("Read Hex");
            value_to_hex_str(converted, buffer.all, len);
            break;
        case DEC:
            value_to_dec_str(converted, &buffer, len);
            //sprintf(converted, "%u", buffer.byte4);
            break;
        case ON_OFF:
            if (buffer.byte1==1) {
                sprintf(converted, "on");
            } else {
                sprintf(converted, "off");
            }
            break;
		default:
			UART_Put_String(buffer.all);
			return;
    }

    //UART_Put_String("MacGetData Last Line Start\r\n");
    UART_Put_String(converted);
    //UART_Put_String("\r\nMacGetData Last Line End\r\n");
}


void little_endian_value_to_hex_str(char* converted, char* buffer, uint8_t len);
void big_endian_value_to_hex_str(char* converted, char* buffer, uint8_t len);

// len이 4보다 크면 리틀인디언, 4이히면 빅인디언으로
void value_to_hex_str(char* converted, char* buffer, uint8_t len)
{
    if ( len > 4 ) {
        little_endian_value_to_hex_str(converted, buffer, len);
    } else {
        big_endian_value_to_hex_str(converted, buffer, len);
    }
}

void little_endian_value_to_hex_str(char* converted, char* buffer, uint8_t len) {    
    for (int8_t i=0; i<len; i++) {
        sprintf(converted, "%02X", buffer[i]);
        converted+=2;
    }
}

void big_endian_value_to_hex_str(char* converted, char* buffer, uint8_t len) {    
    for (int8_t i=len-1; i>=0; i--) {
        sprintf(converted, "%02X", buffer[i]);
        converted+=2;
    }
}


// 빅인디언
void value_to_dec_str(uint8_t* converted, Buffer* pBuffer, uint8_t len) {

    switch (len) {
        case 4:
            sprintf(converted, "%lu", pBuffer->byte4);
            break;
        case 2:
            sprintf(converted, "%u", pBuffer->byte2);
            break;
        case 1:
            sprintf(converted, "%u", pBuffer->byte1);
            break;
    }
}



void str_hex_to_value(char* buffer, char* param, uint8_t len);
//void str_dec_to_value(Buffer* pBuffer, char* param);
char on_off_to_bool(char* param);
void excute_setter_function(void* setter, Buffer *pBuffer, uint8_t len);


void convert_and_excute_setter_function(NameLenGetterSetter* pNameLenGetterSetter, ValueType type, char* param) {
    Buffer buffer;
    uint8_t len = pNameLenGetterSetter->len;
    void* setter = pNameLenGetterSetter->setter;
	char* end_pointer;
    //SavingOrNot saving_or_not = pNameLenGetterSetter->saving_or_not;    
    
    switch (type) {
        case HEX:
            //UART_Put_String("HEX\r\n");
            str_hex_to_value(buffer.all, param, len);
            break;
        case DEC:
            buffer.byte4 = strtoul(param, &end_pointer, 10);
            break;
        case ON_OFF:
            buffer.byte1 = on_off_to_bool(param);
			break;
		default:
			buffer.pointer = param;
    }
        
    excute_setter_function(setter, &buffer, len);
}


#include <string.h>
uint8_t hex_char_to_value(char c);
// 뒷자리부터 채워야함(리틀인디언)
void little_endian_str_hex_to_value(uint8_t* buffer, char* param, uint8_t len);
void big_endian_str_hex_to_value(uint8_t* buffer, char* param, uint8_t len);


void str_hex_to_value(uint8_t* buffer, char* param, uint8_t len) {
    if (len > 4 ) {
        little_endian_str_hex_to_value(buffer, param, len);
    } else {
        big_endian_str_hex_to_value(buffer, param, len);
    }	
}


void little_endian_str_hex_to_value(uint8_t* buffer, char* param, uint8_t len) {
    const uint8_t str_last_idx = strlen(param)-1;    
    // 문자열의 인덱스
    int8_t i; // 인덱스는 unsigned를 쓰면 무한반복 됨
    int8_t j = str_last_idx;
    char test[20];    
    
    // unsigned 쓰면 무한반복
    for (i = len-1; i>=0; i--) {
        buffer[i] = hex_char_to_value(param[j]);
        if (j>0) {
            buffer[i] += hex_char_to_value(param[j-1])*16;
        }
        
        j-=2;
        if (j < 0) {
            i--;  // for문에 i--를 못 쓰게 되므로, 이렇게함.
            break;
        }
    }    
    for (; i>=0; i--)
    {
        buffer[i] = 0;
    }
}


void big_endian_str_hex_to_value(uint8_t* buffer, char* param, uint8_t len) {
    const uint8_t str_last_idx = strlen(param)-1;    
    // 문자열의 인덱스
    uint8_t i; // 인덱스는 unsigned를 쓰면 무한반복 됨
    int8_t j = str_last_idx;
    char test[100];
    
    // unsigned 쓰면 무한반복
    for (i = 0; i<len; i++) {
        buffer[i] = hex_char_to_value(param[j]);
        if (j>0) {
            buffer[i] += hex_char_to_value(param[j-1])*16;
        }
		
        j-=2;
		
        if (j < 0) {
            i++;
            break;
        }
    }
    
    for (; i<len; i++)
    {
        buffer[i] = 0;
    }
	
}


uint8_t hex_char_to_value(char c) {
    if ( c <= 57 )
        return c-48;
    else if ( c <= 70)
        return c-55;
    else
        return c-87;
}

char on_off_to_bool(char* param) {
    if ( str_equals (param, "on") ) {
        return 1;
    } else {
        return 0;
    }
}