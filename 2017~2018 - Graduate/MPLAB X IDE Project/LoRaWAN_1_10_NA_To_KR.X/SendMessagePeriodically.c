/*
 * File:   Timer0_ISR.c
 * Author: 김진희
 *
 * Created on January 24, 2018, 3:58 PM
 */


#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/LoRaWAN/sw_timer.h"


#define PERIOD_IN_MS		60000UL

static uint8_t sendingTimerId;


#define PERIOD_IN_TWO_SECOND		30
#define LENGTH 8
static uint8_t data[LENGTH] = { 0x03, 0x98, 0x76, 0x54, 0x32, 0x00, 0x02, 0x00 };
static uint8_t counts = 0;


void SendingTimerCallback(void);
void delay_seconds(uint8_t seconds);
//uint8_t SwTimerCreate(void);


void SendMessagePeriodically()
{
	while (1)
    {
		LorawanError_t result;
		LORAWAN_Mainloop();		
		//meter_request_callback();
		//sensor_type = Get_SwitchValue() + 2;
		uint8_t a = 0x0;
		result = LORAWAN_Send(UNCNF, 1, &a, 1);
		if (result==OK)
		{
			delay_seconds(4);
			LATC5 = !LATC5;
		}		
	}
	
	/*
	sendingTimerId = SwTimerCreate();
	SwTimerSetCallback( sendingTimerId , SendingTimerCallback, 0 );
	SwTimerSetTimeout( sendingTimerId, MS_TO_TICKS(PERIOD_IN_MS) );
	SwTimerStart( sendingTimerId );
	LATD5 = 1;
	LATC5 = 0;
	*/
}

// SwTimerStop(sendingTimerId);


void SendingTimerCallback(void)
{
	//LORAWAN_Mainloop();
	LORAWAN_Send( UNCNF, 1, data, LENGTH );
	SwTimerSetTimeout( sendingTimerId, MS_TO_TICKS(PERIOD_IN_MS) );
	SwTimerStart( sendingTimerId );
	LATD5 = !LATD5;
	LATC5 = !LATC5;
}


void TwoSeconds(void)
{
	counts++;
	if (counts >= PERIOD_IN_TWO_SECOND ) {
		LORAWAN_Send(CNF, 1, data, LENGTH);
		counts -= PERIOD_IN_TWO_SECOND;
	}		
}
