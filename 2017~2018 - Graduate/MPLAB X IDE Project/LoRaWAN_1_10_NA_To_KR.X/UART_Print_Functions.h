/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART_PRINT_FUNCTIONS_H
#define	UART_PRINT_FUNCTIONS_H

#include "mcc_generated_files/LoRaWAN/lorawan.h"
#include <stdio.h>

void UART_Put_Line(const char *string);
void UART_Put_String(const char *string);
void UART_Print_Result (LorawanError_t result);
void UART_Put_Hex(uint8_t *data, uint8_t length);


#endif	/* UART_PRINT_FUNCTIONS_H */

