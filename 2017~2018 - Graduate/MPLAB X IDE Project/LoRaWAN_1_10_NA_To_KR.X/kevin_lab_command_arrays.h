/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef KEVIN_LAB_COMMAND_ARRAYS_H
#define	KEVIN_LAB_COMMAND_ARRAYS_H

#include "StringAndCommandArrays.h"


LorawanError_t kevin_lab_tx_sample(char* param);


static const StringAndFunction array_of_kevin_lab_tx_string_and_fucntions[] = {
	{ "sample", kevin_lab_tx_sample },
	{NULL}
};


static const CommandArrays kevin_lab_tx_arrays = { array_of_kevin_lab_tx_string_and_fucntions, NULL };


static const StringAndFunction array_of_kevin_lab_string_and_functions[] = {
	//{ "sleep", sys_sleep },	
	{NULL},
};

static const StringAndCommandArrays array_of_kevin_lab_string_and_array[] =
{
	//{ "get", &sys_get_arrays },	
	{ "tx", &kevin_lab_tx_arrays },
	{NULL}
};


static const CommandArrays kevin_lab_command_arrays = 
//static const void* sys_command_arrays[2] = 
{ array_of_kevin_lab_string_and_functions, array_of_kevin_lab_string_and_array };



#endif	/* KEVIN_LAB_COMMAND_ARRAYS_H */

