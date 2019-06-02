/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RECENT_VARIABLES_H
#define	RECENT_VARIABLES_H

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/LoRaWAN/lorawan_eu.h"

extern uint32_t g_recent_frequency;
extern uint8_t g_recent_data_rate;
extern uint8_t g_fPort;
extern uint8_t *g_pseudoAppKey;
extern JoinAccept_t *g_joinAccept;
extern bool g_skt_joining_mode;
extern uint8_t g_copied_net_id[3];;


#endif	/* RECENT_VARIABLES_H */

