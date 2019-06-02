#include "stdafx.h"
#include "ShowTimeInput.h"


extern const int EX_AMPM_LEN;
const int EX_AMPM_LEN = 2;


LPCTSTR
EX_STR_AM = STR_AM,
EX_STR_PM = STR_PM;


void ShowStartTimeInput(HWND hWnd)
{
	ShowText(hWnd, START_TEXT, STR_START_TIME);
	
	
	h_start_ampm = ShowAMPMComboBox(hWnd, START_AMPM_COMBO, IDC_COMBO_AMPM);
	h_start_edit_hour = ShowEdit(hWnd, START_HOUR_EDIT, IDC_EDIT_HOUR);
	ShowText(hWnd, START_HOUR_TEXT, STR_HOUR);
	h_start_edit_minute = ShowEdit(hWnd, START_MINUTE_EDIT, IDC_EDIT_MINUTE);
	ShowText(hWnd, START_MINUTE_TEXT, STR_MINUTE);
}


void ShowEndTimeInput(HWND hWnd)
{
	ShowText(hWnd, END_TEXT, STR_END_TIME);

	h_end_ampm = ShowAMPMComboBox(hWnd, END_AMPM_COMBO, IDC_COMBO_AMPM);
	h_end_edit_hour = ShowEdit(hWnd, END_HOUR_EDIT, IDC_EDIT_HOUR);
	ShowText(hWnd, END_HOUR_TEXT, STR_HOUR);
	h_end_edit_minute = ShowEdit(hWnd, END_MINUTE_EDIT, IDC_EDIT_MINUTE);
	ShowText(hWnd, END_MINUTE_TEXT, STR_MINUTE);
}


HWND ShowAMPMComboBox(HWND hWnd, XYWH xywh, int IDC_COMBO_AMPM)
{
	// static을 붙히거나 전역변수로 해야함
	static HWND hCombo;
	int count;
	extern HINSTANCE hInst;
	hCombo = CreateWindow
		(TEXT("ComboBox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			xywh.X, xywh.Y, xywh.W, xywh.H, hWnd, 
			(HMENU)IDC_COMBO_AMPM, hInst, NULL);

	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)STR_AM);
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)STR_PM);

	SendMessage(hCombo, CB_SETCURSEL, (WPARAM)0, 0);

	return hCombo;
}