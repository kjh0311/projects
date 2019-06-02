/*
 * Watch.c
 *
 * Created: 2015-05-30 Ïò§Ï†Ñ 11:37:27
 *  Author: kimjin
 */ 


#include "Time.h"
Time CurrentTime;
// 2Í∞úÏùò ÏïåÎûå ÏÇ¨Ïö©
Time AlarmTimes[2];
ShortInt alarmIndex = 0;

void SetDefaultCurrentTime()
{
	CurrentTime.ampm = AM;
	CurrentTime.hour = 10;
	CurrentTime.minute = 00;
	CurrentTime.second = 0;	
}



void SetDefaultAlarmTime()
{
	AlarmTimes[0].ampm = AM;
	AlarmTimes[0].hour = 10;
	AlarmTimes[0].minute = 00;
	//AlarmTime.minute = 20;
	AlarmTimes[0].second = 5;
	
	AlarmTimes[1].ampm = AM;
	AlarmTimes[1].hour = 10;
	AlarmTimes[1].minute = 00;
	//AlarmTime.minute = 20;
	AlarmTimes[1].second = 30;
}



void TimerStart(void){		
	TIMSK = 0x01; 	// Timer enable
	TCCR0 = 0x07 ;  // CLK / 1024
    TCNT0 = 178 ;
	/***********************************************************
    // Clock Source = System clock/1024
    // 10mSEC ∏∂¥Ÿ ø¿πˆ«√∑Œ ¿Œ≈Õ∑¥∆Æ 
  
    X * ∫–¡÷ * ( 1 / 8000000  ) = 10mSEC 
    X * 1024 * ( 1.25 * 10^-7 ) = 10mSEC
    X = 78.125
    256 - 78.125 = 178  = TCNT0
     
    ************************************************************/
}




