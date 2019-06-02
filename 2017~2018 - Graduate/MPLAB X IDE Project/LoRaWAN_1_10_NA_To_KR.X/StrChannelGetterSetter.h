/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef STR_CHANNEL_GETTER_SETTER_H
#define	STR_CHANNEL_GETTER_SETTER_H
#include <stdint.h>
#include <string.h>
#include "mcc_generated_files/LoRaWAN/lorawan.h"
//#include "ChannelFunctionPointer.h"
typedef LorawanError_t (*ChannelSetter)(uint8_t ch, char* param);
typedef void (*ChannelGetter)(uint8_t ch, char* buffer);

#define str_equals(a,b) (!strcmp(a,b))
typedef struct {
	char* string;
	ChannelGetter getter;
	ChannelSetter setter;
	//ChannelFunction function;
} StrChannelGetterSetter;

#endif	/* STR_CHANNEL_GETTER_SETTER_H */

