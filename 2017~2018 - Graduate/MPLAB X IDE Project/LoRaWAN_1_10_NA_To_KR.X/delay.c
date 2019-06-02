/*
 * File:   delay.c
 * Author: 김진희
 *
 * Created on May 20, 2018, 5:06 PM
 */


#include "mcc_generated_files/mcc.h"


void delay_seconds(uint8_t seconds)
{
    for (uint8_t i = 0; i < seconds; i++)
	{
		for (uint8_t j = 0; j < 100; j++)		
		{
			LORAWAN_Mainloop(); // receive down link message
			__delay_ms(10);
		}		
		LATC5 = !LATC5; // blink green led
    }
}
