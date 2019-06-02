#include "stdafx.h"
#include "XYWH.h"



extern HINSTANCE hInst;
HWND ShowEdit(HWND hWnd, XYWH xywh, int ID_EDIT)
{
	return CreateWindow
		(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			xywh.X, xywh.Y, xywh.W, xywh.H, hWnd, (HMENU)ID_EDIT, hInst, NULL);
}
HWND ShowText(HWND hWnd, XYWH xywh, LPCTSTR str)
{
	return CreateWindow
		(TEXT("STATIC"), str, WS_CHILD | WS_VISIBLE,
			xywh.X, xywh.Y, xywh.W, xywh.H, hWnd, (HMENU)-1, hInst, NULL);
}
HWND ShowButton(HWND hWnd, XYWH xywh, LPCTSTR str, int ID_BUTTON)
{
	return CreateWindow
		(TEXT("BUTTON"), str, WS_CHILD | WS_VISIBLE|BS_PUSHBUTTON,
			xywh.X, xywh.Y, xywh.W, xywh.H, hWnd, (HMENU)ID_BUTTON, hInst, NULL);
}