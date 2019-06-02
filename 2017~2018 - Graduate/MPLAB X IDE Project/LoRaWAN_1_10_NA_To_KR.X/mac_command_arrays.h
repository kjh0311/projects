/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAC_COMMAND_ARRAYS_H
#define	MAC_COMMAND_ARRAYS_H


#include "mcc_generated_files/mcc.h"
#include "StringAndCommandArrays.h"


LorawanError_t mac_tx_cnf(char* param);
LorawanError_t mac_tx_uncnf(char* param);
LorawanError_t mac_join(char* param);
LorawanError_t mac_save(char* param);
LorawanError_t mac_set(char* param);
LorawanError_t mac_get(char* param);


static const StringAndFunction mac_tx_string_and_functions[] = {
	{ "cnf", mac_tx_cnf },
	{ "uncnf", mac_tx_uncnf },
};


static const CommandArrays mac_tx_arrays = { mac_tx_string_and_functions, NULL };


static const StringAndFunction array_of_mac_string_and_functions[] = {
	{ "reset", LORAWAN_Reset },
	
	{ "join", mac_join },
	{ "save", mac_save },
	{ "forceENABLE", LORAWAN_ForceEnable },
	{ "pause", LORAWAN_Pause },
	{ "resume", LORAWAN_Resume },
	{ "set", mac_set },
	{ "get", mac_get },
	{NULL},
};


static const StringAndCommandArrays array_of_mac_string_and_arrays[] = {
	{ "tx", &mac_tx_arrays },
};


//static c




static const CommandArrays mac_command_arrays = 
{ array_of_mac_string_and_functions, array_of_mac_string_and_arrays };


#endif	/* MAC_COMMAND_ARRAYS_H */

