#pragma once
#include "ShowTimeInput.h"


static LPCTSTR
STR_KCAL = TEXT("칼로리 소모:"),
STR_KCAL_UNIT = TEXT("kcal"),
STR_KM = TEXT("이동거리:"),
STR_KM_UNIT = TEXT("km"),
STR_GRAD = TEXT("경사:"),
STR_GRAD_UNIT = TEXT("%"),
STR_SPEED = TEXT("속도:"),
STR_SPEED_UNIT = TEXT("km/h");


static const XYWH

KCAL_TEXT = down_from(END_TEXT, 90, 20),
KCAL_EDIT = right_from(KCAL_TEXT, 5, 40, 20),
KCAL_UNIT_TEXT = right_from(KCAL_EDIT, 0, 40, 20),

KM_TEXT = down_from(KCAL_TEXT, 70, 20),
KM_EDIT = right_from(KM_TEXT, 5, 40, 20),
KM_UNIT_TEXT = right_from(KM_EDIT, 0, 40, 20),

GRAD_TEXT = down_from(KM_TEXT, 40, 20),
GRAD_EDIT = right_from(GRAD_TEXT, 5, 40, 20),
GRAD_UNIT_TEXT = right_from(GRAD_EDIT, 0, 40, 20),

SPEED_TEXT = right_from(GRAD_UNIT_TEXT, 0, 40, 20),
SPEED_EDIT = right_from(SPEED_TEXT, 5, 40, 20),
SPEED_UNIT_TEXT = right_from(SPEED_EDIT, 0, 40, 20);