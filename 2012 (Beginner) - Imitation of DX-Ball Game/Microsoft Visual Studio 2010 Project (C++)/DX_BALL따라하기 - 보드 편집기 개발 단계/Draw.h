void Draw(){
//	RECT rc;
//	SetRect(&rc,0,0,WIDTH,HEIGHT);
//	Draw(&rc);
//	return;
//	exit(0);
//	EnterCriticalSection(&DrawCrt);
	HDC hdc,MemDC;
	HBITMAP hOldBmp;
	HBRUSH MyBrush,OldBrush;
	int i,j;
	static HBITMAP hBit,OldBit;
	static HBITMAP MemBit;

	hdc=GetDC(hWndMain);//BeginPaint(hWnd, &ps);
		if(MemBit) DeleteObject(MemBit);
		MemBit=CreateCompatibleBitmap(hdc,WIDTH,HEIGHT);
		MemDC=CreateCompatibleDC(hdc);
		hOldBmp=(HBITMAP)SelectObject(MemDC, MemBit);
		MyBrush=CreateSolidBrush(Color);
		OldBrush=(HBRUSH)SelectObject(MemDC,MyBrush);
		SetRect(&window,0,0,WIDTH,HEIGHT);
		FillRect(MemDC,&window,MyBrush);
		SelectObject(MemDC,OldBrush);
		DeleteObject(MyBrush);

		//background
		switch (Option){
		case 1:
			DrawBitmap(MemDC,0,0,BitFile);
			break;
		case 2:
			DrawCenterBitmap(MemDC,WIDTH/2,HEIGHT/2,BitFile);
			break;
		case 3:
			DrawTileBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile);
			break;
		case 4:
			DrawStretchBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile);
			break;
		case 5:
			DrawFixBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile);
			break;
		}
		
		for(i=0;i<BH;i++) for(j=0;j<BW;j++) 
		if(board[i][j]>='0' && board[i][j]<='9')
		{	//한자리수만 검사가능
			int k=board[i][j] - '0';	//문자를 숫자로
			DrawBitmap(MemDC,20+blockX*j,mostBrick+blockY*i,brick[k]);
			//DrawBitmap(MemDC,20+blockX*j,mostBrick+blockY*i,brick[k]);
			//number+=1;
		}
		DrawBitmap(MemDC,0,0,left);
		DrawBitmap(MemDC,20+blockX*18,0,right);

		// Life & Energy
		if (MAX_ENERGY>1)	//에너지 게이지가 있을 경우만 그림.
			for (i=0;i<energy;i++){
				SetRect(&RCenergy,(545-11*i),20,(555-11*i),25);
				MyBrush= CreateSolidBrush(RGB(0,255,255));				
				FillRect(MemDC,&RCenergy, MyBrush );
				DeleteObject(MyBrush);
			}
		for (i=1;i<life;i++)
			DrawStretchBitmap(MemDC,559-33*i,3,30,15, bar);
		if(life>0){				
			if(BoolShootingPaddle == TRUE){
				DrawStretchBitmap(MemDC,pos,314, LengthOfBar, HeightOfShooting, ShootingPaddle);
				if(bGrabbed)	DrawStretchBitmap(MemDC,pos,310, LengthOfBar, 9, GrabLaser);
			}
			else if(bGrabbed) DrawStretchBitmap(MemDC,pos,310, LengthOfBar, HeightOfGrab, Grabbed);
			else if(BoolGrab == TRUE) DrawStretchBitmap(MemDC,pos,318, LengthOfBar, HeightOfGrabPaddle, GrabPaddle);			
			else DrawStretchBitmap(MemDC,pos,329, LengthOfBar, 14,bar);
			
			//for(BallStruct *CheckBall = FirstBall; CheckBall!=NULL; CheckBall=CheckBall->next;) 와 동일
			EnterCriticalSection(&Ball_CRT);
			BallStruct *CheckBall = FirstBall;
			while(CheckBall != NULL)
			{
				if(Pierce==FALSE && bFireBall==FALSE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, ball);
				else if(bFireBall==TRUE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, FireBall);
				else if(Pierce==TRUE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, PierceBall);
				CheckBall=CheckBall->next;
			}
			LeaveCriticalSection(&Ball_CRT);
			//아이템 그리기
			EnterCriticalSection(&crit);
			DropingItem *check = DropingItemHead;
			while(check != NULL)	//check가 NULL이면 튕겨나감
			{
				//주소값 저장
				DrawBitmap(MemDC,check->x,check->y,*(check->rand));
				check=check->next;
			}
			LeaveCriticalSection(&crit);
			EnterCriticalSection(&Missile_CRT);
			//레이저 그리기
			Missile *check1 = MissileHead;
			while(check1 != NULL)	//check가 NULL이면 튕겨나감
			{
				//주소값 저장
				DrawBitmap(MemDC,check1->x,check1->y,Laser);			
				check1=check1->next;
			}
			LeaveCriticalSection(&Missile_CRT);
			if(paused) DrawBitmap(MemDC,10,2*HEIGHT/7,gamePaused);
		}
		//LeaveCriticalSection(&crit);
		//ValidateRect(hWndMain,rc);
		else if(life==0) DrawBitmap(MemDC,WIDTH/4,HEIGHT/3,gameover);		
		SelectObject(MemDC,hOldBmp);
		DeleteDC(MemDC);		
		//ReleaseDC(hWndMain,hdc);
		// DC는 이미 얻었음.d
		//hdc=GetDC(hWndMain);
		// 우선순위 높이면 잘 그려짐.
		DrawStretchBitmapNoTransperent(hdc,0,0,WIDTH*fw,HEIGHT*fh,MemBit);
		ReleaseDC(hWndMain,hdc);
		//DeleteObject(MemBit);
		LeaveCriticalSection(&DrawCrt);
}
/*
void Draw(LPRECT rc){
	HDC hdc,MemDC;
	HBITMAP hOldBmp;
	HBRUSH MyBrush,OldBrush;
	int i,j;
	static HBITMAP hBit,OldBit;
	static HBITMAP MemBit;

	hdc=GetDC(hWndMain);//BeginPaint(hWnd, &ps);
		if(MemBit) DeleteObject(MemBit);
		MemBit=CreateCompatibleBitmap(hdc,WIDTH,HEIGHT);
		MemDC=CreateCompatibleDC(hdc);
		hOldBmp=(HBITMAP)SelectObject(MemDC, MemBit);
		MyBrush=CreateSolidBrush(Color);
		OldBrush=(HBRUSH)SelectObject(MemDC,MyBrush);
		//SetRect(&window,0,0,WIDTH,HEIGHT);
		SetRect(&window,rc->left,rc->top,rc->right,rc->bottom);
		FillRect(MemDC,&window,MyBrush);
		SelectObject(MemDC,OldBrush);
		DeleteObject(MyBrush);

		//background
		switch (Option){
		case 1:
			DrawBitmap(MemDC,0,0,BitFile);
			break;
		case 2:
			DrawCenterBitmap(MemDC,WIDTH/2,HEIGHT/2,BitFile);
			break;
		case 3:
			DrawTileBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile);
			break;
		case 4:
			DrawStretchBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile);
			break;
		case 5:
			DrawFixBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile);
			break;
		}
		
		for(i=0;i<BH;i++) for(j=0;j<BW;j++) 
		if(board[i][j]>='0' && board[i][j]<='9')
		{	//한자리수만 검사가능
			int k=board[i][j] - '0';	//문자를 숫자로
			DrawBitmap(MemDC,20+blockX*j,mostBrick+blockY*i,brick[k]);
		}
		DrawBitmap(MemDC,0,0,left);
		DrawBitmap(MemDC,20+blockX*18,0,right);

		// Life & Energy
		if (MAX_ENERGY>1)	//에너지 게이지가 있을 경우만 그림.
			for (i=0;i<energy;i++){
				SetRect(&RCenergy,(545-11*i),20,(555-11*i),25);
				MyBrush= CreateSolidBrush(RGB(0,255,255));				
				FillRect(MemDC,&RCenergy, MyBrush );
				DeleteObject(MyBrush);
			}
		for (i=1;i<life;i++)
			DrawStretchBitmap(MemDC,559-33*i,3,30,15, bar);
		if(life>0){				
			if(BoolShootingPaddle == TRUE){
				DrawStretchBitmap(MemDC,pos,314, LengthOfBar, HeightOfShooting, ShootingPaddle);
				if(bGrabbed)	DrawStretchBitmap(MemDC,pos,310, LengthOfBar, 9, GrabLaser);
			}
			else if(bGrabbed) DrawStretchBitmap(MemDC,pos,310, LengthOfBar, HeightOfGrab, Grabbed);
			else if(BoolGrab == TRUE) DrawStretchBitmap(MemDC,pos,318, LengthOfBar, HeightOfGrabPaddle, GrabPaddle);			
			else DrawStretchBitmap(MemDC,pos,329, LengthOfBar, 14,bar);
			
			//for(BallStruct *CheckBall = FirstBall; CheckBall!=NULL; CheckBall=CheckBall->next;) 와 동일
			EnterCriticalSection(&Ball_CRT);
			BallStruct *CheckBall = FirstBall;
			while(CheckBall != NULL)
			{
				if(Pierce==FALSE && bFireBall==FALSE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, ball);
				else if(bFireBall==TRUE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, FireBall);
				else if(Pierce==TRUE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, PierceBall);
				CheckBall=CheckBall->next;
			}
			LeaveCriticalSection(&Ball_CRT);
			//아이템 그리기
			EnterCriticalSection(&crit);
			DropingItem *check = DropingItemHead;
			while(check != NULL)	//check가 NULL이면 튕겨나감
			{
				//주소값 저장
				DrawBitmap(MemDC,check->x,check->y,*(check->rand));
				check=check->next;
			}
			LeaveCriticalSection(&crit);
			EnterCriticalSection(&Missile_CRT);
			//레이저 그리기
			Missile *check1 = MissileHead;
			while(check1 != NULL)	//check가 NULL이면 튕겨나감
			{
				//주소값 저장
				DrawBitmap(MemDC,check1->x,check1->y,Laser);			
				check1=check1->next;
			}
			LeaveCriticalSection(&Missile_CRT);
			if(paused) DrawBitmap(MemDC,10,2*HEIGHT/7,gamePaused);
		}
		//LeaveCriticalSection(&crit);
		//ValidateRect(hWndMain,rc);
		else if(life==0) DrawBitmap(MemDC,WIDTH/4,HEIGHT/3,gameover);		
		SelectObject(MemDC,hOldBmp);
		DeleteDC(MemDC);		
		//ReleaseDC(hWndMain,hdc);
		// DC는 이미 얻었음.d
		//hdc=GetDC(hWndMain);
		// 우선순위 높이면 잘 그려짐.
		DrawStretchBitmapNoTransperent(hdc,0,0,WIDTH*fw,HEIGHT*fh2,MemBit);
		ReleaseDC(hWndMain,hdc);
		DeleteObject(MemBit);
		LeaveCriticalSection(&DrawCrt);
}
*/
/*
void Draw(LPRECT rc){
//	EnterCriticalSection(&DrawCrt);
	//////////////////////////////////////
	HDC hdc,MemDC;
	HBITMAP hOldBmp;
	HBRUSH MyBrush,OldBrush;
	int i,j;
	static HBITMAP hBit,OldBit;
	static HBITMAP MemBit;

	hdc=GetDC(hWndMain);//BeginPaint(hWnd, &ps);	
		// 아래 것은 문제가 있음.(좀만 고치면 됨)
		// 즉, WIDTH는 일치하지만 HEIGHT가 불일치
//		MemBit=CreateCompatibleBitmap(hdc,(rc->right - rc->left),(rc->bottom - rc->top)	);
	if(MemBit) DeleteObject(MemBit);
		MemBit=CreateCompatibleBitmap(hdc,WIDTH,HEIGHT);
		MemDC=CreateCompatibleDC(hdc);
		hOldBmp=(HBITMAP)SelectObject(MemDC, MemBit);
		MyBrush=CreateSolidBrush(Color);
		OldBrush=(HBRUSH)SelectObject(MemDC,MyBrush);
		// 잘못쓰면 종료됨.
//		SetRect(&window,0,0,(rc->right - rc->left),(rc->bottom - rc->top));
//		SetRect(&window,rc->left,rc->top,(rc->right - rc->left),(rc->bottom - rc->top));
//		SetRect(&window,0,0,WIDTH,HEIGHT);
		SetRect(&window,rc->left,rc->top,rc->right,rc->bottom);
		FillRect(MemDC,&window,MyBrush);
		SelectObject(MemDC,OldBrush);
		DeleteObject(MyBrush);

		//background
		switch (Option){
		case 1:
			DrawBitmap(MemDC,0,0,BitFile,rc);
			break;
		case 2:
			DrawCenterBitmap(MemDC,WIDTH/2,HEIGHT/2,BitFile,rc);
			break;
		case 3:
			DrawTileBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile,rc);
			break;
		case 4:
			DrawStretchBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile,rc);
			break;
		case 5:
			DrawFixBitmap(MemDC,0,0,WIDTH,HEIGHT,BitFile,rc);
			break;
		}
		
		for(i=0;i<BH;i++) for(j=0;j<BW;j++) 
		if(board[i][j]>='0' && board[i][j]<='9')
		{	//한자리수만 검사가능
			int k=board[i][j] - '0';	//문자를 숫자로
			DrawBitmap(MemDC,20+blockX*j,mostBrick+blockY*i,brick[k],rc);
			//number+=1;
		}
		// 이게 먹혀야 함.
		DrawBitmap(MemDC,0,0,left,rc);
		DrawBitmap(MemDC,20+blockX*18,0,right,rc);

		// Life & Energy
		if (MAX_ENERGY>1)	//에너지 게이지가 있을 경우만 그림.
			for (i=0;i<energy;i++){
				SetRect(&RCenergy,(545-11*i)-(rc->left),20-(rc->top),(555-11*i)-(rc->left),25-(rc->top));
				MyBrush= CreateSolidBrush(RGB(0,255,255));				
				FillRect(MemDC,&RCenergy, MyBrush );
				DeleteObject(MyBrush);
			}
		for (i=1;i<life;i++)
			DrawStretchBitmap(MemDC,559-33*i,3,30,15, bar,rc);
		if(life>0){				
			if(BoolShootingPaddle == TRUE){
				DrawStretchBitmap(MemDC,pos,314, LengthOfBar, HeightOfShooting, ShootingPaddle,rc);
				if(bGrabbed)	DrawStretchBitmap(MemDC,pos,310, LengthOfBar, 9, GrabLaser,rc);
			}
			else if(bGrabbed) DrawStretchBitmap(MemDC,pos,310, LengthOfBar, HeightOfGrab, Grabbed,rc);
			else if(BoolGrab == TRUE) DrawStretchBitmap(MemDC,pos,318, LengthOfBar, HeightOfGrabPaddle, GrabPaddle,rc);
			else 
				DrawStretchBitmap(MemDC,pos,329, LengthOfBar, 14,bar,rc);
			
			//for(BallStruct *CheckBall = FirstBall; CheckBall!=NULL; CheckBall=CheckBall->next;) 와 동일
			EnterCriticalSection(&Ball_CRT);
			BallStruct *CheckBall = FirstBall;
			while(CheckBall != NULL)
			{
				if(Pierce==FALSE && bFireBall==FALSE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, ball,rc);
				//if(Pierce==FALSE && bFireBall==FALSE) DrawBitmap(MemDC,CheckBall->x,CheckBall->y,ball,rc);
				else if(bFireBall==TRUE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, FireBall,rc);
				else if(Pierce==TRUE) DrawStretchBitmap(MemDC,CheckBall->x,CheckBall->y,BallSize, BallSize, PierceBall,rc);
				CheckBall=CheckBall->next;
			}
			LeaveCriticalSection(&Ball_CRT);
			//아이템 그리기
		//	EnterCriticalSection(&crit);
			DropingItem *check = DropingItemHead;
			while(check != NULL)	//check가 NULL이면 튕겨나감
			{
				//주소값 저장
				DrawBitmap(MemDC,check->x,check->y,*(check->rand),rc);
				check=check->next;
			}
		//	LeaveCriticalSection(&crit);
		//	EnterCriticalSection(&Missile_CRT);
			//레이저 그리기
			Missile *check1 = MissileHead;
			while(check1 != NULL)	//check가 NULL이면 튕겨나감
			{
				//주소값 저장
				DrawBitmap(MemDC,check1->x,check1->y,Laser,rc);			
				check1=check1->next;
			}
		//	LeaveCriticalSection(&Missile_CRT);
			if(paused) DrawBitmap(MemDC,10,2*HEIGHT/7,gamePaused,rc);
		}
		//LeaveCriticalSection(&crit);
		//ValidateRect(hWndMain,rc);
		else if(life==0) DrawBitmap(MemDC,WIDTH/4,HEIGHT/3,gameover,rc);		
		SelectObject(MemDC,hOldBmp);
		DeleteDC(MemDC);		
		//ReleaseDC(hWndMain,hdc);
		// DC는 이미 얻었음.d
		//hdc=GetDC(hWndMain);
		// 우선순위 높이면 잘 그려짐.
		//rc = &rc1;
		DrawStretchBitmapNoTransperent(hdc,rc->left*fw,rc->top*fh,(rc->right - rc->left)*fw,(rc->bottom - rc->top)*fh,MemBit,rc);
		//DrawStretchBitmapNoTransperent(hdc,rc->left*fw,rc->top*fh2,(rc->right - rc->left)*fw,(rc->bottom - rc->top)*fh2,MemBit);
		//DrawStretchBitmapNoTransperent(hdc,0,0,width,height,MemBit,rc);
		ReleaseDC(hWndMain,hdc);
		//DeleteObject(MemBit);
	//	LeaveCriticalSection(&DrawCrt);
}
*/