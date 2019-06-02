#pragma once
#include "../stdafx.h"
// #include "XYWH.h"
#include "Handles.h"
HWND ShowEdit(HWND hWnd, XYWH xywh, int ID_EDIT);
HWND ShowText(HWND hWnd, XYWH xywh, LPCTSTR str);
HWND ShowButton(HWND hWnd, XYWH xywh, LPCTSTR str, int ID_BUTTON);
