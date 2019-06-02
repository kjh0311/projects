




#include "Watch\Time.h"
#include "Button.h"
void StepMotorBackward();
void StepMotorForward();
void StepMotorStop();
typedef int bool;
#define false	0
#define true	1
#define	DOOR_CLOSED		0
#define	DOOR_OPENING	1
#define	DOOR_OPENED		2
#define	DOOR_CLOSING	3
// 버튼을 누를 경우 발생
#define	DOOR_STOPPED	4

// 시간재서 5초 이상이 되면 상태를 바꿈
#define	OPENING_SECOND		5
#define	OPENED_SECOND		5
#define	CLOSING_SECOND		5
#define	MAX_OPENING_COUNT	100
#define	MAX_OPENED_COUNT	100


#include "DoorInfo.h"
bool doorTimeExpired(DoorInfo *pInfo);
State ToNextState(DoorInfo *pInfo, ShortInt keyPressed);
int DoorControlForState(DoorInfo *pInfo);



DoorInfo Door = {DOOR_CLOSED, 0, 0};
ShortInt DoorControl(bool keyPressed, ShortInt keyBuf)
{	
	if ( (keyPressed && keyBuf == DOOR_BUTTON) ||
		doorTimeExpired(&Door)	)
	{
		Door.mode = ToNextState(&Door, keyPressed);
	}
	return DoorControlForState(&Door);
}



#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>


bool checkAlarmTime();
bool checkDoorOpeningTime(SecondAndTenMili openingStartTime);
bool checkDoorOpenedTime(SecondAndTenMili openedStartTime);
bool checkDoorClosingTime(SecondAndTenMili closingStartTime);
bool doorTimeExpired(DoorInfo *pInfo)
{
	switch(pInfo->mode)
	{
	case DOOR_CLOSED:
		return checkAlarmTime();
	case DOOR_OPENING:
		return checkDoorOpeningTime(pInfo->openingStartTime);
	case DOOR_OPENED:
		return checkDoorOpenedTime(pInfo->openedStartTime);
	case DOOR_CLOSING:
		return checkDoorClosingTime(pInfo->closingStartTime);
	case DOOR_STOPPED:
		return false;
	default:
		return false;
	}
}


#define	DOOR_CLOSED		0
#define	DOOR_OPENING	1
#define	DOOR_OPENED		2
#define	DOOR_CLOSING	3
// 버튼을 누를 경우 발생
#define	DOOR_STOPPED	4


State openStart(DoorInfo *pInfo);
State openedStart(DoorInfo *pInfo, ShortInt keyPressed);
State closeStart(DoorInfo *pInfo, ShortInt keyPressed);
State closingToNext(ShortInt keyPressed);
State ToNextState(DoorInfo *pInfo, ShortInt keyPressed)
{
	switch(pInfo->mode){
	case DOOR_CLOSED:
		return openStart(pInfo);		
	case DOOR_OPENING:
		return openedStart(pInfo, keyPressed);		
	case DOOR_STOPPED: // 강제로 멈춘경우
	case DOOR_OPENED:
		return closeStart(pInfo, keyPressed);		
	case DOOR_CLOSING:
		return closingToNext(keyPressed);		
	default:
		return pInfo->mode;
	}
}


State openStart(DoorInfo *pInfo)
{
	pInfo->openingStartTime.sec = CurrentTime.second;
	pInfo->openingStartTime.tenMili = tenMiliSec;
	return DOOR_OPENING;
}


State openedStart(DoorInfo *pInfo, ShortInt keyPressed)
{
	pInfo->openedStartTime.sec = CurrentTime.second;
	pInfo->openedStartTime.tenMili = tenMiliSec;
	if (keyPressed == true) // 강제로 멈춤
		return DOOR_STOPPED;
	else
		return DOOR_OPENED;
}


State closeStart(DoorInfo *pInfo, ShortInt keyPressed)
{
	pInfo->closingStartTime.sec = CurrentTime.second;
	pInfo->closingStartTime.tenMili = tenMiliSec;
	return DOOR_CLOSING;
}


State closingToNext(ShortInt keyPressed)
{
	if (keyPressed == true) // 강제로 멈춤
		return DOOR_STOPPED;
	else
		return DOOR_CLOSED;
}


int doorOpenControl(DoorInfo *pInfo);
int doorOpenedControl(DoorInfo *pInfo);
int doorCloseControl(DoorInfo *pInfo);

int DoorControlForState(DoorInfo *pInfo)
{
	switch(pInfo->mode){
	case DOOR_OPENING:
		return doorOpenControl(pInfo);
	case DOOR_OPENED:
		return doorOpenedControl(pInfo);
	case DOOR_CLOSING:
		return doorCloseControl(pInfo);
	default:
		return 0;
	}
}


// alarmIndex는 Watch.c파일에 있음
bool checkAlarmTime(){
	if (CurrentTime.ampm == AlarmTimes[alarmIndex].ampm
	&&	CurrentTime.hour == AlarmTimes[alarmIndex].hour
	&&	CurrentTime.minute == AlarmTimes[alarmIndex].minute
	&&	CurrentTime.second == AlarmTimes[alarmIndex].second
	)
	{
		return true;
	}
	else
		return false;
}


/*
#define	OPENING_SECOND		5
#define	OPENED_SECOND		5
#define	CLOSING_SECOND		5
*/

#include "ShowNumber.h"
bool checkDoorOpeningTime(SecondAndTenMili openingStartTime)
{
	ShortInt secDiff = CurrentTime.second - openingStartTime.sec;
	ShowNumber(secDiff, DEBUG_ROW, COL_HOUR);
	if ( secDiff == OPENING_SECOND &&
		openingStartTime.tenMili >= tenMiliSec 
		// 정상적인 경우 아래에는 걸리지 않음
		|| secDiff > OPENING_SECOND
		){
		return true;
		}
	else
		return false;

}
bool checkDoorOpenedTime(SecondAndTenMili openedStartTime)
{	
	ShortInt secDiff = CurrentTime.second - openedStartTime.sec;
	ShowNumber(secDiff, DEBUG_ROW, COL_MINUTE);
	if ( (	secDiff == OPENED_SECOND &&
		openedStartTime.tenMili >= tenMiliSec )
		// 정상적인 경우 아래에는 걸리지 않음
		|| secDiff > OPENED_SECOND
		){
		return true;
	}
	else
		return false;

}
bool checkDoorClosingTime(SecondAndTenMili closingStartTime)
{
	ShortInt secDiff = CurrentTime.second - closingStartTime.sec;
	ShowNumber(secDiff, DEBUG_ROW, COL_SECOND);
	if ( 
	 ( secDiff == CLOSING_SECOND &&
		closingStartTime.tenMili >= tenMiliSec )
		// 정상적인 경우 아래에는 걸리지 않음
		|| secDiff > CLOSING_SECOND
		){
		return true;
		}
	else
		return false;
}


void StepMotorBackward();
void StepMotorForward();
void StepMotorStop();

int doorOpenControl(DoorInfo *pInfo)
{
	StepMotorForward();
	/*
	pInfo->openingCount++;
	if (pInfo->openingCount > MAX_OPENING_COUNT)
		pInfo->openingCount = MAX_OPENING_COUNT-1;
	*/
	return 0;
}

int doorOpenedControl(DoorInfo *pInfo)
{
	StepMotorStop();
	/*
	pInfo->openedCount++;
	if (pInfo->openedCount > MAX_OPENED_COUNT)
		pInfo->openedCount = MAX_OPENED_COUNT;
	*/
	return 0;
}

int doorStopControl(DoorInfo *pInfo)
{
	StepMotorStop();	
	return 0;
}

int doorCloseControl(DoorInfo *pInfo)
{
	StepMotorBackward();
	/*
	pInfo->openingCount--;
	if (pInfo->openingCount < 0)
		pInfo->openingCount = 0;
	*/
	return 0;
}

