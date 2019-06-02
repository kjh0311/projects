/*
 * Time.h
 *
 * Created: 2015-05-30 오전 11:41:36
 *  Author: kimjin
 */ 

#include <avr/io.h>
#ifndef TIME_H_
#define TIME_H_
typedef int AMPM;
#define AM 0
#define PM 1
typedef struct
{
	int hour, minute, second;
	AMPM ampm;
}
Time;
extern Time CurrentTime;
extern Time AlarmTimes[2];
 #ifndef SHORT_INT
 #define SHORT_INT
 // 첫 글자의 대소문자 구분을 제거함
typedef	unsigned char	shortInt;
typedef	unsigned char	ShortInt;
#endif

extern ShortInt	alarmIndex;

extern volatile uint8_t tenMiliSec;
#endif /* TIME_H_ */
