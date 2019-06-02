#include "stdafx.h"

#include "ServerHeader.h"
#include "ReadyInformation.h"







// accept 하기 전에 필요한 모든 동작을 한다.
ULONG ready_to_accept(ReadyInformation *p_ready_information)
{
	ULONG           ulRetCode = CXN_SUCCESS;
	int             iAddrLen = sizeof(SOCKADDR_BTH);
	size_t          cbInstanceNameSize = 0;	
	wchar_t *       pszInstanceName = NULL;
	wchar_t         szThisComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD           dwLenComputerName = MAX_COMPUTERNAME_LENGTH + 1;
	SOCKET          LocalSocket = INVALID_SOCKET;
	WSAQUERYSET     wsaQuerySet = { 0 };
	SOCKADDR_BTH    SockAddrBthLocal = { 0 };
	LPCSADDR_INFO   lpCSAddrInfo = NULL;
	HRESULT         res;

	//
	// This fixed-size allocation can be on the stack assuming the
	// total doesn't cause a stack overflow (depends on your compiler settings)
	// However, they are shown here as dynamic to allow for easier expansion
	//


	WSADATA     WSAData = { 0 };


	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (CXN_SUCCESS != ulRetCode)
	{
		wprintf(L"-FATAL- | Unable to initialize Winsock version 2.2\n");
	}


	if (CXN_SUCCESS == ulRetCode)
	{
		lpCSAddrInfo = (LPCSADDR_INFO)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CSADDR_INFO));
		if (NULL == lpCSAddrInfo)
		{
			wprintf(L"!ERROR! | Unable to allocate memory for CSADDR_INFO\n");
			ulRetCode = CXN_ERROR;
		}
	}

	if (CXN_SUCCESS == ulRetCode)
	{

		if (!GetComputerName(szThisComputerName, &dwLenComputerName))
		{
			wprintf(L"=CRITICAL= | GetComputerName() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	//
	// Open a bluetooth socket using RFCOMM protocol
	//
	if (CXN_SUCCESS == ulRetCode)
	{
		LocalSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
		if (INVALID_SOCKET == LocalSocket)
		{
			wprintf(L"=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if (CXN_SUCCESS == ulRetCode)
	{
		//
		// Setting address family to AF_BTH indicates winsock2 to use Bluetooth port
		//
		SockAddrBthLocal.addressFamily = AF_BTH;
		SockAddrBthLocal.port = BT_PORT_ANY;

		//
		// bind() associates a local address and port combination
		// with the socket just created. This is most useful when
		// the application is a server that has a well-known port
		// that clients know about in advance.
		//
		if (SOCKET_ERROR == bind(LocalSocket, (struct sockaddr *) &SockAddrBthLocal, sizeof(SOCKADDR_BTH)))
		{
			//printf("bind에서, 일단 오류 무시해보기\n");			
			wprintf(L"=CRITICAL= | bind() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)LocalSocket, WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if (CXN_SUCCESS == ulRetCode)
	{
		ulRetCode = getsockname(LocalSocket, (struct sockaddr *)&SockAddrBthLocal, &iAddrLen);
		if (SOCKET_ERROR == ulRetCode)
		{
			wprintf(L"=CRITICAL= | getsockname() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)LocalSocket, WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if (CXN_SUCCESS == ulRetCode)
	{
		//
		// CSADDR_INFO
		//
		lpCSAddrInfo[0].LocalAddr.iSockaddrLength = sizeof(SOCKADDR_BTH);
		lpCSAddrInfo[0].LocalAddr.lpSockaddr = (LPSOCKADDR)&SockAddrBthLocal;
		lpCSAddrInfo[0].RemoteAddr.iSockaddrLength = sizeof(SOCKADDR_BTH);
		lpCSAddrInfo[0].RemoteAddr.lpSockaddr = (LPSOCKADDR)&SockAddrBthLocal;
		lpCSAddrInfo[0].iSocketType = SOCK_STREAM;
		lpCSAddrInfo[0].iProtocol = BTHPROTO_RFCOMM;

		//
		// If we got an address, go ahead and advertise it.
		//
		ZeroMemory(&wsaQuerySet, sizeof(WSAQUERYSET));
		wsaQuerySet.dwSize = sizeof(WSAQUERYSET);
		wsaQuerySet.lpServiceClassId = (LPGUID)&g_guidServiceClass;

		//
		// Adding a byte to the size to account for the space in the
		// format string in the swprintf call. This will have to change if converted
		// to UNICODE
		//
		res = StringCchLength(szThisComputerName, sizeof(szThisComputerName), &cbInstanceNameSize);
		if (FAILED(res))
		{
			wprintf(L"-FATAL- | ComputerName specified is too large\n");
			ulRetCode = CXN_ERROR;
		}
	}

	if (CXN_SUCCESS == ulRetCode)
	{
		cbInstanceNameSize += sizeof(CXN_INSTANCE_STRING) + 1;
		pszInstanceName = (LPWSTR)HeapAlloc(GetProcessHeap(),
			HEAP_ZERO_MEMORY,
			cbInstanceNameSize);
		if (NULL == pszInstanceName)
		{
			wprintf(L"-FATAL- | HeapAlloc failed | out of memory | gle = [%d] \n", GetLastError());
			ulRetCode = CXN_ERROR;
		}
	}	


	if (CXN_SUCCESS == ulRetCode)
	{
		StringCbPrintf(pszInstanceName, cbInstanceNameSize, L"%s %s", szThisComputerName, CXN_INSTANCE_STRING);
		wsaQuerySet.lpszServiceInstanceName = pszInstanceName;
		wsaQuerySet.lpszComment = L"Example Service instance registered in the directory service through RnR";
		wsaQuerySet.dwNameSpace = NS_BTH;
		wsaQuerySet.dwNumberOfCsAddrs = 1;      // Must be 1.
		wsaQuerySet.lpcsaBuffer = lpCSAddrInfo; // Req'd.

		//
		// As long as we use a blocking accept(), we will have a race
		// between advertising the service and actually being ready to
		// accept connections.  If we use non-blocking accept, advertise
		// the service after accept has been called.
		//
		if (SOCKET_ERROR == WSASetService(&wsaQuerySet, RNRSERVICE_REGISTER, 0))
		{
			wprintf(L"=CRITICAL= | WSASetService() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	//
	// listen() call indicates winsock2 to listen on a given socket for any incoming connection.
	//
	if (CXN_SUCCESS == ulRetCode)
	{
		if (SOCKET_ERROR == listen(LocalSocket, CXN_DEFAULT_LISTEN_BACKLOG))
		{
			wprintf(L"=CRITICAL= | listen() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)LocalSocket, WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}


	
	wprintf(L"Computer name: %s", szThisComputerName);
	p_ready_information->LocalSocket = LocalSocket;
	p_ready_information->lpCSAddrInfo = lpCSAddrInfo;
	p_ready_information->pszInstanceName = pszInstanceName;
	return(ulRetCode);
}