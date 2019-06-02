/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SKT_JOINING_STATE_H
#define	SKT_JOINING_STATE_H

typedef enum {
    NOT_YET_PSEUDO_ACCEPTED,
    PSEUDO_ACCEPTED,
    REQ_APP_NONCE_SENDED,
    ANS_APP_NONCE_RECEIVED,
    REPORT_RX_APP_NONCE_SENDED,
    ANS_RX_APP_NONCE_RECEIVED,
    REAL_ACCEPTED
} STATE;


extern STATE state;

#endif	/* SKT_JOINING_STATE_H */

