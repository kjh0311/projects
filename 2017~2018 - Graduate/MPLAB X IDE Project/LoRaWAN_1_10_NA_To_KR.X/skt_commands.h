/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SKT_COMMANDS_H
#define	SKT_COMMANDS_H

#include "mcc_generated_files/mcc.h"


typedef enum {
    REQ_APP_NONCE = 0x00,
    ANS_APP_NONCE = 0x01,
    REPORT_APP_NONCE_RECEIVED = 0x02,
    ANS_REPORT_APP_NONCE_RECEIVED = 0x03,
    SET_RETRANSMITION = 0x04,
} SKT_MESSAGE_TYPE;


typedef union {
    uint8_t value;
    struct {
        uint8_t ver             : 2;
        uint8_t rfu             : 6;
    }bits;    
}VER_RFU;


typedef union {
    uint8_t value[250];
    struct {
        VER_RFU ver_rfu;
        uint8_t mtype, paylen, payload[247];   
    } fields;
} AppDataUnion;

#include "skt_joining_state.h"



LorawanError_t SendSktMessage(SKT_MESSAGE_TYPE skt_message_type);


#endif	/* SKT_COMMANDS_H */

