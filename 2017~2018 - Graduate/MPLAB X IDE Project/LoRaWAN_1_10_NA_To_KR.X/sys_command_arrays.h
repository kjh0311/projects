/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SYS_COMMAND_ARRAYS_H
#define	SYS_COMMAND_ARRAYS_H

#include "StringAndCommandArrays.h"


LorawanError_t sys_sleep(char* param);
LorawanError_t sys_reset(char* param);
LorawanError_t sys_eraseFW(char* param);
LorawanError_t sys_factoryRESET(char* param);

//LorawanError_t sys_set(char* param);
LorawanError_t sys_get_ver(char* param);


static const StringAndFunction array_of_sys_get_string_and_fucntions[] = {
	{ "ver", sys_get_ver },
	{NULL}
};


static const CommandArrays sys_get_arrays = { array_of_sys_get_string_and_fucntions, NULL };


static const StringAndFunction array_of_sys_string_and_functions[] = {
	{ "sleep", sys_sleep },
	{ "reset", sys_reset },
	{ "eraseFW", sys_eraseFW },
	{ "factoryRESET", sys_factoryRESET },
	{NULL},
};

static const StringAndCommandArrays array_of_sys_string_and_array[] =
{
	{ "get", &sys_get_arrays },
	{NULL}
	//{ "set", NULL },
};


static const CommandArrays sys_command_arrays = 
//static const void* sys_command_arrays[2] = 
{ array_of_sys_string_and_functions, array_of_sys_string_and_array };



#endif	/* SYS_COMMAND_ARRAYS_H */

