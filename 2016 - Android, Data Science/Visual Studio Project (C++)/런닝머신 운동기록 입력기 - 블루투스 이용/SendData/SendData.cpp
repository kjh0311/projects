#include "stdafx.h"
#include "SendData.h"



/*
블루투스를 이용해서 입력한 값을 보낸다.
입력한 값은 SQL 형식으로 보낸다.
SQL 형식
'yyyy-mm-dd', 'HH:MM', 'HH:MM', iiii, ff.ff, ff.f, ff.f
*/


extern HWND hWndMain;
HWND hWndMain;

void MakeSQLiteInsertParameter(LPTSTR start_of_data);
void SendToBluetooth(LPTSTR data);

extern const int EX_TOTAL_LEN;
const int EX_TOTAL_LEN = TOTAL_LEN;


void SendData(HWND hWnd)
{	
	TCHAR data[TOTAL_LEN];

	hWndMain = hWnd;
	
	MakeSQLiteInsertParameter(data);

	SendToBluetooth(data);

	MessageBox(hWnd, data, TEXT("보낼 정보"), MB_OK);
}


void MakeSQLiteInsertParameter(LPTSTR start_of_data)
{
	LPTSTR pointer_of_data;


	pointer_of_data = start_of_data;

	pointer_of_data = AppendDate(pointer_of_data);
	pointer_of_data = AppendComma(pointer_of_data);

	pointer_of_data = AppendStartTime(pointer_of_data);
	pointer_of_data = AppendComma(pointer_of_data);

	pointer_of_data = AppendEndTime(pointer_of_data);
	pointer_of_data = AppendComma(pointer_of_data);

	pointer_of_data = AppendKcal(pointer_of_data);
	pointer_of_data = AppendComma(pointer_of_data);

	pointer_of_data = AppendKm(pointer_of_data);
	pointer_of_data = AppendComma(pointer_of_data);

	pointer_of_data = AppendGrad(pointer_of_data);
	pointer_of_data = AppendComma(pointer_of_data);

	pointer_of_data = AppendSpeed(pointer_of_data);

	// 마지막 표시	
	*pointer_of_data = '\0';
	pointer_of_data++;
	*pointer_of_data = '\0';
}

// 'yyyy-mm-dd'
LPTSTR AppendDate(LPTSTR pointer_of_data)
{
	// 작은 따옴표(')를 추가함
	*pointer_of_data = '\'';
	pointer_of_data++;


	get_text_and_fix_length(h_edit_year, pointer_of_data, YEAR_LEN);
	pointer_of_data += YEAR_LEN;
	*pointer_of_data = '-';
	pointer_of_data++;


	get_text_and_fix_length(h_edit_month, pointer_of_data, MONTH_LEN);
	pointer_of_data += MONTH_LEN;
	*pointer_of_data = '-';
	pointer_of_data++;


	get_text_and_fix_length(h_edit_day, pointer_of_data, DAY_LEN);
	pointer_of_data += DAY_LEN;


	// 작은 따옴표(')를 추가함
	*pointer_of_data = '\'';
	pointer_of_data++;


	return pointer_of_data;
}


LPTSTR AppendStartTime(LPTSTR pointer_of_data)
{
	// 작은 따옴표(')를 추가함
	*pointer_of_data = '\'';
	pointer_of_data++;


	get_hour(h_start_ampm, h_start_edit_hour, pointer_of_data);
	pointer_of_data += HOUR_LEN;


	*pointer_of_data = ':';
	pointer_of_data++;


	get_text_and_fix_length(h_start_edit_minute, pointer_of_data, MINUTE_LEN);
	pointer_of_data += MINUTE_LEN;


	// 작은 따옴표(')를 추가함
	*pointer_of_data = '\'';
	pointer_of_data++;

	return pointer_of_data;
}


// 'HH:MM'
LPTSTR AppendEndTime(LPTSTR pointer_of_data)
{
	// 작은 따옴표(')를 추가함
	*pointer_of_data = '\'';
	pointer_of_data++;


	get_hour(h_end_ampm, h_end_edit_hour, pointer_of_data);
	pointer_of_data += HOUR_LEN;


	*pointer_of_data = ':';
	pointer_of_data++;


	get_text_and_fix_length(h_end_edit_minute, pointer_of_data, MINUTE_LEN);
	pointer_of_data += MINUTE_LEN;


	// 작은 따옴표(')를 추가함
	*pointer_of_data = '\'';
	pointer_of_data++;

	return pointer_of_data;
}

// iiii
LPTSTR AppendKcal(LPTSTR pointer_of_data)
{
	int len;

	len = get_number(h_edit_kcal, pointer_of_data, KCAL_LEN);
	pointer_of_data += len;

	return pointer_of_data;
}

// ff.ff
LPTSTR AppendKm(LPTSTR pointer_of_data)
{
	int len;

	len = get_number(h_edit_km, pointer_of_data, KM_LEN);
	pointer_of_data += len;

	return pointer_of_data;
}

// ff.f
LPTSTR AppendGrad(LPTSTR pointer_of_data)
{
	int len;

	len = get_number(h_edit_grad, pointer_of_data, GRAD_LEN);
	pointer_of_data += len;

	return pointer_of_data;
}

// ff.f
LPTSTR AppendSpeed(LPTSTR pointer_of_data)
{
	int len;

	len = get_number(h_edit_speed, pointer_of_data, SPEED_LEN);
	pointer_of_data += len;

	return pointer_of_data;
}


// 콤마(,) 추가
LPTSTR AppendComma(LPTSTR pointer_of_data)
{
	*pointer_of_data = ',';
	pointer_of_data++;
	return pointer_of_data;
}