/*
 * UpdateWatch.c
 *
 * Created: 2015-05-30 오후 1:53:47
 *  Author: kimjin
 */ 


#include "Time.h"
//#include "Show\ShowWatchNumber.h"
#include "Show\RowAndColDefine.h"

void ToggleAMPM();

void ShowTime(const Time *pTime, const int row);
void UpdateWatch()
{
	static ShortInt prevAlarmIndex;
	if(tenMiliSec>99){	
		tenMiliSec-=100;
		UpdateWatchForSecond();
		ShowTimeAlarmDiff();
	}
	if (alarmIndex != prevAlarmIndex){		
		prevAlarmIndex = alarmIndex;
		ShowTime(&AlarmTimes[alarmIndex], ALARM_ROW);
	}
}

 #ifndef SHORT_INT
 #define SHORT_INT
typedef	unsigned char	shortInt;
typedef	unsigned char	ShortInt;
#endif
void ShowNumber(ShortInt number, ShortInt row, ShortInt col);
void UpdateWatchForSecond()
{
	CurrentTime.second++;
	ShowNumber(CurrentTime.second, WATCH_ROW, COL_SECOND);
	if(CurrentTime.second>59)
	{	
		CurrentTime.second-=60;
		CurrentTime.minute++;
		ShowNumber(CurrentTime.minute, WATCH_ROW, COL_MINUTE);
		if(CurrentTime.minute>59)
		{
			CurrentTime.minute-=60;
			CurrentTime.hour++;
			ShowNumber(CurrentTime.hour, WATCH_ROW, COL_HOUR);
			if (CurrentTime.hour>11)
			{
				CurrentTime.hour-=12;
				ToggleAMPM();
			}
		}
	}
}



void ToggleAMPM()
{
	if(CurrentTime.ampm==AM)
	CurrentTime.ampm=PM;
	else
	CurrentTime.ampm=AM;
	ShowAMPM();
}
