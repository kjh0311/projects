/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef STRING_AND_FUNCTION_H
#define	STRING_AND_FUNCTION_H

#include "tokenize_string.h"

typedef LorawanError_t (*Function)(char* param);
typedef struct {
	char* command_string;
	Function function;
} StringAndFunction;


#endif	/* STRING_AND_FUNCTION_H */

