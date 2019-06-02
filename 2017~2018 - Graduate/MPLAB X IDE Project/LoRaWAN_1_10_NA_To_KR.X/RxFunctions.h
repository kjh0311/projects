/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RX_FUNCTIONS_H
#include "mcc_generated_files/LoRaWAN/lorawan.h"
#include <stdint.h>

void RxData(uint8_t* pData, uint8_t dataLength, OpStatus_t status);
void RxJoinResponse(bool status);


#endif	/* RX_FUNCTIONS_H */

