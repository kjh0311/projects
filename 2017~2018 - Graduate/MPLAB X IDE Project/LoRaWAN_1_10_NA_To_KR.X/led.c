/*
 * File:   led.c
 * Author: 김진희
 *
 * Created on 2018년 2월 13일 (화), 오후 2:31
 */


#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/LoRaWAN/sw_timer.h"
#include "Timer_In_LoRaMote.h"
#include "led.h"

#define GREEN_LED_ON					 1000
#define GREEN_LED_OFF					  500
#define	RED_LED_ON						 5000


#define CONTROL_GREEN_LED_ON			1
#define CONTROL_RED_LED_ON				2
#define CONTROL_GREEN_LED_OFF			3
#define CONTROL_RED_LED_OFF				4



static uint8_t green_led_on_timer_id;
static uint8_t green_led_off_timer_id;
static uint8_t red_led_on_timer_id;
//uint8_t led_enable = 1;


void led_timer_initialize()
{
	green_led_on_timer_id = CreateTimer(GreenLedBlinkCallback);
	green_led_off_timer_id = CreateTimer(GreenLedBlink);
	red_led_on_timer_id = CreateTimer(RedLedOnCallback);
}


void GreenLedTimerOff()
{
	LATC5 = 0;
	SwTimerStop( green_led_on_timer_id );
	SwTimerStop( green_led_off_timer_id );
}



void GreenLedBlink()
{
	LATC5 = 1;
	StartTimer( green_led_on_timer_id, GREEN_LED_ON );
}
void GreenLedBlinkCallback()
{
	LATC5 = 0;
	StartTimer( green_led_off_timer_id, GREEN_LED_OFF );
}
void RedLedOn()
{
	LATD5 = 1;
	StartTimer( red_led_on_timer_id, RED_LED_ON );
}
void RedLedOnCallback()
{
	LATD5 = 0;
}


#define CONTROL_GREEN_LED_ON			1
#define CONTROL_RED_LED_ON				2
#define CONTROL_GREEN_LED_OFF			3
#define CONTROL_RED_LED_OFF				4

char* LedControl(uint8_t* pData, uint8_t data_length)
{
	if (data_length!=0)
	{
		switch (pData[0])
		{
			case CONTROL_GREEN_LED_ON:
				LATC5 = 1;
				return "green led on";
			case CONTROL_RED_LED_ON:
				LATD5 = 1;
				return "red led on";
			case CONTROL_GREEN_LED_OFF:
				LATC5 = 0;
				return "green led off";
			case CONTROL_RED_LED_OFF:
				LATD5 = 0;
				return "red led off";
		}
	}
}