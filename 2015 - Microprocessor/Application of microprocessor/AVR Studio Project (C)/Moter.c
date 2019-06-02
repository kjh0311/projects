

// STEP MOTOR
#define STEP_MOTOR_CS (*(volatile unsigned char *)0x4000 )
#define EX_CS0        (*(volatile unsigned char *)0x5C00 )
#include <avr/interrupt.h>
int count_flag=0;
extern volatile uint8_t StepMotorCnt;
// 모터 전진 함수
void StepMotorForward( void ) 
{	
	count_flag = 1 ;
	// half step 즉 1이 한 개
	// 1이 두개면 Full step
	switch(StepMotorCnt) {
		case 1 :
			STEP_MOTOR_CS = 0x01;
			EX_CS0        = 0x11;
			//STEP_MOTOR_CS = 0x05;
			break;
		case 2 :
			STEP_MOTOR_CS = 0x04;
			EX_CS0        = 0x44;
			//STEP_MOTOR_CS = 0x06;
			break;
		case 3 :
			STEP_MOTOR_CS = 0x02;
			EX_CS0        = 0x22;
			//STEP_MOTOR_CS = 0x0A;
			break;
		case 4 :
			STEP_MOTOR_CS = 0x08;
			EX_CS0        = 0x28;
			//STEP_MOTOR_CS = 0x09;
			break;
		default : 
			StepMotorCnt=0;
			break;
		
	}

}

// 모터 후진 함수
void StepMotorBackward( void ) 
{	
	count_flag = 1 ;
	switch(StepMotorCnt) {
		case 1 :
			STEP_MOTOR_CS = 0x04;
			EX_CS0        = 0x44;
			//STEP_MOTOR_CS = 0x06;
			break;
		case 2 :
			STEP_MOTOR_CS = 0x01;
			EX_CS0        = 0x11;
			//STEP_MOTOR_CS = 0x05;
			break;
		case 3 :
			STEP_MOTOR_CS = 0x08;
			EX_CS0        = 0x88;
			//STEP_MOTOR_CS = 0x09;
			break;
		case 4 :
			STEP_MOTOR_CS = 0x02;
			EX_CS0        = 0x22;
			//STEP_MOTOR_CS = 0x0A;
			break;
		default : 
			StepMotorCnt=0;
			break;
	}

}


void StepMotorStop ( void ) {
	count_flag = 0 ;
}
