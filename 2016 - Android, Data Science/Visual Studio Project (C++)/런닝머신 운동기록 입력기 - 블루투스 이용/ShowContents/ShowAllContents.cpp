#include "stdafx.h"
#include "XYWH.h"
#include "ShowContents.h"
#include "IDs.h"
void ShowDateInput(HWND hWnd);
void ShowStartTimeInput(HWND hWnd);
void ShowEndTimeInput(HWND hWnd);
void Show_Detail_Input(HWND hWnd);
void ShowSendButton(HWND hWnd);


void ShowAllContents(HWND hWnd)
{
	ShowDateInput(hWnd);

	ShowStartTimeInput(hWnd);
	ShowEndTimeInput(hWnd);
	Show_Detail_Input(hWnd);

	ShowSendButton(hWnd);
}


void ShowSendButton(HWND hWnd)
{
	XYWH xywh = right_top(80, 25);
	ShowButton(hWnd, xywh, TEXT("º¸³»±â"), IDC_BUTTON_SEND);
}