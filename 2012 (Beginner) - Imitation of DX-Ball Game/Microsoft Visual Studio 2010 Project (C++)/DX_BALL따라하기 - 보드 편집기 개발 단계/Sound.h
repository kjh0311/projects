extern BOOL bSound;
extern HINSTANCE g_hInst;
extern HWND hWndMain;

BOOL Sounding=FALSE;
BOOL SoundShort=FALSE;
BOOL SoundLong=FALSE;
#define SoundCount 100

void SoundNoStop(int IDR_WAVE);

DWORD WINAPI Sounded(LPVOID temp){
	//UpdateWindow(hWndMain);
	//SwitchToThread();
	if(SoundShort){
		Sleep(500);
		SoundShort=FALSE;
		Sounding=FALSE;
	}
	else if(SoundLong){
		Sleep(1000);
		Sounding=FALSE;
		SoundLong=FALSE;
	}
	else{		
		Sleep(100);
		Sounding=FALSE;
	}
	HANDLE hThread = GetCurrentProcess();
//	SetPriorityClass(hThread, REALTIME_PRIORITY_CLASS);
	SetPriorityClass(hThread, HIGH_PRIORITY_CLASS);
//	SetPriorityClass(hThread, NORMAL_PRIORITY_CLASS);
	CloseHandle(hThread);
	return 0;
}
void SoundStop(int IDR_WAVE){
	if (bSound){
		PlaySound(MAKEINTRESOURCE(IDR_WAVE),g_hInst,SND_RESOURCE|SND_ASYNC|SND_PURGE);		
	}
}
void Sound(int IDR_WAVE){
	if (bSound){
		if(Sounding == TRUE){
		//	Sounding=FALSE;
			return;	// 앞에서 들어간 경우만 못 들어가게 함.
		}
		HANDLE hThread;
		hThread = GetCurrentProcess();
		DWORD ThreadID;
		EnterCriticalSection(&DrawCrt);		
		PlaySound(MAKEINTRESOURCE(IDR_WAVE),g_hInst,SND_RESOURCE|SND_ASYNC);
		//SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
		LeaveCriticalSection(&DrawCrt);
		CloseHandle(hThread);
		hThread = CreateThread(NULL,0,Sounded,NULL,0,&ThreadID);
		SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
		Sounding=TRUE;
		CloseHandle(hThread);
	}
}

void SoundNoStop(int IDR_WAVE){
	if (bSound){	
		HANDLE hThread;
		hThread = GetCurrentProcess();
		EnterCriticalSection(&DrawCrt);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE),g_hInst,SND_RESOURCE|SND_ASYNC);	
		PlaySound(MAKEINTRESOURCE(IDR_WAVE),g_hInst,SND_RESOURCE|SND_ASYNC|SND_NOSTOP);	
		//SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
		LeaveCriticalSection(&DrawCrt);
		CloseHandle(hThread);
		Sounding=TRUE;
		SoundLong=TRUE;
		DWORD ThreadID;
		hThread = CreateThread(NULL,0,Sounded,NULL,0,&ThreadID);
		SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
		CloseHandle(hThread);
		//LeaveCriticalSection(&Sound_CRT);
	}
}
void SoundNoStopShort(int IDR_WAVE){
	if (bSound){
		
		HANDLE hThread;
		hThread = GetCurrentProcess();
		EnterCriticalSection(&DrawCrt);
		CloseHandle(hThread);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE),g_hInst,SND_RESOURCE|SND_ASYNC);	
		PlaySound(MAKEINTRESOURCE(IDR_WAVE),g_hInst,SND_RESOURCE|SND_ASYNC|SND_NOSTOP);
		//SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
		LeaveCriticalSection(&DrawCrt);
		CloseHandle(hThread);
		Sounding=TRUE;
		SoundShort=TRUE;
		DWORD ThreadID;
		hThread = CreateThread(NULL,0,Sounded,NULL,0,&ThreadID);
		SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
		CloseHandle(hThread);
	}
}

void SleepHigh (double seconds)
{
	LARGE_INTEGER freq, st, ed;
	double gap;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&st);
	HANDLE hThread = GetCurrentProcess();
	//SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
	do{
		SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
		SwitchToThread();
		SetPriorityClass(hThread, HIGH_PRIORITY_CLASS);
		QueryPerformanceCounter(&ed);
		gap = ( (double)ed.QuadPart - (double)st.QuadPart )
			/ ( (double)freq.QuadPart );
	} while(gap< seconds);
	//
}
