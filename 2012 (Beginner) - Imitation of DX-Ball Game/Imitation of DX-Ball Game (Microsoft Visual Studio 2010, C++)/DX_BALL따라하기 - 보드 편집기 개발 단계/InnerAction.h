HANDLE hMoveBarThread = NULL;
DWORD WINAPI MoveBarThread(LPVOID PwParam){
	//WPARAM wParam = *(WPARAM*)PwParam;
	static int MoveCount;
	MoveCount=0;
	while(MoveCount < 2){
		Sleep(15);		
		
		if(*(WPARAM*)PwParam==VK_LEFT){			
			if(pos-PaddleSpeed>20){			
					for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
					{
						if(Ball->Grabbed)
						Ball->x-=PaddleSpeed;
					}
					pos-=PaddleSpeed;
					SetRect(&Paddle,(pos-PaddleSpeed),290,(pos+LengthOfBar+PaddleSpeed),(310+HeightOfGrab));					
					//InvalidateRect(hWndMain,&Paddle,FALSE);
					//wsprintf(String,"pos:%d, speed:%d",pos,speed);
				}
			else if(pos>20){
				for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
				{
					if(Ball->Grabbed)
					Ball->x-=pos-20;
				}
				pos=20;
				SetRect(&Paddle,pos,310,(pos+LengthOfBar+PaddleSpeed),(310+HeightOfGrab));
				//InvalidateRect(hWndMain,&Paddle,FALSE);
				//wsprintf(String,"22222222");
			}
		}
		if(*(WPARAM*)PwParam==VK_RIGHT){
			if(pos+LengthOfBar+PaddleSpeed<560){
				for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next){
					if(Ball->Grabbed)
						Ball->x+=PaddleSpeed;
				}
					pos+=PaddleSpeed;
					SetRect(&Paddle,(pos-PaddleSpeed),300,(pos+LengthOfBar),(310+HeightOfGrab));
					//InvalidateRect(hWndMain,&Paddle,FALSE);
				}
			else if(pos<560-LengthOfBar){
						for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
							if(Ball->Grabbed)
							Ball->x+=560-LengthOfBar-pos;
					pos=560-LengthOfBar;
					SetRect(&Paddle,(pos-PaddleSpeed),300,(pos+LengthOfBar),(310+HeightOfGrab));
					//InvalidateRect(hWndMain,&Paddle,FALSE);
				}
		}
		////InvalidateRect(hWndMain,&Paddle,FALSE);
		//UpdateWindow(hWndMain);		
		//Draw();
		//Draw(&Paddle);
		MoveCount ++;
	}	
	return 0;
}
void MoveBar(WPARAM wParam){
	DWORD ThreadID;
	HANDLE hThread;
	static WPARAM temp;
	temp = wParam;
	if ( hMoveBarThread != NULL )
		TerminateThread(hMoveBarThread, 0);
	hMoveBarThread = CreateThread(NULL,0,MoveBarThread,&temp, 0,&ThreadID);
	SetThreadPriority(hMoveBarThread,THREAD_PRIORITY_HIGHEST);	
}

DWORD WINAPI DropItemThread(LPVOID temp){
	//1. 구조체를 생성한다.
	//2. 구조체의 x와 y의 값을 바꾼다.
	//3. 구조체의 x, y 값을 근거로 무효영역을 만든다.
	//4. Draw(RECT rc)함수에서 구조체에 접근한다.	
	//srand((unsigned)time(NULL)+rand());
	//srand(rand());
	//HBITMAP *RandBit = RandItem();
	HBITMAP *RandBit = ((ItemInfo*)temp)->randBit;
	//EnterCriticalSection(&crit);
	DropingItem *Item = CreateItem(((ItemInfo*)temp)->x,((ItemInfo*)temp)->y,RandBit);	// 지역변수만 필요
	//LeaveCriticalSection(&crit);	
	//SetRect(&RcItem, Item->x*fw,Item->y*fh,(Item->x+32)*fw, (Item->y+30)*fh);
	////InvalidateRect(hWndMain,&RcItem,FALSE);
	//PlaySound(MAKEINTRESOURCE(IDR_ITEM),g_hInst,SND_RESOURCE|SND_SYNC|SND_NOSTOP);
	SoundNoStop(IDR_ITEM);	
	//Sleep(10);
	while(TRUE)
	{	
		while(gameOvered || paused){Sleep(100);}	//정지시 멈춤
		Sleep(20);
		EnterCriticalSection(&crit);
		//SwitchToThread();		
		Item->y+=3;
		//Item->y+=((ItemInfo*)temp)->dy*0.02/(0.032/Frame/speed) /2;
		//Item->x+=((ItemInfo*)temp)->dx*0.02/(0.032/Frame/speed) /2;
		// 공유 영역을 건들때는 반드시 Critical을 걸어야 함.
		SetRect(&RcItem, (Item->x-10),(Item->y-10),((Item->x+10)+32), ((Item->y+10)+30));		
		//Draw(&RcItem);
		LeaveCriticalSection(&crit);
		//UpdateWindow(hWndMain);		
		//아이템 먹기
		if(Item->y + 30 > 330)
		if(Item->x + 34 >pos && Item->x < pos + LengthOfBar){			
			////InvalidateRect(hWndMain,NULL,FALSE);
			//UpdateWindow(hWndMain);
			EnterCriticalSection(&crit);
			ItemAction(Item);
			SetRect(&RcItem, (Item->x-10),(Item->y-10),((Item->x+10)+32), ((Item->y+10)+30));			
			////InvalidateRect(hWndMain,&RcItem,FALSE);
			DeleteItem(Item);
		//	Draw(&RcItem);
			LeaveCriticalSection(&crit);
			break;
		}
		else if(Item->y > HEIGHT-30){
			EnterCriticalSection(&crit);
			SetRect(&RcItem, (Item->x-10),(Item->y-10),((Item->x+10)+32), ((Item->y+10)+30));			
			////InvalidateRect(hWndMain,&RcItem,FALSE);
			////InvalidateRect(hWndMain,NULL,FALSE);
			DeleteItem(Item);
	//		Draw(&RcItem);
			LeaveCriticalSection(&crit);
			break;
		}
	}
	//SetRect(&RcItem, (Item->x-10),(Item->y-10),((Item->x+10)+32), ((Item->y+10)+30));
	//Draw(&RcItem);
	////InvalidateRect(hWndMain,&RcItem,FALSE);
	return 0;
}

void DropItem(ItemInfo* temp){
	//srand((unsigned)time(NULL));
	DWORD ThreadID;
	HANDLE hThread;
	hThread = CreateThread(NULL,0,DropItemThread,temp,0,&ThreadID);
	//SetThreadPriority(hThread,THREAD_PRIORITY_LOWEST);
	SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
	//SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	CloseHandle(hThread);	
}

DWORD WINAPI ShootThread(LPVOID temp){	
	Missile *NewMissile = CreateMissile(pos+5,314);
	//SetRect(&RcMissile, NewMissile->x*fw,NewMissile->y*fh,(NewMissile->x+3)*fw, (NewMissile->y+30)*fh);
	////InvalidateRect(hWndMain,&RcMissile,FALSE);

	while(TRUE)
	{
		while(gameOvered || paused){Sleep(100);}
		Sleep(10);
		EnterCriticalSection(&Missile_CRT);
		NewMissile->y-=5;		
		SetRect(&RcMissile, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));
//		Draw(&RcMissile);
		////InvalidateRect(hWndMain,&RcMissile,FALSE);
		LeaveCriticalSection(&Missile_CRT);

		int i,j;	// 벽돌배열
		i=(NewMissile->y - mostBrick)/blockY;
		j=(NewMissile->x -20)/blockX;

		if(i>=0 && i<BH && j>=0 && j<BW)
		if(board[i][j]>='0' && board[i][j]<='3'){			
			board[i][j]=' ';
			//DropItem(
			EnterCriticalSection(&Missile_CRT);
			SetRect(&Target,(20+blockX*j),(mostBrick+blockY*i),(20+blockX*(j+1)),(mostBrick+blockY*(i+1)));
	//		Draw(&Target);
			LeaveCriticalSection(&Missile_CRT);
			////InvalidateRect(hWndMain,&Target,FALSE);
			//srand((unsigned)time(NULL));
			if(rand() % 10 == 0){
				tempCoord.x=NewMissile->x;
				tempCoord.y=NewMissile->y;
				tempCoord.randBit=RandItem();
				DropItem(&tempCoord);
			}
			else
			Sound(IDR_TOCK);
			EnterCriticalSection(&Missile_CRT);
			SetRect(&RcMissile, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));			
			////InvalidateRect(hWndMain,&RcMissile,FALSE);
			DeleteMissile(NewMissile);
	//		Draw(&RcMissile);
			LeaveCriticalSection(&Missile_CRT);
			break;
		}
		else if(NewMissile->y <0){
			EnterCriticalSection(&Missile_CRT);
			SetRect(&RcMissile, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));			
			////InvalidateRect(hWndMain,&RcMissile,FALSE);
			DeleteMissile(NewMissile);
	//		Draw(&RcMissile);
			LeaveCriticalSection(&Missile_CRT);
			break;
		}
		//LeaveCriticalSection(&crit); // while문 안에 있을 때
	}
//	SetRect(&RcMissile, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));
//	//InvalidateRect(hWndMain,&RcMissile,FALSE);
	//LeaveCriticalSection(&crit); //while문이 깨질때
	return 0;
}
DWORD WINAPI ShootThread1(LPVOID temp){	
	Missile *NewMissile = CreateMissile(pos+LengthOfBar-7,314);
	//SetRect(&RcMissile1, NewMissile->x*fw,NewMissile->y*fh,(NewMissile->x+3)*fw, (NewMissile->y+30)*fh);
	////InvalidateRect(hWndMain,&RcMissile1,FALSE);

	while(TRUE)
	{
		while(gameOvered || paused){Sleep(100);}
		Sleep(10);
		EnterCriticalSection(&Missile_CRT);
		NewMissile->y-=5;		
		SetRect(&RcMissile1, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));
	//	Draw(&RcMissile1);
		////InvalidateRect(hWndMain,&RcMissile1,FALSE);	
		LeaveCriticalSection(&Missile_CRT);

		int i,j;	// 벽돌배열
		i=(NewMissile->y - mostBrick)/blockY;
		j=(NewMissile->x -20)/blockX;

		if(i>=0 && i<BH && j>=0 && j<BW)
		if(board[i][j]>='0' && board[i][j]<='3'){
			board[i][j]=' ';
			EnterCriticalSection(&Missile_CRT);
			SetRect(&Target,(20+blockX*j),(mostBrick+blockY*i),(20+blockX*(j+1)),(mostBrick+blockY*(i+1)));
		//	Draw(&Target);
			LeaveCriticalSection(&Missile_CRT);
			////InvalidateRect(hWndMain,&Target,FALSE);
			//srand((unsigned)time(NULL));
			if(rand() % 10 == 0){
				tempCoord.x=NewMissile->x;
				tempCoord.y=NewMissile->y;
				tempCoord.randBit=RandItem();
				DropItem(&tempCoord);
			}
			else 
			Sound(IDR_TOCK);
			EnterCriticalSection(&Missile_CRT);
			SetRect(&RcMissile1, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));			
			////InvalidateRect(hWndMain,&RcMissile,FALSE);
			DeleteMissile(NewMissile);
		//	Draw(&RcMissile1);
			LeaveCriticalSection(&Missile_CRT);
			break;
		}
		else if(NewMissile->y <0){
			EnterCriticalSection(&Missile_CRT);
			SetRect(&RcMissile1, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));			
			////InvalidateRect(hWndMain,&RcMissile,FALSE);
			DeleteMissile(NewMissile);
		//	Draw(&RcMissile1);
			LeaveCriticalSection(&Missile_CRT);
			break;
		}
		//LeaveCriticalSection(&crit);
	}
//	SetRect(&RcMissile1, NewMissile->x,NewMissile->y,(NewMissile->x+3), (NewMissile->y+30));
//	//InvalidateRect(hWndMain,&RcMissile1,FALSE);	
	return 0;
}
void Shoot(){
	DWORD ThreadID;
	HANDLE hThread;
	hThread = CreateThread(NULL,0,ShootThread,NULL,0,&ThreadID);
	//SetThreadPriority(hThread,THREAD_PRIORITY_LOWEST);
	SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
	//SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	CloseHandle(hThread);
	hThread = CreateThread(NULL,0,ShootThread1,NULL,0,&ThreadID);
	//SetThreadPriority(hThread,THREAD_PRIORITY_LOWEST);
	SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
	//SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	CloseHandle(hThread);
	ShootCount++;
	if(ShootCount>=MAX_SHOOT){
		BoolShootingPaddle=FALSE;
		ShootCount=0;
		SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
	//	Draw(&Paddle);
		////InvalidateRect(hWndMain,&Paddle,FALSE);
	}
	Sound(IDR_GunFire);
}

DWORD WINAPI ChangeSpeed(LPVOID temp){
	while(TRUE)
	{
		Sleep(5000);
		if(speed<MAX_SPEED)
		{
			speed+=0.1;
		}
	}
	return 0;
}

void CALLBACK HideTitle(HWND hWnd,UINT uMsg, UINT idEvent, DWORD dwTime){	
	HRGN hWndRgn;
	if(BoolFullScreen){
				//GetWindowRect(hWnd,&window);
				//GetClientRect(hWnd,&client);
				//int WindowWidth= width + 2*
				hWndRgn=CreateRectRgn(0,0,width,height);
				SetWindowRgn(hWnd,hWndRgn,TRUE);
			}
			if(!paused)
			while(ShowCursor(FALSE)>=0);
			KillTimer(hWnd,3);
}

inline void CheckBrick(int a,int a1,int b,int b1, BallStruct* Ball){
	//srand((unsigned)time(NULL));
	//
	if(a>=0 && a<BH && b>=0 && b<BW)
	if(board[a][b]>='0' && board[a][b]<='9'){
		//board[i][k]=' ';		
		if(xStriked==false)
		if(a!=a1){if(Pierce==FALSE)
			if(yStriked==false)Ball->dy *= -1;board[a][b]=' ';xStriked=true;
		
		if(rand() % 5 == 0){
			tempCoord.x=Ball->x;
			tempCoord.y=Ball->y;
			tempCoord.dx=Ball->dx;
			tempCoord.dy=Ball->dy;
			tempCoord.randBit=RandItem();
			DropItem(&tempCoord); // 전역변수에 접근
		}
		else	Sound(IDR_TOCK);
		}
		if(yStriked==false)
		if(b!=b1){if(Pierce==FALSE)
		if(xStriked==false)Ball->dx *= -1;board[a][b]=' ';yStriked=true;
		//
		if(rand() % 5 == 0){
			tempCoord.x=Ball->x;
			tempCoord.y=Ball->y;
			tempCoord.dx=Ball->dx;
			tempCoord.dy=Ball->dy;
			tempCoord.randBit=RandItem();
			DropItem(&tempCoord); // 전역변수에 접근
		}
		else	Sound(IDR_TOCK);}
		//EnterCriticalSection(&Brick_CRT);
		SetRect(&Target,(20+blockX*b),(mostBrick+blockY*a),(20+blockX*(b+1)),(mostBrick+blockY*(a+1)));
	//	Draw(&Target);
		////InvalidateRect(hWndMain,&Target,FALSE);
		//LeaveCriticalSection(&Brick_CRT);
		
				
		number--;
		//if(number=0) NEXT;
		//return true;
	}
	//
	return;
}
void KillPaddle(){
}
void MoveBall()
{		
	
	LARGE_INTEGER st,ed,freq,ed1, st1;
	double gap;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&st);
	QueryPerformanceCounter(&st1);
	while(!paused && !gameOvered)
	{	
		HANDLE hThread = GetCurrentProcess();
		// 그리거나 소리내는 동안은 대기		
		//	continue;	// 이렇게 하면 CPU점유율 높을 때 이동이 원천 차단됨.
		//	SetThreadPriority(hMoveThread, THREAD_PRIORITY_IDLE);
		//SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
		// 화질을 위해서 아래것은 꼭 해야함.
	//	if( GetPriorityClass(hThread) == IDLE_PRIORITY_CLASS ){	
	//	if (Sounding == FALSE)
			SetPriorityClass(hThread, HIGH_PRIORITY_CLASS);
		//SetPriorityClass(hThread, NORMAL_PRIORITY_CLASS);
	//	else
	//		SetPriorityClass(hThread, NORMAL_PRIORITY_CLASS);
			// HIGH이면 그리기가 확실히 보장됨.
			// NORMAL이면 사운드도 보장되고, 그리기는 최악을 막음.
			// IDLE이면 사운드만 보장되고, 그리기는 최악이 됨.
	//	}
		QueryPerformanceCounter(&ed);
		gap=((double)(ed.QuadPart-st.QuadPart))/((double)freq.QuadPart);		
		if(gap>0.032/Frame/speed)
		{			
			// 0.01이면 IDLE TIME시 모두 작동.
			if(gap>0.1*BallCount)	// 작업량이 많을 때만 작동
			{				
				QueryPerformanceCounter(&st);
				continue;	// 재검사
			}			
			for(i=0;i<gap/(0.032/Frame/speed);i++)
			{
				
				BallStruct *Next;
				for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Next)
				{
					Next=Ball->next;
					if(Ball->Grabbed==TRUE) continue;	
					static int maxCount = 3;
					//maxCount=8*speed;
					SetRect(&BallRect,(Ball->x)-maxCount,(Ball->y)-maxCount,(Ball->x + BallSize)+maxCount,(Ball->y + BallSize)+maxCount);
				//	Draw(&BallRect);
					//InvalidateRect(hWndMain,&BallRect,FALSE);
					////InvalidateRect(hWndMain,NULL,FALSE);
					//y축
					if(Ball->y + Ball->dy <10 ){ Ball->y = 10; Ball->dy *= -1; }
					else if(Ball->y + Ball->dy > 340)
					{
						Ball->y = 340; Ball->dy *= -1;
						SetRect(&BallRect,(Ball->x)-maxCount,(Ball->y)-maxCount,(Ball->x + BallSize)+maxCount,(Ball->y + BallSize)+maxCount);
			//			Draw(&BallRect);
						//InvalidateRect(hWndMain,&BallRect,FALSE);
						
						if(Ball->next==NULL && Ball->back==NULL){
							if(energy>1)
							{	
								//SetRect(&RCenergy,(545-11*(energy-3)),20,(555-11*(energy+3)),25);
								energy--;
								SetRect(&RCenergy,(545-11*(energy)),20,(555-11*(energy)),25);
						//		Draw(&RCenergy);
								//InvalidateRect(hWndMain,&RCenergy,FALSE);
								Sound(IDR_SHRINK);
							}
							else
							{//DEAD
								DeleteBall(Ball);
								KillPaddle();
								life--;
								if(life>0){					
									InitializeGame();					
								}
								else{				
									gameOvered=true;
									SetRect(&Target,10,HEIGHT/3,WIDTH,2*HEIGHT/2);
									////InvalidateRect(hWndMain,&Target,FALSE);
								//	Draw(&Target);
									SetRect(&RCenergy,(545),20,(555),25);
									energy--;									
									//Draw(&RCenergy);
									//InvalidateRect(hWndMain,&RCenergy,FALSE);				
								}								
								SetRect(&RClife, (559-33*life),3, (589-33*life), 18);
							//	Draw(&RClife);
								////InvalidateRect(hWndMain,&RClife,FALSE);				
								SoundNoStop(IDR_DEAD);
								break;
							}
						}
						else{//공이 1개가 아니면 바로죽음
							//Ball=Ball->next;

							DeleteBall(Ball);
							SoundNoStopShort(IDR_ByeBall);
							//DeadBall = Ball;	// 나중에 지움
							continue;
						}
					}
					else{Ball->y += Ball->dy;}

					//x축
					if(Ball->x + Ball->dx < 20) { Ball->x = 20; Ball->dx *= -1 ; Sound(IDR_TICK);}
					else if(Ball->x + BallSize + Ball->dx > 20+blockX*18) 
					{ Ball->x = 20+blockX*18-BallSize; Ball->dx *= -1; Sound(IDR_TICK);}
					else Ball->x += Ball->dx;
					// 벽돌판정
					
					if(Ball->y <= mostBrick+blockY*15){
						int h,i,j, k;
						int h1,i1,j1, k1;		
						
						h=(Ball->y + Ball->dy - mostBrick+2)/blockY;
						i=(Ball->y + Ball->dy + BallSize - mostBrick-1)/blockY;
						j=(Ball->x + Ball->dx - 20+2)/blockX;
						k=(Ball->x + Ball->dx + BallSize-20-2)/blockX;
						h1=(Ball->y - mostBrick+2)/blockY;
						i1=(Ball->y + BallSize-mostBrick-2)/blockY;
						j1=(Ball->x - 20+2)/blockX;
						k1=(Ball->x + BallSize-20-2)/blockX;

						//srand((unsigned)time(NULL));
						
						if(Ball->dx > 0 && Ball->dy < 0){
							CheckBrick(h,h1,j,j1, Ball);
							CheckBrick(i,i1,k,k1, Ball);
						//	CheckBrick(h,h1,k,k1, Ball);
						}
						if(Ball->dx<0 && Ball->dy<0){
							CheckBrick(h,h1,k,k1, Ball);
							CheckBrick(i,i1,j,j1, Ball);
						//	CheckBrick(h,h1,j,j1, Ball);
						}
						if(Ball->dx>0 && Ball->dy>0){			
							CheckBrick(i,i1,j,j1, Ball);
							CheckBrick(h,h1,k,k1, Ball);
						//	CheckBrick(i,i1,k,k1, Ball);
						}
						if(Ball->dx<0 && Ball->dy>0){
							CheckBrick(i,i1,k,k1, Ball);
							CheckBrick(h,h1,j,j1, Ball);			
						//	CheckBrick(i,i1,j,j1, Ball);
						}
						if(Ball->dx==0 && Ball->dy<0){
							CheckBrick(h,h1,j,j1, Ball);
							CheckBrick(h,h1,k,k1, Ball);
						}
						if(Ball->dx==0 && Ball->dy > 0){
							CheckBrick(i,i1,j,j1, Ball);
							CheckBrick(i,i1,k,k1, Ball);
						}

						xStriked=false;
						yStriked=false;
					}
					

					// 막대판정
					if(pos<= Ball->x +BallSize && pos+LengthOfBar>= Ball->x && Ball->y +Ball->dy + BallSize>329)
					{	
						if(Ball->x >= pos && Ball->x + BallSize <= pos + LengthOfBar)
						if(BoolGrab ==TRUE){
							bGrabbed=true;
							Ball->Grabbed=TRUE;							
							SetRect(&Paddle,pos,310,(pos+LengthOfBar),(310+HeightOfGrab));
					//		Draw(&Paddle);
							////InvalidateRect(hWndMain,&Paddle,FALSE);
							SoundNoStopShort(IDR_GRAB);
						}
						int i,j;
						if(bFallingBrick== FALSE && bUppingBrick == FALSE)
							Sound(IDR_TICK);
						else if(bFallingBrick){
							for(i=BH-1;i>0;i--) for(j=0;j<BW;j++) 
								if(board[i-1][j]>='0' && board[i-1][j]<='9')
							{	
								if(board[i][j] == ' '	// 공백 문자는 셋중 하나며,
														// 확률이 가장 높은 곳을 맨 위로 하여
														// 검사시간을 최소화
									|| board[i][j] == '\n'
									|| board[i][j] == '\0'	)
								{
									board[i][j]=board[i-1][j];
									board[i-1][j]=' ';
								}
							}
							Sound(IDR_Warn);
							//20+blockX*j
							//mostBrick+blockY*i
							SetRect(&BrickRect,20,mostBrick, (20+blockX*18), (mostBrick+blockY*15));
						//	Draw(&BrickRect);
							////InvalidateRect(hWndMain,&BrickRect, FALSE);
							////InvalidateRect(hWndMain,NULL,FALSE);
						}
						else if(bUppingBrick){
							for(i=1;i<BH;i++) for(j=0;j<BW;j++) 
								if(board[i][j]>='0' && board[i][j]<='9')
							{
								if(board[i-1][j] == ' '					
									|| board[i-1][j] == '\n'
									|| board[i-1][j] == '\0'
									)
								{
									board[i-1][j]=board[i][j];
									board[i][j]=' ';
								}
							}
							Sound(IDR_ItemSound);
							SetRect(&BrickRect,20,mostBrick, (20+blockX*18), (mostBrick+blockY*15));
							//Draw(&BrickRect);
							////InvalidateRect(hWndMain,&BrickRect, FALSE);
						}
						Ball->y = 329-BallSize;
						Ball->x = Ball->x + Ball->dx * float(329-BallSize- Ball->y )/float(Ball->dy);					
						//InvalidateRect(hWndMain,&BallRect,FALSE);
						Ball->dx = pow( ((Ball->x + BallSize/2.0)-(pos+LengthOfBar/2.0))/((LengthOfBar/2.0)/3.5), 3);
						if(Ball->dx > 45) Ball->dx=45;
						else if(Ball->dx < -45) Ball->dx=-45;
						if(Ball->dy != 8) Ball->dy = 8.0;
						float t=(8.2/sqrt(pow(Ball->dx,2)+pow(Ball->dy,2))/INIT_FRAME);
						Ball->dx *= t;
						Ball->dy *= t;
						Ball->dy *= -1;
						//InvalidateRect(hWndMain,NULL,FALSE);		
					}	
				}		
				
				st.QuadPart+=(0.032/Frame/speed)*freq.QuadPart;			
			}
			//SetPriorityClass(hThread, NORMAL_PRIORITY_CLASS);
			//InvalidateRect(hWndMain,NULL,FALSE);
			Draw();
			//SetPriorityClass(hThread, HIGH_PRIORITY_CLASS);
			SwitchToThread();
		}
	CloseHandle(hThread);
	}
}

DWORD WINAPI MoveThread(LPVOID temp){
resume:		
	MoveBall();	

	if(gameOvered) return 0;
	
	// 스페이스 입력 받음.
	while(paused){
	if (PeekMessage(&Message,NULL,0,0,PM_NOREMOVE)) {		
		break;
		}Sleep(10);
	
	}
	goto resume;
	return 0;
}


void Threading(){
	DWORD ThreadID;
	HANDLE hThread;
	hThread = GetCurrentProcess();
//	SetPriorityClass(hThread, IDLE_PRIORITY_CLASS);
	SetPriorityClass(hThread, HIGH_PRIORITY_CLASS);
	//SetPriorityClass(hThread, REALTIME_PRIORITY_CLASS);
	//SetPriorityClass(hThread, NORMAL_PRIORITY_CLASS);
	
	CloseHandle(hThread);
	hThread = CreateThread(NULL,0,ChangeSpeed,NULL,0,&ThreadID);
	CloseHandle(hThread);
	hMoveThread = CreateThread(NULL,0,MoveThread,NULL,0,&ThreadID);
	SetThreadPriority(hMoveThread,THREAD_PRIORITY_LOWEST);	
	//hDrawThread = CreateThread(NULL,0,DrawThread,NULL,0,&ThreadID);
	//프로세스 우선순위가 높을 경우 절대 건들면 안 됨.
	//SetThreadPriority(hDrawThread,THREAD_PRIORITY_LOWEST);
	//SetThreadPriority(hThread,THREAD_PRIORITY_IDLE);
	//SetThreadPriority(hMoveThread,THREAD_PRIORITY_LOWEST);
	//CloseHandle(hThread);
}