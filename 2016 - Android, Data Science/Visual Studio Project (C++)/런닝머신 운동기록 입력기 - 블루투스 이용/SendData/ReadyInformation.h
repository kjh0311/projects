#pragma once
#include "ServerHeader.h"



typedef struct _ReadyInformation
{
	SOCKET          LocalSocket;
	LPCSADDR_INFO   lpCSAddrInfo;
	wchar_t *       pszInstanceName;
}ReadyInformation;