CRITICAL_SECTION DrawCrt;
void InitCS(){
	InitializeCriticalSection(&DrawCrt);
	InitializeCriticalSection(&crit);
	InitializeCriticalSection(&Brick_CRT);
	InitializeCriticalSection(&Sound_CRT);
	InitializeCriticalSection(&Missile_CRT);
	InitializeCriticalSection(&Ball_CRT);
}
void DestroyCS(){
	DeleteCriticalSection(&DrawCrt);
	DeleteCriticalSection(&crit);
	DeleteCriticalSection(&Brick_CRT);
	DeleteCriticalSection(&Sound_CRT);
	DeleteCriticalSection(&Ball_CRT);
}