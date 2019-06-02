
#include "Show\RowAndColDefine.h"
//#include "Show\ShowNumber.h"
#include "Time.h"


void TimerStart();
void ShowTitle();
void ShowTime(const Time *pTime, const int row);
void ShowAlarmTimeReminder();
void ShowAlarmTime7Seg();
void ShowAlarmTime();
/*
// 16글자를 맞추어야 함
unsigned char title[16] =
{' ',' ','-','-','-',	'C','L','O','C','K',	'-','-','-',' ',' ', '\0'};
*/
unsigned char* title = "---CLOCK---";

//void ShowText( const ShortInt SetLine, const ShortInt col, unsigned char* String);
void ShowTitle();
void TimerStart(void);
void StartWatch()
{

	GLcdClr(); // Graphic LCD 화면 지우기	
	//GraphLcdCharactorGen(TITLE_ROW, title);
	//ShowText(TITLE_ROW, TITLE_COL, title);
	ShowTitle();
	SetDefaultCurrentTime();
	SetDefaultAlarmTime();
	TimerStart();
	
	ShowTime(&CurrentTime, WATCH_ROW);
	ShowAlarmTimeReminder();
	ShowTime(&AlarmTimes[alarmIndex], ALARM_ROW);

}



void ShowAMPM(int row);
void ShowSi(int row);
void ShowBoon(int row);
void ShowCho(int row);
void ShowNumber(int number, int row, int col);
void ShowTime(const Time *pTime, const int row)
{
	ShowAMPM(row);
	ShowNumber(pTime->hour, row, COL_HOUR);
	ShowSi(row);
	ShowNumber(pTime->minute, row, COL_MINUTE);
	ShowBoon(row);
	ShowNumber(pTime->second, row, COL_SECOND);
	ShowCho(row);
}



void ShowAlarmTime7Seg()
{
	
	
	
}


