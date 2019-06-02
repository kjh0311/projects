/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18LF46K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "Listen_And_Response.h"
#include "RxFunctions.h"
#include "debug_mode.h"
#include "UART_Print_Functions.h"
#include "interrupt_enable.h"
#include "Join.h"
void Meter_LORA_Communicate();
/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    interrupt_enable();	
	
	LORAWAN_Init(RxData, RxJoinResponse);
	
	LORAWAN_SetTxPower(0);
	JoinABP();	
#ifdef DEBUG_MODE	
	#ifdef AUTO_SEND
		SendMessagePeriodically();
	#else
		//UART_Put_String("start\r\n");
		Listen_And_Response();
	#endif
#else
	LORAWAN_SetAdr(false);
	LORAWAN_SetCurrentDataRate(3);
	//LORAWAN_SetTxPower(1);
	Meter_LORA_Communicate();
		
	//LATC5 = 1;
	//LATC5 = 1;
	/*
    while (1)
    {
		LorawanError_t result;
		LORAWAN_Mainloop();		
		//meter_request_callback();
		sensor_type = Get_SwitchValue() + 2;
		uint8_t a = 0x0;
		result = LORAWAN_Send(UNCNF, sensor_type, &a, 1);
		if (result==OK)
		{
			delay_seconds(METER_REQUEST_INTERVAL);
			LATC5 = !LATC5;
		}		
	}
	*/
#endif	
}
/**
 End of File
*/