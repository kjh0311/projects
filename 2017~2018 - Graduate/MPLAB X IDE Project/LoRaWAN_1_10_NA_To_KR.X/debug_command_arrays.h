/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DEBUG_COMMAND_ARRAYS_H
#define	DEBUG_COMMAND_ARRAYS_H


#include "StringAndCommandArrays.h"


LorawanError_t debug_get_recent_frequency();
LorawanError_t debug_get_recent_data_rate();


static const StringAndFunction array_of_debug_get_string_and_functions[] = {
	{ "recent_frequency", debug_get_recent_frequency },
	{ "recent_data_rate", debug_get_recent_data_rate },
	{NULL}
};

static const StringAndCommandArrays array_of_debug_get_string_and_array[] =
{
	{NULL}
};


static const CommandArrays debug_get_arrays = 
{ array_of_debug_get_string_and_functions, array_of_debug_get_string_and_array };



static const StringAndFunction array_of_debug_string_and_functions[] = {
	{NULL},
};

static const StringAndCommandArrays array_of_debug_string_and_array[] =
{
	{ "get", &debug_get_arrays },
	{NULL}
	//{ "set", NULL },
};


static const CommandArrays debug_command_arrays = 
//static const void* sys_command_arrays[2] = 
{ array_of_debug_string_and_functions, array_of_debug_string_and_array };



#endif	/* DEBUG_COMMAND_ARRAYS_H */

