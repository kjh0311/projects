#include "stdafx.h"
#include "SendData.h"


void get_text_and_fix_length(HWND hwnd, LPTSTR ptr, const int LEN)
{

	int len, diff;
	LPTSTR temp;


	temp = (LPTSTR)malloc(sizeof(LPTSTR)*LEN);
	if (temp)
	{
		len = GetWindowText(hwnd, temp, LEN + 1);
		diff = LEN - len;
		for (int i = 0; i < diff; i++)
		{
			*ptr = '0';
			ptr++;
		}

		// if 문 안 걸면 heap corruption 오류 발생함
		if (len > 0)
		{
			memcpy(ptr, temp, LEN * sizeof(TCHAR));
		}
		free(temp);
	}
}


// 컴공 대학원에서 이렇게 만들면 혼남.
// 이럴 때는 get_text_and_fix_length와 get_number를
// 담을 파일을 따로 만들어야함.
int get_number(HWND hwnd, LPTSTR ptr, int LEN)
{
	int len;
	LPTSTR temp;
	temp = (LPTSTR)malloc(sizeof(LPTSTR)*LEN);
	if (temp)
	{
		len = GetWindowText(hwnd, temp, LEN + 1);
		if (len > 0)
		{
			memcpy(ptr, temp, len * sizeof(TCHAR));
		}
		else
		{
			*ptr = '0';
			len = 1;
		}
		free(temp);
	}
	return len;
}


int ampm_to_int(HWND h_ampm);
int get_edit_hour_to_int(HWND h_edit_hour);
void int_to_string_and_fix_digits(LPTSTR ptr, const int LEN, int int_value);
void get_hour(HWND h_ampm, HWND h_edit_hour, LPTSTR pointer_of_data)
{
	int hour;
	LPTSTR str_hour;

	hour = ampm_to_int(h_ampm);
	hour += get_edit_hour_to_int(h_edit_hour);

	int_to_string_and_fix_digits(pointer_of_data, HOUR_LEN, hour);
}


void int_to_string_and_fix_digits(LPTSTR ptr, const int LEN, int int_value)
{
	int len, diff;
	LPTSTR temp;

	temp = (LPTSTR)malloc(sizeof(LPTSTR)*LEN);
	if (temp)
	{
		len = _stprintf_s(temp, LEN + 1, _T("%d"), int_value);
		diff = LEN - len;
		for (int i = 0; i < diff; i++)
		{
			*ptr = '0';
			ptr++;
		}
		memcpy(ptr, temp, LEN * sizeof(TCHAR));
		free(temp);
	}

}


// 'HH:MM'
void get_hour(HWND h_ampm, HWND h_edit_hour, LPTSTR pointer_of_data);
#define string_equal(str1, str2)	(!lstrcmp(str1, str2))
int get_edit_hour_to_int(HWND h_edit_hour)
{
	int hour = 0;
	LPTSTR str_hour;

	str_hour = (LPTSTR)malloc(sizeof(TCHAR)*(HOUR_LEN + 1));
	if (str_hour)
	{
		get_text_and_fix_length(h_edit_hour, str_hour, HOUR_LEN);
		*(str_hour + HOUR_LEN) = '\0';

		// TODO: 글자를 수로 만들어 더하고 더한 결과를 다시
		// 글자로 만들어서 pointer_of_data에 기록하라!
		// MessageBox(hWndMain, str_hour, _T("디버그 정보"), MB_OK);
		hour = _ttoi(str_hour);
		free(str_hour);
	}
	return hour;
}


int ampm_to_int(HWND h_ampm)
{
	int hour = 0;
	LPTSTR str_ampm;
	str_ampm = (LPTSTR)malloc(sizeof(TCHAR)*(EX_AMPM_LEN + 1));
	if (str_ampm)
	{
		get_text_and_fix_length(h_ampm, str_ampm, EX_AMPM_LEN);
		*(str_ampm + EX_AMPM_LEN) = '\0';

		// MessageBox(hWndMain, str_ampm, _T("디버그 정보"), MB_OK);
		if (string_equal(EX_STR_PM, str_ampm))
		{
			hour = 12;
		}
		free(str_ampm);
	}
	return hour;
}