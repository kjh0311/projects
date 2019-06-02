/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DATA_GET_SET_H
#define	DATA_GET_SET_H

//#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include "DataLength.h"

//void MacGetData(uint32_t addr, uint8_t len, ValueType type);
//void MacSetData(uint32_t addr, uint8_t len, ValueType type, char* param);

void SaveData(char* buffer, uint32_t addr, uint8_t len);
void LoadData(char* buffer, uint32_t addr, uint8_t len);



//#define START 0x00000000ULL;

typedef enum {
	NO_SAVE				= 0xFFFFFFFFULL,
	//START				= 0x00000000ULL,
	//START				= 0,
	addr_devaddr		= 0,
	addr_deveui			= addr_devaddr + len_devaddr,
	addr_appeui			= addr_deveui + len_deveui,
	addr_nwkskey		= addr_appeui + len_appeui,
	addr_appskey		= addr_nwkskey + len_nwkskey,
	addr_appkey			= addr_appskey + len_appskey,
	addr_sync			= addr_appkey + len_appkey,
	addr_pwridx			= addr_sync + len_sync,
	addr_dr				= addr_pwridx + len_pwridx,
	addr_rxdelay1		= addr_dr + len_dr,
	addr_rxdelay2		= addr_rxdelay1 + len_rxdelay1,
	addr_acceptDelay1	= addr_rxdelay2 + len_rxdelay2,
	addr_acceptDelay2	= addr_acceptDelay1 + len_acceptDelay1,
	addr_adr			= addr_acceptDelay2 + len_acceptDelay2,
} DataAddress;

#endif	/* DATA_GET_SET_H */

