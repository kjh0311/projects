/* Program Name : 외부 Graphic LCD 제어 프로그램
   File Name    : EXT_GRAPHIC_LCD.c
   AUTHOR       : Huins
   DATE         : 2008 . 03
   Copyright    : Huins, Inc          */



void StartWatch(); 
void UpdateWatch();
#include "Moter.h"

#define F_CPU 8000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
//#include "Watch\EasyPK_AVR.h"
//#include "Watch\EayPKGLCD.h"
#include <stdlib.h>

void UpdateWatch();
void UpdateTimeAlarmDiff();

#include "Button.h"

 #ifndef SHORT_INT
 #define SHORT_INT
typedef	unsigned char	shortInt;
typedef	unsigned char	ShortInt;
#endif
ShortInt mainInLoop();
#define EX_CS0_CW        (*(volatile unsigned char *)0x5C03 )
int main(void)
{
  	Platform_Init(); // AVR 초기화
	StartWatch();
	sei();     // 인터럽트 인에이블
	EX_CS0_CW = 0x80;
	while(1){
		mainInLoop();		
	}			
	return 0;
		
}// end of main


void ShowValueInHourPos(int value);
void ShowValueInMinutePos(int value);
void ShowValueInMinuteBellow(int value);
unsigned char KeyPadRead();


#include <util/delay.h>
#include "DoorInfo.h"
extern DoorInfo Door;


#include "Watch\Time.h"
#include "Watch\Show\RowAndColDefine.h"
typedef unsigned char bool;
#define false	0
#define true	1


// 디버그 용으로 유용함
void ShowNumber(ShortInt number, ShortInt row, ShortInt col);
bool checkKeyPressed(ShortInt keyBuf);
ShortInt KeyFunction(ShortInt keyBuf);
ShortInt DoorControl(bool keyPressed, ShortInt keyBuf);
ShortInt WatchSetControl(bool keyPressed, ShortInt keyBuf);


#include "AlarmDiff.h"
extern AlarmDiff d1, d2;
ShortInt mainInLoop()
{			

	ShortInt keyBuf;
	bool keyPressed;
	keyBuf = KeyPadRead(); // 키 패드의 값을 입력 받음
/*
	ShowNumber(d1.hour, DEBUG_ROW, COL_HOUR);
	ShowNumber(d1.minute, DEBUG_ROW, COL_MINUTE);
	ShowNumber(d1.second, DEBUG_ROW, COL_SECOND);
	ShowNumber(d2.hour, DEBUG_ROW2, COL_HOUR);
	ShowNumber(d2.minute, DEBUG_ROW2, COL_MINUTE);
	ShowNumber(d2.second, DEBUG_ROW2, COL_SECOND);
*/
	/*
	ShowNumber(Door.openingStartTime.sec, DEBUG_ROW, COL_HOUR);
	ShowNumber(Door.openedStartTime.sec, DEBUG_ROW, COL_MINUTE);
	ShowNumber(Door.closingStartTime.sec, DEBUG_ROW, COL_SECOND);
	ShowNumber(keyBuf, DEBUG_ROW2, COL_MINUTE);
	ShowNumber(Door.mode, DEBUG_ROW2, COL_SECOND);
	*/
	
	UpdateWatch();	// 여기서만 시간이 이동함
	
	keyPressed = checkKeyPressed(keyBuf);
	//keyPressed = false;

	DoorControl(keyPressed, keyBuf);

//	WatchSetControl(keyPressed, keyBuf);
}



bool checkKeyPressed(ShortInt keyBuf)
{
	bool keyPressed = false;	
	static ShortInt prevKeyBuf = 0;	
	if ( keyBuf == 0 ||
		keyBuf == prevKeyBuf)
		keyPressed = false;	
	else
	{		
		keyPressed = true;
	}
	prevKeyBuf = keyBuf;
	return keyPressed;
}



void watchISR();
volatile uint8_t StepMotorCnt = 0, ExtGraphLcdCnt = 0, tenMiliSec = 0;
// 10ms留??諛?????명꽣?쏀?
ISR(TIMER0_OVF_vect)				// OC0A interrupt function
{	
	StepMotorCnt++;
	watchISR();
}

void watchISR()
{
	TCNT0 = 178;
	// 이거 꼭 해야함
	ExtGraphLcdCnt++; 	
	// 이상하게 2초에 한번 시간이 올라서 이렇게함.
	// 다른 키트에서는 제대로 됨
	tenMiliSec++;
}
