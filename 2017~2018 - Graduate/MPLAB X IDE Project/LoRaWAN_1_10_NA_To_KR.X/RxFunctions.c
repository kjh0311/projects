/*
 * File:   RxFunctions.c
 * Author: 김진희
 *
 * Created on 2017년 10월 20일 (금), 오후 10:11
 */


#include "RxFunctions.h"
#include "mcc_generated_files/LoRaWAN/lorawan_private.h"
#include "UART_Print_Functions.h"
#include <stdio.h>

/*
    MAC_NOT_OK = 0,     //LoRaWAN operation failed
    MAC_OK,             //LoRaWAN operation successful
    RADIO_NOT_OK,       //Radio operation failed
    RADIO_OK,           //Radio operation successful
    INVALID_BUFFER_LEN, //during retransmission, we have changed SF and the buffer is too large
    MCAST_RE_KEYING_NEEDED
*/



char* InterpretServerCommands (uint8_t* pData, uint8_t dataLength);

void RxData (uint8_t* pData, uint8_t dataLength, OpStatus_t status)
{
	char* result_string;	
    switch(status) {
		case MAC_NOT_OK:
			result_string = "mac_err";
			break;
		case MAC_OK:
			if (pData==NULL)
			{
				result_string = "mac_tx_ok";
			}
			else
			{
				result_string = InterpretServerCommands (pData, dataLength);
			}
			break;
		case RADIO_NOT_OK:
			result_string = "RADIO_NOT_OK";
			break;
		case RADIO_OK:
			result_string = "RADIO_OK";
			break;
		case INVALID_BUFFER_LEN:
			result_string = "invalid_data_len";
			break;
		case MCAST_RE_KEYING_NEEDED:
			result_string = "MCAST_RE_KEYING_NEEDED";
			break;
	}	
    UART_Put_Line(result_string);
}


void RxJoinResponse(bool status)
{
    switch (status)
    {
        case ACCEPTED:
            UART_Put_Line("accepted");
			break;
        case REJECTED:
            UART_Put_Line("rejected");
			break;
    }
}