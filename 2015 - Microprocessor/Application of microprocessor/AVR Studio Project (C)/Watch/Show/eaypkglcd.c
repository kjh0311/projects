

#include "LCD_MAP.h"

// LCD 제어 함수
void GLcdCmd(unsigned char signal,unsigned char command){   // write a command 
  LCD_CONTROL = signal & 0xC0;
                			                             // D/-I = 0
  LCD_DATA = command;                                            // write command
  LCD_CONTROL = (signal & 0xC0)|0x20;	                         // E = 1
  LCD_CONTROL = signal & 0xC0;                                   // E = 0
  Delay_us(10);
  LCD_CONTROL = 0x00;				                            // clear all control signals
  Delay_us(50);                                                  // wait for GLCD busy
}

// LCD에 한문자를 출력해주는 함수 
void GLcdSetData(unsigned int signal,unsigned int character)     // write a data 
{ LCD_CONTROL = (signal & 0xC0)|0x10;		                     // D/-I = 1
  LCD_DATA = character;                                          // write data
  LCD_CONTROL = (signal & 0xC0)|0x30;		                     // E = 1
  LCD_CONTROL = (signal & 0xC0)|0x10;                            // E = 0
  Delay_us(10);
  LCD_CONTROL = 0x00;				                             // clear all control signals
  Delay_us(50);                                                   // wait GLCD busy
}

// 화면 지우기 함수 
void GLcdClr(void)				                                     // clear GLCD screen 
{ unsigned char i, j, x;

  LCD_CONTROL = 0x00;				                                     // clear all control signals
  GLcdCmd(0xC0,0x3F);			                                 // CS1,CS2 display ON
  GLcdCmd(0xC0,0xC0);			                                 // CS1,CS2 display position

  x = 0xB8;
  for(i = 0; i <= 7; i++){ 
    GLcdCmd(0xC0,x);                                        // X start addtess
  	GLcdCmd(0xC0,0x40);                                     // Y start address
    for(j = 0; j <= 63; j++) GLcdSetData(0xC0,0x00);			         // clear CS1 and CS2 screen
    x++;
  } 
}


// 기본 예제 용 함수 
void GLcdStringPrint( unsigned char line, 
											 unsigned char *c0 ,unsigned char *c1 ,unsigned char *c2 ,unsigned char *c3 ,
                       unsigned char *c4 ,unsigned char *c5 ,unsigned char *c6 ,unsigned char *c7 ,
                       unsigned char *c8 ,unsigned char *c9 ,unsigned char *c10 ,unsigned char *c11 ,
                       unsigned char *c12 ,unsigned char *c13 ,unsigned char *c14  ,unsigned char *c15 ){
 
	unsigned char i ; 
	
  for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x40 + i);
		GLcdSetData(0x40,c0[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x48 + i);
		GLcdSetData(0x40,c1[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x50 + i);
		GLcdSetData(0x40,c2[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x58 + i);
		GLcdSetData(0x40,c3[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x60 + i);
		GLcdSetData(0x40,c4[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x68 + i);
		GLcdSetData(0x40,c5[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x70 + i);
		GLcdSetData(0x40,c6[i]);
	}
	 
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x78 + i);
		GLcdSetData(0x40,c7[i]);
	}
	 
	
  for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x40 + i);
		GLcdSetData(0x80,c8[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x48 + i);
		GLcdSetData(0x80,c9[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x50 + i);
		GLcdSetData(0x80,c10[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x58 + i);
		GLcdSetData(0x80,c11[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x60 + i);
		GLcdSetData(0x80,c12[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x68 + i);
		GLcdSetData(0x80,c13[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x70 + i);
		GLcdSetData(0x80,c14[i]);
	}
	for(i=0; i<8  ; i++){
  	GLcdCmd(0xC0,0xB8 + line );
		GLcdCmd(0x40,0x78 + i);
		GLcdSetData(0x80,c15[i]);
	}
                          
}  

// LCD에 문자를 출력해주는 함수
void GraphLcdCharactorSet( unsigned char line, unsigned char Poz, const char *Charactor)
{
	unsigned char i=0;
	unsigned char gSet;
	unsigned char gPoz;

	switch(Poz) {
		case 0 : gSet = 0x40; gPoz = 0x40; break;  case 1 : gSet = 0x40; gPoz = 0x48; break;
		case 2 : gSet = 0x40; gPoz = 0x50; break;  case 3 : gSet = 0x40; gPoz = 0x58; break;
		case 4 : gSet = 0x40; gPoz = 0x60; break;  case 5 : gSet = 0x40; gPoz = 0x68; break;
		case 6 : gSet = 0x40; gPoz = 0x70; break;  case 7 : gSet = 0x40; gPoz = 0x78; break;
		case 8 : gSet = 0x80; gPoz = 0x40; break;  case 9 : gSet = 0x80; gPoz = 0x48; break;
		case 10 : gSet = 0x80; gPoz = 0x50; break; case 11 : gSet = 0x80; gPoz = 0x58; break;
		case 12 : gSet = 0x80; gPoz = 0x60; break; case 13 : gSet = 0x80; gPoz = 0x68; break;
		case 14 : gSet = 0x80; gPoz = 0x70; break; case 15 : gSet = 0x80; gPoz = 0x78; break;
	}

	for(i=0;i<8;i++) {
		GLcdCmd(0xC0,0xB8 + line );
		//GLcdCmd(0x40,gPoz + i); // 요녀석을 내가 아래와 같이 수정함
		GLcdCmd(0xC0,gPoz + i);
		GLcdSetData(gSet,Charactor[i]);
	}
}
