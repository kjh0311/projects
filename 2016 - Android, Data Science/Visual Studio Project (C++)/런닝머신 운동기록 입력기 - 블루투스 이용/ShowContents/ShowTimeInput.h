#pragma once
#include "ShowDateInput.h"


static LPCTSTR
STR_START_TIME = TEXT("시작시간:"),
STR_END_TIME = TEXT("종료시간:"),
STR_AM = TEXT("오전"),
STR_PM = TEXT("오후"),
STR_HOUR = TEXT("시"),
STR_MINUTE = TEXT("분");



static const XYWH
START_TEXT = down_from(YEAR_EDIT, 80, 20),
START_AMPM_COMBO = right_from(START_TEXT, 5, 60, 100),
START_HOUR_EDIT = right_from(START_AMPM_COMBO, 15, 20, 20),
START_HOUR_TEXT = right_from(START_HOUR_EDIT, 0, 20, 20),
START_MINUTE_EDIT = right_from(START_HOUR_TEXT, 5, 20, 20),
START_MINUTE_TEXT = right_from(START_MINUTE_EDIT, 0, 20, 20),


END_TEXT = down_from(START_TEXT, 80, 20),
END_AMPM_COMBO = right_from(END_TEXT, 5, 60, 100),
END_HOUR_EDIT = right_from(END_AMPM_COMBO, 15, 20, 20),
END_HOUR_TEXT = right_from(END_HOUR_EDIT, 0, 20, 20),
END_MINUTE_EDIT = right_from(END_HOUR_TEXT, 5, 20, 20),
END_MINUTE_TEXT = right_from(END_MINUTE_EDIT, 0, 20, 20)
;


HWND ShowAMPMComboBox(HWND hWnd, XYWH xywh, int IDC_COMBO_AMPM);
