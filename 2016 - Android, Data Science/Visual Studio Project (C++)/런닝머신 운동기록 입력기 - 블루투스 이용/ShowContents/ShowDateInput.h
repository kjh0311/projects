#pragma once
#include "XYWH.h"
#include "ShowContents.h"
#include "IDs.h"


static LPCTSTR
STR_YEAR = TEXT("³â"),
STR_MONTH = TEXT("¿ù"),
STR_DAY = TEXT("ÀÏ");



static const XYWH
YEAR_EDIT = left_top(40, 20),
YEAR_TEXT = right_from(YEAR_EDIT, 0, 20, 20),
MONTH_EDIT = right_from(YEAR_TEXT, 10, 20, 20),
MONTH_TEXT = right_from(MONTH_EDIT, 0, 20, 20),
DAY_EDIT = right_from(MONTH_TEXT, 5, 20, 20),
DAY_TEXT = right_from(DAY_EDIT, 0, 20, 20);


