/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SKT_COMMAND_ARRAYS_H
#define	SKT_COMMAND_ARRAYS_H


#include "StringAndCommandArrays.h"


LorawanError_t RequestAppNonce();
LorawanError_t ReportAppNonceReceived();
LorawanError_t ComputeRealAppKey ();
LorawanError_t enter_skt_join_mode();


static const StringAndFunction array_of_skt_string_and_functions[] = {
	{ "RequestAppNonce", RequestAppNonce },
	{ "ReportAppNonceReceived", ReportAppNonceReceived },
	{ "ComputeRealAppKey", ComputeRealAppKey },
	{ "join", enter_skt_join_mode },
	{NULL},
};

static const StringAndCommandArrays array_of_skt_string_and_array[] =
{
	//{ "get", &debug_get_arrays },
	{NULL}
};


static const CommandArrays skt_command_arrays = 
//static const void* sys_command_arrays[2] = 
{ array_of_skt_string_and_functions, array_of_skt_string_and_array };



#endif	/* SKT_COMMAND_ARRAYS_H */

