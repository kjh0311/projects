/*
 * File:   UART_Demo.c
 * Author: ???
 *
 * Created on October 8, 2017, 7:10 PM
 */


#include "mcc_generated_files/mcc.h"
#include "Listen_And_Response.h"
#include "RxFunctions.h"
#include "UART_Print_Functions.h"

#define COMMAND_BUFFER_LEN 100
void Interpret_UART_Command(char* buffer);

/* 이 펌웨어 전체의 메인 루프입니다. */
void Listen_And_Response() {    
    uint8_t i;
    char buffer[COMMAND_BUFFER_LEN];    
    
    /* 데이터를 수신할 때, Join Response를 받을 때 호출할 함수 설정 및
     * UART로 명령을 받을 때 기본값을 설정하는 부분*/
    //LORAWAN_Init(RxData, RxJoinResponse);
    
    
    while(1) {
		// LORAWAN에서 수신 받는 부분
        LORAWAN_Mainloop();
        if(eusart1RxCount!=0) {
            char c;
            // UART 문자 한 바이트를 읽음.
            c = EUSART1_Read();
			//EUSART1_Write(c);
            
            /* \r\n으로 끝나는 형식의 커맨드와 호환가능하도록, \r을 무시하여
             * 끝문자의 위치에 영향을 안 주도록 설정 */
            if ( c == '\r' )
            {
                continue;             
            }            
            /* 줄바꿈(\n)문자를 만나야 명령어 한 줄이 완성된 것으로 간주하여,
             * 모든 동작을 중치한체 명령어 해석을 시작한다.*/
            else if ( c == '\n' )
            {
                buffer[i] = '\0';
				//UART_Put_String(buffer);
                Interpret_UART_Command(buffer);
				i = 0;
            }
            else
            {
                buffer[i] = c;
                i++;
            }
        }
    }
}


void UART_Demo_Initialize(void)
{
    UART_Put_String("Hello World!");
}


unsigned char temp;


void UART_Demo_Command_INT(void) 
{    
    if(eusart1RxCount!=0) 
    {

    temp=EUSART1_Read();  // read a byte for RX

    EUSART1_Write(temp);  // send a byte to TX  (from Rx)

    switch(temp)    // check command  
    {
     case 'H':
     case 'h':
        {
            //LED_SetHigh();
            //printf(" -> LED On!!      \r");             
            break;
        }
     case 'L':
     case 'l':
        {
            //LED_SetLow();
            //printf(" -> LED Off!!     \r");   
            break;
        }
     default:
        {
            //printf(" -> Fail Command!! \r");            
            break;
        }       
    }
    }
}


/**
 End of File
 */
