#include "RowAndColDefine.h"


typedef unsigned char Char;
#define MAX_COL		16
#define FONT_SIZE	8

Char originLeftFont[FONT_SIZE];
Char originTopFonts[MAX_COL][FONT_SIZE];
Char originRightFont[FONT_SIZE];
Char originBottomFonts[MAX_COL][FONT_SIZE];

 #ifndef SHORT_INT
 #define SHORT_INT
typedef	unsigned char	shortInt;
typedef	unsigned char	ShortInt;
#endif

// ÏÇ¨Í∞ÅÌòïÏùÑ Í∑∏Î¶∞Îã§.
void drawLeftEdge(ShortInt row, ShortInt col);
void drawRightEdge(ShortInt row, ShortInt col);
void drawTopEdge(ShortInt row, ShortInt col, ShortInt offset);
void drawBottomEdge(ShortInt row, ShortInt col, ShortInt offset);
void ShowSettingRect(shortInt row, shortInt colLeft, shortInt colRight)
{
	ShortInt i;
	ShortInt leftRightDif = colRight - colLeft;
	
	drawLeftEdge(row, colLeft-1);
	drawRightEdge(row, colRight+1);	
	for (i = 0; i < leftRightDif; i++)
	{
		drawTopEdge(row-1, colLeft, i);	
		drawBottomEdge(row+1, colLeft, i);
	}
}


void EraseSettingRect(shortInt row, shortInt colLeft, shortInt colRight)
{
	ShortInt i;
	ShortInt leftRightDif = colRight - colLeft;
	
	eraseLeftEdge(row, colLeft-1);
	eraseRightEdge(row, colRight+1);	
	for (i = 0; i < leftRightDif; i++)
	{
		eraseTopEdge(row-1, colLeft, i);	
		eraseBottomEdge(row+1, colLeft, i);
	}
}


// æ∆∑° ≤® ºˆ¡§«ÿæﬂ«‘ æ∆¡˜ ºˆ¡§ æ» «ﬂ¿Ω

const char font_LeftEdge[8] = { 0x00,0x40,0x70,0x1D,0x17,0x1F,0x78,0x60 }; // A
const char font_RightEdge[8] = { 0x00,0x41,0x7F,0x7F,0x49,0x4F,0x7E,0x30 }; // B
const char font_TopEdge[8] = { 0x00,0x1C,0x3E,0x63,0x41,0x41,0x42,0x27 }; // C
const char font_BottomEdge[8] = { 0x00,0x41,0x7F,0x7F,0x41,0x63,0x3E,0x1C }; // D

void GraphLcdCharactorSet_OR_AND( unsigned char line
, unsigned char Poz, const char *Charactor, Char *originFont);
void drawLeftEdge(ShortInt row, ShortInt col)
{
	GraphLcdCharactorSet_OR_AND(row,col,font_LeftEdge, originLeftFont);
}


void drawRightEdge(ShortInt row, ShortInt col)
{
	GraphLcdCharactorSet_OR_AND(row,col,font_RightEdge, originRightFont);
}


void drawTopEdge(ShortInt row, ShortInt col, ShortInt offset)
{
	GraphLcdCharactorSet_OR_AND(row,col+offset,font_TopEdge
							, originTopFonts[offset]);
}


void drawBottomEdge(ShortInt row, ShortInt col, ShortInt offset)
{
	GraphLcdCharactorSet_OR_AND(row,col+offset,font_BottomEdge, 
							originBottomFonts[offset]);
}


#define		NULL	(char*)0
void eraseLeftEdge(ShortInt row, ShortInt col)
{
	GraphLcdCharactorSet_OR_AND(row,col,NULL, originLeftFont);
}


void eraseRightEdge(ShortInt row, ShortInt col)
{
	GraphLcdCharactorSet_OR_AND(row,col,NULL, originRightFont);
}


void eraseTopEdge(ShortInt row, ShortInt col, ShortInt offset)
{
	GraphLcdCharactorSet_OR_AND(row,col+offset,NULL
							, originTopFonts[offset]);
}


void eraseBottomEdge(ShortInt row, ShortInt col, ShortInt offset)
{
	GraphLcdCharactorSet_OR_AND(row,col+offset,NULL, 
							originBottomFonts[offset]);
}


void GLcdCmd(unsigned char signal,unsigned char command);
void GLcdDataOr(unsigned int signal,unsigned int character);
void GLcdDataAnd(unsigned int signal,unsigned int character);
void GraphLcdCharactorSet_OR_AND( unsigned char line
, unsigned char Poz, const char *Charactor, Char *originFont)
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
		//GLcdCmd(0x40,gPoz + i); // ÏöîÎÖÄÏÑùÏùÑ ÎÇ¥Í∞Ä ÏïÑÎûòÏôÄ Í∞ôÏù¥ ÏàòÏ†ïÌï®
		GLcdCmd(0xC0,gPoz + i);
		if (Charactor) { // Í∑∏Î¶¨Í∏∞ Î™®Îìú
			originFont[i] = Charactor[i];
			GLcdDataOr(gSet,Charactor[i]);
		} else { // ÏßÄÏö∞Í∏∞ Î™®Îìú
			GLcdDataAnd(gSet,originFont[i]);
		}
	}
}



#include "LCD_Map.h"
// LCDÏóê ÌïúÎ¨∏ÏûêÎ•º Ï∂úÎ†•Ìï¥Ï£ºÎäî Ìï®Ïàò 
void GLcdDataOr(unsigned int signal,unsigned int character)    	 // write a data 
{
	LCD_CONTROL = (signal & 0xC0)|0x10;		                   	  // D/-I = 1	
	LCD_DATA |= character;                                      	 // write data
	LCD_CONTROL = (signal & 0xC0)|0x30;		                    	 // E = 1
	LCD_CONTROL = (signal & 0xC0)|0x10;                            // E = 0
	Delay_us(10);
	LCD_CONTROL = 0x00;				                             	// clear all control signals
	Delay_us(50);                                                   // wait GLCD busy
}

void GLcdDataAnd(unsigned int signal,unsigned int character)    	 // write a data 
{
	LCD_CONTROL = (signal & 0xC0)|0x10;		                   	  // D/-I = 1	
	LCD_DATA &= character;                                      	 // write data
	LCD_CONTROL = (signal & 0xC0)|0x30;		                    	 // E = 1
	LCD_CONTROL = (signal & 0xC0)|0x10;                            // E = 0
	Delay_us(10);
	LCD_CONTROL = 0x00;				                             	// clear all control signals
	Delay_us(50);                                                   // wait GLCD busy
}    

