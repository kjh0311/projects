/*
 * File:   translate_enum_parameter_and_excute_function.c
 * Author: 김진희
 *
 * Created on 2017년 11월 9일 (목), 오후 3:04
 */


#include "translate_enum_parameter_and_excute_function.h"
#define str_equals(a,b) (!strcmp(a,b))


LorawanError_t translate_enum_parameter_and_excute_function(char* string_parameter, StringAndValue* array, EnumFunction function)
{
	for ( uint8_t i=0; array[i].string!=NULL; i++) {
		
		if (str_equals(string_parameter, array[i].string)) {		
			return function(array[i].value);
		}
	}
	
	return function(0);
}
