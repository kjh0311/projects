#include "stdafx.h"



SOCKET g_client_socket;
extern const int EX_TOTAL_LEN;


extern HWND hWndMain;
// 소켓을 이용하여 데이터를 전송한다.


#ifdef UNICODE
void SendToBluetooth(LPTSTR lptstr_data)
{	
	char* data;


	data = (char*)malloc(EX_TOTAL_LEN*sizeof(char));

	WideCharToMultiByte(CP_ACP, 0, lptstr_data, -1, data, EX_TOTAL_LEN, NULL, NULL);


	send(g_client_socket, data, strlen(data), 0);

	if (data)
	free(data);
}

#else
void SendToBluetooth(LPTSTR lptstr_data)
{	
	send(g_client_socket, lptstr_data, strlen(lptstr_data), 0);
}

#endif

DWORD WINAPI ServerRunThread(LPVOID temp);

// 여기서 g_client_socket 값을 얻어온다.

void StartServer(HWND hwnd)
{
	HANDLE h_thread;
	h_thread = CreateThread(NULL, 0, ServerRunThread, hwnd, 0, NULL);
	CloseHandle(h_thread);
}




#include "ReadyInformation.h"
#define CXN_SUCCESS                       0


// accept 하기 전에 필요한 모든 동작을 한다.
ULONG ready_to_accept(ReadyInformation *p_ready_information);
// accept 하고, recv, send 와 메모리 할당 및 해제를 하고, 
// ready_to_accept 에서 할당한 자원을 모두 반납한다.
ULONG accept_and_communicate(ReadyInformation ready_information);

DWORD WINAPI ServerRunThread(LPVOID hwnd)
{
	ULONG ulRetCode;
	ReadyInformation ready_information;
	SOCKET LocalSocket;
	int iLengthReceived;
	char buffer[1];


	ulRetCode = ready_to_accept(&ready_information);
	LocalSocket = ready_information.LocalSocket;


	while (ulRetCode == CXN_SUCCESS)
	{
		MessageBox((HWND)hwnd, _T("accept되기 전"), _T("accept되기 전"), MB_OK);
		g_client_socket = accept(LocalSocket, NULL, NULL);
		MessageBox((HWND)hwnd, _T("accept통과"), _T("accept통과"), MB_OK);

		do 
		{
			iLengthReceived = recv(g_client_socket, buffer, 1, 0);

			// send(g_client_socket, (char *)buffer, EX_TOTAL_LEN, 0);

		} while (iLengthReceived > 0);

		MessageBox((HWND)hwnd, _T("다음 연결을 받겠습니다."), _T("연결이 종료되었습니다."), MB_OK);

	}
	return(DWORD)ulRetCode;
}