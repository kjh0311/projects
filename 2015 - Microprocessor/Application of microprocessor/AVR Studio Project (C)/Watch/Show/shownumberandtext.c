/*
 * UpdateWatch.c
 *
 * Created: 2015-05-30 오후 1:31:44
 *  Author: kimjin
 */ 


#include "Font.h"
#include "..\Time.h"
#include "RowAndColDefine.h"

void GraphLcdCharactorSet( unsigned char line, unsigned char Poz, const char *Charactor);
void ShowTitle()
{
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL,font_hyphen);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+1,font_hyphen);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+2,font_hyphen);

	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+3,font_Hyun);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+4,font_Jae);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+5,font_Si);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+6,font_Gak);
	
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+7,font_hyphen);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+8,font_hyphen);
	GraphLcdCharactorSet(TITLE_ROW,TITLE_COL+9,font_hyphen);
}


void ShowSi(int row){
	GraphLcdCharactorSet(row,COL_HOUR+2,font_Si);
}

void ShowBoon(int row){
	GraphLcdCharactorSet(row,COL_MINUTE+2,font_Boon);
}

void ShowCho(int row){
	GraphLcdCharactorSet(row,COL_SECOND+2,font_Cho);
}


void ShowAMPM(int row)
{
	char *font_Jyun_or_Hoo;
	if (CurrentTime.ampm == AM)	
		font_Jyun_or_Hoo = font_Jyun;
	else
		font_Jyun_or_Hoo = font_Hoo;	
	GraphLcdCharactorSet(row,COL_AMPM,font_OO);
	GraphLcdCharactorSet(row,COL_AMPM+1,font_Jyun_or_Hoo);
}

 #ifndef SHORT_INT
 #define SHORT_INT
typedef	unsigned char	shortInt;
typedef	unsigned char	ShortInt;
#endif
#include <string.h>
void GraphLcdCharactorSet( ShortInt line, ShortInt Poz, const char *Charactor);

void ShowText( const ShortInt SetLine, const ShortInt col, unsigned char* String)
{
	ShortInt i, colOffset = 0;
	ShortInt length = strlen(String);
	for(i=0;i<length;i++) {
		switch(String[colOffset]) {
			case '0' : GraphLcdCharactorSet(SetLine,col+colOffset,font_0); break; 
			case '1' : GraphLcdCharactorSet(SetLine,col+colOffset,font_1); break; 
			case '2' : GraphLcdCharactorSet(SetLine,col+colOffset,font_2); break; 
			case '3' : GraphLcdCharactorSet(SetLine,col+colOffset,font_3); break; 
			case '4' : GraphLcdCharactorSet(SetLine,col+colOffset,font_4); break; 
			case '5' : GraphLcdCharactorSet(SetLine,col+colOffset,font_5); break; 
			case '6' : GraphLcdCharactorSet(SetLine,col+colOffset,font_6); break; 
			case '7' : GraphLcdCharactorSet(SetLine,col+colOffset,font_7); break; 
			case '8' : GraphLcdCharactorSet(SetLine,col+colOffset,font_8); break; 
			case '9' : GraphLcdCharactorSet(SetLine,col+colOffset,font_9); break; 
			case 'A' : GraphLcdCharactorSet(SetLine,col+colOffset,font_A); break; 
			case 'B' : GraphLcdCharactorSet(SetLine,col+colOffset,font_B); break; 
			case 'C' : GraphLcdCharactorSet(SetLine,col+colOffset,font_C); break; 
			case 'D' : GraphLcdCharactorSet(SetLine,col+colOffset,font_D); break; 
			case 'E' : GraphLcdCharactorSet(SetLine,col+colOffset,font_E); break; 
			case 'F' : GraphLcdCharactorSet(SetLine,col+colOffset,font_F); break;
			case 'G' : GraphLcdCharactorSet(SetLine,col+colOffset,font_G); break;
			case 'H' : GraphLcdCharactorSet(SetLine,col+colOffset,font_H); break; 
			case 'I' : GraphLcdCharactorSet(SetLine,col+colOffset,font_I); break; 
			case 'K' : GraphLcdCharactorSet(SetLine,col+colOffset,font_K); break; 
			// L은 내가 만듬
			case 'L' : GraphLcdCharactorSet(SetLine,col+colOffset,font_L); break;
			case 'O' : GraphLcdCharactorSet(SetLine,col+colOffset,font_O); break; 
			case 'P' : GraphLcdCharactorSet(SetLine,col+colOffset,font_P); break; 
			case 'R' : GraphLcdCharactorSet(SetLine,col+colOffset,font_R); break; 
			case 'S' : GraphLcdCharactorSet(SetLine,col+colOffset,font_S); break; 
			case 'T' : GraphLcdCharactorSet(SetLine,col+colOffset,font_T); break; 
			case 'Y' : GraphLcdCharactorSet(SetLine,col+colOffset,font_Y); break;
			case '-' : GraphLcdCharactorSet(SetLine,col+colOffset,font_hyphen); break; 
			case ' ' : GraphLcdCharactorSet(SetLine,col+colOffset,font_NULL); break; 
			case 'u' : GraphLcdCharactorSet(SetLine,col+colOffset,font_u); break;
			case 'i' : GraphLcdCharactorSet(SetLine,col+colOffset,font_i); break;
			case 'n' : GraphLcdCharactorSet(SetLine,col+colOffset,font_n); break;
			case 's' : GraphLcdCharactorSet(SetLine,col+colOffset,font_s); break;

			default :  GraphLcdCharactorSet(SetLine,col+colOffset,font_NULL);			 
		} // End of Switch
		colOffset++;
	} // End of While
}

void two_int_to_font(ShortInt two_ShortInt, char **p_h_font, char **p_l_font);
void ShowNumber(ShortInt number, ShortInt row, ShortInt col)
{
	char *h_font, *l_font;
	two_int_to_font(number, &h_font, &l_font);
	GraphLcdCharactorSet(row,col,h_font);
	GraphLcdCharactorSet(row,col+1,l_font);
}


char* one_int_to_font(ShortInt one_ShortInt);
void two_int_to_font(ShortInt two_ShortInt, char **p_h_font, char **p_l_font)
{
	ShortInt h_ShortInt = two_ShortInt/10;
	ShortInt l_ShortInt = two_ShortInt%10;
	*p_h_font = one_int_to_font(h_ShortInt);
	*p_l_font = one_int_to_font(l_ShortInt);
}


char* one_int_to_font(ShortInt one_ShortInt)
{
	switch(one_ShortInt) {
		case 0 : return font_0;
		case 1 : return font_1;
		case 2 : return font_2;
		case 3 : return font_3;
		case 4 : return font_4;
		case 5 : return font_5;
		case 6 : return font_6;
		case 7 : return font_7;
		case 8 : return font_8;
		case 9 : return font_9;
		default: return font_NULL;
	}
}
