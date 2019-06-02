/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef INTERPRET_UART_COMMAND_H
#define	INTERPRET_UART_COMMAND_H

#include "mcc_generated_files/mcc.h"
#include "StringAndCommandArrays.h"
#include "sys_command_arrays.h"
#include "mac_command_arrays.h"
#include "radio_command_arrays.h"
#include "region_command_arrays.h"
#include "debug_command_arrays.h"
#include "skt_command_arrays.h"
#include "kevin_lab_command_arrays.h"


/*
static const StringAndCommandArrays command_array_of_string_and_arrays[] = {
	{ "sys", &sys_command_arrays },
	{ "mac", &mac_command_arrays },
	{ "debug", &debug_command_arrays },
    { NULL }
};
*/



static const StringAndCommandArrays command_array_of_string_and_arrays[] = {
	{ "sys", &sys_command_arrays },
	{ "mac", &mac_command_arrays },
	//{ "radio", &radio_command_arrays },
	//{ "region", &region_command_arrays },
	{ "debug", &debug_command_arrays },
	{ "skt", &skt_command_arrays },
	{ "kevin_lab", &kevin_lab_command_arrays },
    { NULL }
};

#endif	/* INTERPRET_UART_COMMAND_H */

