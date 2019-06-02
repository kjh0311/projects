/*
 * File:   Periodical_Action_In_LoRaMote.c
 * Author: 김진희
 *
 * Created on 2018년 1월 30일 (화), 오후 4:52
 */


#include "mcc_generated_files/LoRaWAN/sw_timer.h"
#include "Timer_In_LoRaMote.h"


uint8_t CreateTimer(void (*callback)(uint8_t))
{
	uint8_t timer_id;
	
	timer_id = SwTimerCreate();
	SwTimerSetCallback( timer_id , callback, 0 );
	return timer_id;
}


void StartTimer( uint8_t timer_id, uint32_t time_in_milliseconds )
{
	SwTimerSetTimeout( timer_id, MS_TO_TICKS(time_in_milliseconds) );
	SwTimerStart( timer_id );
}
