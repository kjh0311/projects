/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TRANSLATE_ENUM_PARAMETER_AND_EXCUTE_FUNCTION_H
#define	TRANSLATE_ENUM_PARAMETER_AND_EXCUTE_FUNCTION_H
#include "mcc_generated_files/mcc.h"
//#include "Function.h"


typedef LorawanError_t (*EnumFunction)(uint8_t i);

typedef struct {
	char* string;
	uint8_t value;
} StringAndValue;


LorawanError_t translate_enum_parameter_and_excute_function(char* string_parameter, StringAndValue* array, EnumFunction function);


#endif	/* TRANSLATE_ENUM_PARAMETER_AND_EXCUTE_FUNCTION_H */

