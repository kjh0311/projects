#include "stdafx.h"
#include "ShowDateInput.h"


void ShowDateInput(HWND hWnd)
{
	h_edit_year = ShowEdit(hWnd, YEAR_EDIT, IDC_EDIT_YEAR);
	ShowText(hWnd, YEAR_TEXT, STR_YEAR);

	h_edit_month = ShowEdit(hWnd, MONTH_EDIT, IDC_EDIT_MONTH);
	ShowText(hWnd, MONTH_TEXT, STR_MONTH);

	h_edit_day = ShowEdit(hWnd, DAY_EDIT, IDC_EDIT_DAY);
	ShowText(hWnd, DAY_TEXT, STR_DAY);
}