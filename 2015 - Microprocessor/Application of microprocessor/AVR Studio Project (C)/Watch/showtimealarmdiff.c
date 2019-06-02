/*
 * UpdateTimeDiff.c
 *
 * Created: 2015-05-30 ?¤í›„ 1:54:04
 *  Author: kimjin
 */ 

// Time°ü·Ã º¯¼ö´Â ´Ù ¿©±â¿¡ ÀÖÀ½
#include "Time.h"
#include "Show\RowAndColDefine.h"


void ShowTimeAlarmDiff();
void ShowReminderText();
void ShowAlarmTimeReminder()
{
	ShowTimeAlarmDiff();
	ShowReminderText();
}


#include "..\AlarmDiff.h"
/*
typedef struct _AlarmDiff
{
	int hour, minute, second;
}AlarmDiff;*/
AlarmDiff d1, d2;



void getAlarmDiff(AlarmDiff *pd, ShortInt Index);
AlarmDiff* getMinDiff(AlarmDiff *p1, AlarmDiff *p2);

void two_int_to_font(ShortInt two_ShortInt, char **p_h_font, char **p_l_font);
void GraphLcdCharactorSet( unsigned char line, unsigned char Poz, const char *Charactor);


void ShowTimeAlarmDiff()
{
	char *h_font, *l_font;	
	
	// ?¼ë‹¨ ??êµ¬í•´ë³´ê¸° ??[?Œê³ ë¦¬ì¦˜!]
	
	AlarmDiff *pd_min, *pd1 = &d1, *pd2 = &d2;
	getAlarmDiff(pd1, 0);
	getAlarmDiff(pd2, 1);
	pd_min = getMinDiff(pd1, pd2);
	if ( pd_min == pd1 )
		alarmIndex = 0;
	else
		alarmIndex = 1;

	//alarmIndex = 1;

	
	two_int_to_font(pd_min->hour, &h_font, &l_font);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR,h_font);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+1,l_font);
	
	two_int_to_font(pd_min->minute, &h_font, &l_font);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+4,h_font);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+5,l_font);
}



#include "..\ShortInt.h"
void getAlarmDiff(AlarmDiff *pd, ShortInt Index)
{	
	pd->hour = 0;
	pd->minute = 0;

	pd->second = AlarmTimes[Index].second - CurrentTime.second;
	if (pd->second < 0 ){
		pd->second+=60;
		pd->minute-=1;
	}

	pd->minute += AlarmTimes[Index].minute - CurrentTime.minute;
	if (pd->minute < 0 ){
		pd->minute+=60;
		pd->hour-=1;
	}

	pd->hour += AlarmTimes[Index].hour - CurrentTime.hour
			+ (AlarmTimes[Index].ampm - CurrentTime.ampm)*12;
	if (pd->hour < 0)
		pd->hour+= 24;
}



AlarmDiff* getMinDiff(AlarmDiff *p1, AlarmDiff *p2)
{
	if ( p1->hour < p2->hour )
		return p1;

	else if ( p1->hour > p2->hour )
		return p2;

	else if ( p1->minute < p2->minute )
		return p1;

	else if ( p1->minute > p2->minute )
		return p2;

	else if ( p1->second < p2->second )
		return p1;

	else 
		return p2;

}


extern const char font_Si[8];
extern const char font_Gan[8];

extern const char font_Boon[8];
extern const char font_Nam[8];
extern const char font_Um[8];
void ShowReminderText(){
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+2,font_Si);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+3,font_Gan);

	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+6,font_Boon);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+8,font_Nam);
	GraphLcdCharactorSet(REMINDER_ROW,COL_HOUR+9,font_Um);
}
