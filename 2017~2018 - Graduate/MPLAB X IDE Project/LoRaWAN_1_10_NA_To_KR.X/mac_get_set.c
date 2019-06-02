/*
 * File:   mac_get_set.c
 * Author: 김진희
 *
 * Created on 2017년 11월 9일 (목), 오후 3:30
 */


#include "mac_get_set.h"
#include "tokenize_string.h"
#include "UART_Print_Functions.h"


typedef enum { FOUND, NOT_FOUND } FoundOrNot;
typedef void (*Excuter)(NameLenGetterSetter* pNameLenGetterSetter, ValueType type, char* param);
void get_mac_property_and_print(NameLenGetterSetter* pNameLenGetterSetter, ValueType type, char* param);
void convert_and_excute_setter_function(NameLenGetterSetter* pNameLenGetterSetter, ValueType type, char* param);
void mac_get_or_set(char* param, Excuter func_get_or_set);
FoundOrNot find_prop_and_excute(char* token, Props* p_props, Excuter excuter, char* next);




LorawanError_t mac_get(char* param) {    
    mac_get_or_set(param, get_mac_property_and_print);
	return GETTER;
}

LorawanError_t mac_set(char* param) {
    mac_get_or_set(param, convert_and_excute_setter_function);
	return PRINTED;
}


void mac_get_or_set(char* param, Excuter excuter)
{
    char* token, *next;
    char str[20];
    FoundOrNot found_or_not = NOT_FOUND;
    
    token = param;
    next = tokenize_string(token);
	//UART_Put_String(token);
	//UART_Put_String(next);
    
    for (int8_t i=0; i<NUM_PROP_CLASS; i++)
	{
        found_or_not = find_prop_and_excute(token, props_array + i, excuter, next);        
        if ( found_or_not == FOUND )
		{
            return;
        }
    }
    
    UART_Put_String("err");
}


FoundOrNot find_prop_and_excute(char* token, Props* p_props, Excuter excuter, char* next)
{
    uint8_t array_len = p_props->array_len;
    NameLenGetterSetter* name_len_getter_setter_array = p_props->name_len_getter_setter_array;
    ValueType type = p_props->type;    
	
    
    for (uint8_t i=0; i<array_len; i++)
	{
        if (str_equals( token, name_len_getter_setter_array[i].name ) )
		{
			// excuter : [get_mac_property_and_print] or [convert_and_excute_setter_function]
            excuter(name_len_getter_setter_array + i, type, next);
            return FOUND;
        }
    }

    return NOT_FOUND;
}