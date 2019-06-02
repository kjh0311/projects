// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CREATE_TIMER_IN_LORAMOTE_H
#define	CREATE_TIMER_IN_LORAMOTE_H


uint8_t CreateTimer( void (*callback)(uint8_t) );
void StartTimer( uint8_t timer_id, uint32_t time_in_milliseconds );

#endif	/* CREATE_TIMER_IN_LORAMOTE_H */

