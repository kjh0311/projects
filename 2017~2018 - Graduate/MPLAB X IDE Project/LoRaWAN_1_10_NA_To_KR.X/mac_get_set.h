/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAC_GET_SET_H
#define	MAC_GET_SET_H

#include "mcc_generated_files/mcc.h"
//#include "DataLength.h"
#include "DataSaveLoad.h"



typedef struct {
    const char* name;
    DataLength len;
	DataAddress addr;
    void* getter;
    void* setter;
} NameLenGetterSetter;

typedef union {
    uint8_t all[16];
    uint32_t byte4;
    uint16_t byte2;
    uint8_t byte1;
	char* pointer;
} Buffer;

#define str_equals(a,b) (!strcmp(a,b))
#define NUM_HEX_PROP			8
#define NUM_DEC_PROP			9
#define NUM_ON_OFF_PROP			2
#define NUM_MULTI_PARAM_PROP	2

/* 바이트 수로 파라미터의 변수형이 결정됨
 * (uint8_t, uint16_t, uint32_t, uint8_t*)
 */

//void MyFunction (uint32_t deviceAddressNew);
NameLenGetterSetter HexProps[] = {
    { "devaddr", len_devaddr, addr_devaddr, LORAWAN_GetDeviceAddress, LORAWAN_SetDeviceAddress },
    //{ "devaddr", 4, LORAWAN_GetDeviceAddress, MyFunction },
    { "deveui", len_deveui, addr_deveui, LORAWAN_GetDeviceEui, LORAWAN_SetDeviceEui },
    { "appeui", len_appeui, addr_appeui, LORAWAN_GetApplicationEui, LORAWAN_SetApplicationEui },
    { "nwkskey", len_nwkskey, addr_nwkskey, LORAWAN_GetNetworkSessionKey, LORAWAN_SetNetworkSessionKey },
    { "appskey", len_appskey, addr_appskey, LORAWAN_GetApplicationSessionKey, LORAWAN_SetApplicationSessionKey },
    { "appkey", len_appkey, addr_appkey, LORAWAN_GetApplicationKey, LORAWAN_SetApplicationKey },
    { "sync", len_sync, addr_sync, LORAWAN_GetSyncWord, LORAWAN_SetSyncWord },
    { "status", len_status, NO_SAVE, LORAWAN_GetStatus },
};

NameLenGetterSetter DecProps[] = {
    { "class", len_class, NO_SAVE, LORAWAN_GetClass, LORAWAN_SetClass },
    { "pwridx", len_pwridx, addr_pwridx, LORAWAN_GetTxPower, LORAWAN_SetTxPower },
    { "dr", len_dr, addr_dr, LORAWAN_GetCurrentDataRate, LORAWAN_SetCurrentDataRate },
    { "bat", len_bat, NO_SAVE, NULL, LORAWAN_SetBattery },
    { "retx", len_retx, NO_SAVE, LORAWAN_GetNumberOfRetransmissions, LORAWAN_SetNumberOfRetransmissions },
    { "linkchk", len_linkchk, NO_SAVE, NULL, LORAWAN_LinkCheckConfigure },
    { "rxdelay1", len_rxdelay1, addr_rxdelay1, LORAWAN_GetReceiveDelay1, LORAWAN_SetReceiveDelay1 },
    { "rxdelay2", len_rxdelay2, addr_rxdelay2, LORAWAN_GetReceiveDelay2, NULL },
    { "acceptDelay1", len_acceptDelay1, addr_acceptDelay1, LORAWAN_GetJoinAcceptDelay1, LORAWAN_SetJoinAcceptDelay1 },
    { "acceptDelay2", len_acceptDelay2, addr_acceptDelay2, LORAWAN_GetJoinAcceptDelay2, LORAWAN_SetJoinAcceptDelay2 },
    { "upctr", len_upctr, NO_SAVE, LORAWAN_GetUplinkCounter, LORAWAN_SetUplinkCounter },
    { "dnctr", len_dnctr, NO_SAVE, LORAWAN_GetDownlinkCounter, LORAWAN_SetDownlinkCounter },
};


NameLenGetterSetter OnOffProps[] = {
    { "adr", len_adr, addr_adr, LORAWAN_GetAdr, LORAWAN_SetAdr },
    { "ar", len_ar, NO_SAVE, LORAWAN_GetAutomaticReply, LORAWAN_SetAutomaticReply },
};


LorawanError_t mac_set_rx2(char* param);
void mac_get_rx2(char* buffer);
LorawanError_t mac_set_ch(char* param);
void mac_get_ch(char* buffer, char* param);

#define STRING	0

NameLenGetterSetter MultiParamProps[] = {
    { "rx2", STRING, mac_get_rx2, mac_set_rx2 },
    { "ch", STRING, mac_get_ch, mac_set_ch },
};



typedef enum { HEX, DEC, ON_OFF, MULTI_PARAM } ValueType;

typedef struct {
    ValueType type;
    NameLenGetterSetter* name_len_getter_setter_array;
    uint8_t array_len;
} Props;

#define NUM_PROP_CLASS 4

Props props_array[] = {
    {HEX, HexProps, NUM_HEX_PROP}, 
    {DEC, DecProps, NUM_DEC_PROP}, 
    {ON_OFF, OnOffProps, NUM_ON_OFF_PROP}, 
	{MULTI_PARAM, MultiParamProps, NUM_MULTI_PARAM_PROP}, 
};



void UART_Put_String(const char *string);
void value_to_hex_str(char* converted, char* buffer, uint8_t len);
void value_to_dec_str(char* converted, Buffer* pBuffer, uint8_t len);


#endif	/* MAC_GET_SET_H */

