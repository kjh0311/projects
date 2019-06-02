/*
 * File:   UART_PrintResult.c
 * Author: 김진희
 *
 * Created on 2017년 10월 20일 (금), 오후 8:00
 */

#include "UART_Print_Functions.h"
#include "mcc_generated_files/eusart1.h"
#include "debug_mode.h"


void UART_Put_Line(const char *string)
{
#ifdef DEBUG_MODE
	UART_Put_String(string);
	EUSART1_Write('\r');
    EUSART1_Write('\n');
#endif
}


void UART_Put_String(const char *string)
{
	#ifdef DEBUG_MODE
    char c;
    while (1) 
    {
        c  = *string;
        if ( c == '\0' )
        {
            //EUSART1_Write('\r');
            //EUSART1_Write('\n');
            break;
        }
        else
        {
            EUSART1_Write(c);
            string++;
        }        
    }
	#endif
}


void UART_Print_Result (LorawanError_t result) {
    #ifdef DEBUG_MODE
    char* result_string;
	char result_buffer[50];
    
    switch (result) {
        case OK:
            result_string = "ok";
            break;
        case NETWORK_NOT_JOINED:
            result_string = "not_joined";
            break;
        case MAC_STATE_NOT_READY_FOR_TRANSMISSION:
            result_string = "MAC_STATE_NOT_READY_FOR_TRANSMISSION";
            break;
        case INVALID_PARAMETER:
            result_string = "invalid_param";
            break;
        case KEYS_NOT_INITIALIZED:
            result_string = "KEYS_NOT_INITIALIZED";
            break;
        case SILENT_IMMEDIATELY_ACTIVE:
            result_string = "silent";
            break;
        case FRAME_COUNTER_ERROR_REJOIN_NEEDED:
            result_string = "frame_counter_err_rejoin_needed";
            break;
        case INVALID_BUFFER_LENGTH:
            result_string = "invalid_data_len";
            break;
        case MAC_PAUSED:
            result_string = "mac_paused";
            break;
        case NO_CHANNELS_FOUND:
            result_string = "no_free_ch";
            break;
        case INVALID_CLASS:
            result_string = "INVALID_CLASS";
            break;
        case MCAST_PARAM_ERROR:
            result_string = "MCAST_PARAM_ERROR";
            break;
        case MCAST_MSG_ERROR:
            result_string = "MCAST_MSG_ERROR";
            break;
    }
    
	sprintf(result_buffer, "%s\r\n", result_string);
    UART_Put_String(result_buffer);
	#endif
}


void UART_Put_Hex(uint8_t *data, uint8_t length)
{
	#ifdef DEBUG_MODE
    for (uint8_t i=0; i < length; i++)
	{
		EUSART1_Write(data[i]);
	}
	#endif
}