/*
 * File:   skt_commands.c
 * Author: 김진희
 *
 * Created on 2017년 11월 10일 (금), 오전 12:36
 */
#include "skt_commands.h"
#include "mcc_generated_files/LoRaWAN/lorawan_na.h"
#include "mcc_generated_files/LoRaWAN/lorawan_aes.h"
#include <stdio.h>
void UART_Put_String(const char* buffer);

static void PrepareRealAppKey (uint8_t* realAppKey, uint8_t* appNonce, uint8_t* networkId);
void delay(float second, LorawanError_t result);


STATE state = NOT_YET_PSEUDO_ACCEPTED;


static uint8_t realAppNonce[3];
uint8_t g_copied_net_id[3];
static uint8_t realAppKey[16];
static uint8_t aesBuffer[AES_BLOCKSIZE];
JoinAccept_t *g_joinAccept;
bool g_skt_joining_mode = false;



//void InterpretSktJoinMessage(uint8_t *message){}


LorawanError_t RequestAppNonce() {
	return SendSktMessage(REQ_APP_NONCE);
}

LorawanError_t ReportAppNonceReceived() {
	return SendSktMessage(REPORT_APP_NONCE_RECEIVED);
}


static void PrepareRealAppKey (uint8_t* realAppKey, uint8_t* appNonce, uint8_t* networkId)
{
    uint8_t index = 0;

    memset (&realAppKey[index], 0, sizeof(aesBuffer));  //appends 0-es to the buffer so that pad16 is done
    //index ++; // 1 byte for 0x01 or 0x02 depending on the key type

    memcpy(&realAppKey[index], appNonce, JA_APP_NONCE_SIZE);
    index = index + JA_APP_NONCE_SIZE;

    memcpy(&realAppKey[index], networkId, JA_NET_ID_SIZE);
    index = index + JA_NET_ID_SIZE;

    //memcpy(&sessionKey[index], &loRa.devNonce, sizeof(loRa.devNonce) );
}


LorawanError_t ComputeRealAppKey ()// (JoinAccept_t *joinAcceptBuffer)
{	
    PrepareRealAppKey(realAppKey, realAppNonce, g_copied_net_id);
    AESEncodeLoRa(realAppKey, loRa.activationParameters.applicationKey);
	
	LORAWAN_SetApplicationKey(realAppKey);
	//return LORAWAN_GetApplicationKey();
	return OK;
}

//static void JoinWithRealAppKey


void UART_Put_String(const char *string);
void InterpretSktJoinMessage(uint8_t *message) {
    if (message==NULL) return;
    
	char test[50];
    AppDataUnion app_data;
    memcpy(app_data.value, message, sizeof(AppDataUnion));
    
    switch (app_data.fields.mtype) {
        case ANS_APP_NONCE:
            //ComputeRealAppKey(app_data.fields.payload);
            memcpy(realAppNonce, app_data.fields.payload, 3);
            state = ANS_APP_NONCE_RECEIVED;
			UART_Put_String("ANS_APP_NONCE_RECEIVED\r\n");
            break;
        case ANS_REPORT_APP_NONCE_RECEIVED:
            state = ANS_RX_APP_NONCE_RECEIVED;
			UART_Put_String("ANS_RX_APP_NONCE_RECEIVED\r\n");
            break;
		default:
			break;
    }
	
	
	sprintf(test,
		"app_data.fields.mtype: 0x%x\r\n"
		"ver: 0x%x\r\n rfu: 0x%x\r\n"
		"paylen: 0x%x\r\n", 
		app_data.fields.mtype,
		app_data.fields.ver_rfu.bits.ver,
		app_data.fields.ver_rfu.bits.rfu,
		app_data.fields.paylen
		);
	UART_Put_String(test);
	
}

LorawanError_t SendSktMessage(SKT_MESSAGE_TYPE skt_message_type)
{    
    AppDataUnion app_data;
	TransmissionType_t trType = CNF;
    
    app_data.fields.ver_rfu.bits.ver = 0;
    app_data.fields.ver_rfu.bits.rfu = 0; // 1
    app_data.fields.mtype = skt_message_type; // 1
    app_data.fields.paylen = 0; // 1
        
    return LORAWAN_Send(trType, 0xDF, app_data.value, 3);    
}


void delay(float second, LorawanError_t result) {
    //static uint16_t count      =   1;
    if (result == OK) {
		//count++;
		// x may be 1 to 197             
		for( int i = 1; i <= (int)(second * 10); i++ ) 
		{
		   __delay_ms(100); //600 * 100 = 60000 ms = 60 s = 1 minute
		}             
	}
}


LorawanError_t enter_skt_join_mode() {
	g_skt_joining_mode = true;
}


void act_by_state_in_real_joining_mode() {
    LorawanError_t result;
    //trType = CNF;
    //trType = PROPRIETARY;
    if ( g_skt_joining_mode ) {
		switch(state) {
			case PSEUDO_ACCEPTED:
				result = RequestAppNonce();
				UART_Put_String("PSEUDO_ACCEPTED\r\n");
				break;
			case ANS_APP_NONCE_RECEIVED:
				result = ReportAppNonceReceived();
				UART_Put_String("ANS_APP_NONCE_RECEIVED\r\n");
				break;
			case ANS_RX_APP_NONCE_RECEIVED:
				ComputeRealAppKey();
				result = LORAWAN_Join(OTAA);
				UART_Put_String("ANS_APP_NONCE_RECEIVED\r\n");
				break;
			case REAL_ACCEPTED:
				g_skt_joining_mode = false;
				UART_Put_String("REAL_ACCEPTED\r\n");
				break;
			default: // 조건에 해당하지 않으면 이 함수는 아무 동작도 안 함.
				return;
		}
		delay(5, result);
	}
}