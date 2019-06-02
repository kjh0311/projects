#include "stdafx.h"
#include "Show_Detail_Input.h"




void Show_Detail_Input(HWND hWnd)
{
	ShowText(hWnd, KCAL_TEXT, STR_KCAL);
	h_edit_kcal = ShowEdit(hWnd, KCAL_EDIT, IDC_EDIT_KCAL);
	ShowText(hWnd, KCAL_UNIT_TEXT, STR_KCAL_UNIT);

	ShowText(hWnd, KM_TEXT, STR_KM);
	h_edit_km = ShowEdit(hWnd, KM_EDIT, IDC_EDIT_KM);
	ShowText(hWnd, KM_UNIT_TEXT, STR_KM_UNIT);

	ShowText(hWnd, GRAD_TEXT, STR_GRAD);
	h_edit_grad = ShowEdit(hWnd, GRAD_EDIT, IDC_EDIT_GRAD);
	ShowText(hWnd, GRAD_UNIT_TEXT, STR_GRAD_UNIT);

	ShowText(hWnd, SPEED_TEXT, STR_SPEED);
	h_edit_speed = ShowEdit(hWnd, SPEED_EDIT, IDC_EDIT_SPEED);
	ShowText(hWnd, SPEED_UNIT_TEXT, STR_SPEED_UNIT);
}