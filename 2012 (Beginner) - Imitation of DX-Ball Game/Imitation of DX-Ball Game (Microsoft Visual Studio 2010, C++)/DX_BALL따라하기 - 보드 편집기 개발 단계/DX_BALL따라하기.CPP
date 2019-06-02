#include "Definition.h"


LPCTSTR lpszClass=TEXT("DX_BALL 따라하기");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{	

	HWND hWnd;
	
	WNDCLASS WndClass;
	g_hInst=hInstance;	

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=CreateSolidBrush(Color);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL; //MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	int WindowWidth = width+GetSystemMetrics(SM_CXFRAME)*2;
	int WindowHeight = height + GetSystemMetrics(SM_CYFRAME)*2+GetSystemMetrics(SM_CYCAPTION)
		+ GetSystemMetrics(SM_CYMENU);
	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW
		,300,150,WindowWidth,WindowHeight,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,MemDC;
	HBITMAP hOldBmp;
	PAINTSTRUCT ps;	
	int i,j;
	FILE *f;	
	HRGN hWndRgn;
	int nHit;
	POINT mpt;
	static int mx,my;
	HBRUSH MyBrush,OldBrush;
	static HBITMAP hBit,OldBit;
	CHOOSECOLOR COL;
	RECT window;
	RECT ClientRect;
	HDWP hdwp;	
	TCHAR str[128];
	HANDLE hThread;
	static LARGE_INTEGER st,ed,freq,ed1, st1;
	double gap;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&st);
	
	int nw,nh;
	int tempdx,tempdy;
	hWndMain=hWnd;
	switch (iMessage) {
	case WM_SIZING:
	case WM_SIZE:			
SIZED:		
		OnSizing();
		break;
	case WM_CREATE:
		OnCreate();		
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		Draw();
		//Draw(&ps.rcPaint); // 주소값 전달이 되어야 하므로 &를 붙임.
						   // 그리고 &**.** 하면 &(**.**)로 간주됨.
		EndPaint(hWnd, &ps);
		return 0;
	case WM_COMMAND:
		OnCommand(wParam);
		switch (LOWORD(wParam)){		
		case IDM_NEW:
			goto NEW;
			break;
		case IDM_PAUSE:
			goto PAUSE;
			break;
		case IDM_SOUND:
			goto SOUND;
			break;
		case IDM_HELP:			
			hHelpDlg=CreateDialog(g_hInst,MAKEINTRESOURCE(IDD_HelpDlg),hWnd,HelpDlgProc);
			SetWindowPos(hHelpDlg,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
			ShowWindow(hHelpDlg,SW_SHOW);
			break;
		case IDM_OPENPICTURE:
			KillTimer(hWnd,3);
			while(ShowCursor(TRUE)<0);
			DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DLGBACK),hWnd,BackDlgProc);			
			SetClassLongPtr(hWnd,GCLP_HBRBACKGROUND,(LONG_PTR)CreateSolidBrush(Color));
			for(i=0;i<life;i++)
			SetClassLongPtr(hLife[i],GCLP_HBRBACKGROUND,(LONG_PTR)CreateSolidBrush(Color));
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case IDM_BACKCOLOR:
			KillTimer(hWnd,3);
			while(ShowCursor(TRUE)<0);
			memset(&COL,0,sizeof(CHOOSECOLOR));
			COL.lStructSize=sizeof(CHOOSECOLOR);
			COL.hwndOwner=hWnd;
			COL.lpCustColors=crTemp;
			COL.Flags=CC_FULLOPEN;
			if(ChooseColor(&COL)!=0){
				Color=COL.rgbResult;
			}
			SetClassLongPtr(hWnd,GCLP_HBRBACKGROUND,(LONG_PTR)CreateSolidBrush(Color));
			for(i=0;i<life;i++)
			SetClassLongPtr(hLife[i],GCLP_HBRBACKGROUND,(LONG_PTR)CreateSolidBrush(Color));
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case ID_DEFSCR:
			DefaultScreen();			
			break;
		case ID_FULLSCR:
			FullScreen();
			//i= GetSystemMetrics(SM_CXSCREEN);
			//goto FULL;
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		}		
		break;
	case WM_KEYDOWN:		
		switch(wParam){
		case VK_LEFT:			
		case VK_RIGHT:
			if(paused || gameOvered) break;
			MoveBar(wParam);			
			break;	
		case VK_SHIFT:
			if(PaddleSpeed!=INIT_PADDLE_SPEED/2){
			PaddleSpeed=INIT_PADDLE_SPEED/2;}
			//else PaddleSpeed=OriginSpeed;
			break;
		case VK_CONTROL:
			if(PaddleSpeed!=2*INIT_PADDLE_SPEED){
			PaddleSpeed=2*INIT_PADDLE_SPEED;}
			//else PaddleSpeed=OriginSpeed;
			break;			
		case VK_SPACE:
			if(life==0) return 0;
NEW:
			if(bSpacePressed) return 0;			
			if(Started==FALSE && !gameOvered && !paused)
			{
				while(ShowCursor(FALSE)>=0);
				if(BoolFullScreen==FALSE){
					GetWindowRect(hWnd,&window);
					//GetClientRect(hWnd,&client);
					SetMenu(hWnd,NULL);
					i= GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME);
					hWndRgn=CreateRectRgn(0,i,window.right-window.left,window.bottom-window.top);
					SetWindowRgn(hWnd,hWndRgn,TRUE);
				}				
				SetTimer(hWnd,3,3000,HideTitle);
				Threading();				
				Started=TRUE;
			}
			if(Started==TRUE)
			{
				if(BoolShootingPaddle  && !gameOvered && !paused){					
					Shoot();						
				}
				if(bGrabbed){
					for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
					{	
						//while(TRUE) Sleep(10000);
						if(Ball->Grabbed){							
							Ball->Grabbed=FALSE;							
						}
					}					
					if(BoolGrab ==TRUE){
						GrabCount++;
						if(GrabCount>=MAX_GRAB){
								BoolGrab = FALSE;
								GrabCount = 0;
								for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next){
									if(Ball->Grabbed)	Ball->Grabbed=FALSE;
								}
							}
					}
					bGrabbed=false;
					SetRect(&Paddle,pos,310,(pos+LengthOfBar),(310+HeightOfGrab));
					InvalidateRect(hWnd,&Paddle,FALSE);	
				}
			}
			bSpacePressed=TRUE;
			break;
		case 'P':
PAUSE:			
			GetWindowRect(hWnd,&window);
			hWndRgn=CreateRectRgn(0,0,window.right-window.left,window.bottom-window.top);
			SetWindowRgn(hWnd,hWndRgn,TRUE);
			SetTimer(hWnd,3,3000,NULL);
			if (gameOvered) break;
			if(paused){
				//if(BoolFullScreen) 
					SetMenu(hWnd,NULL);
				if(BoolFullScreen==FALSE)
					i= GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME);
				else i=0;
				hWndRgn=CreateRectRgn(0,i,window.right-window.left,window.bottom-window.top);
				SetWindowRgn(hWnd,hWndRgn,TRUE);
				paused=false;
				SetRect(&window,10,HEIGHT/4,WIDTH,2*HEIGHT/3);
				InvalidateRect(hWnd,&window,FALSE);
				if(wParam== VK_MENU || wParam== VK_F10)
					SetFocus((HWND)hMenu);
			}
			else{
				// 멈추는 동작
				KillTimer(hWnd,1);
				paused=true;
				//DrawBitmap(hdc,10,height/3,gamePaused);				
			}
			SetRect(&window,10,HEIGHT/4,WIDTH,2*HEIGHT/3);
			InvalidateRect(hWnd,&window,FALSE);
			//Draw(&window);
			break;
		case 'M':
SOUND:
			bSound=!bSound;
			if(bSound) CheckMenuItem(hMenu,IDM_SOUND,MF_BYCOMMAND | MF_CHECKED);
			else CheckMenuItem(hMenu,IDM_SOUND,MF_BYCOMMAND | MF_UNCHECKED);
			break;
		case 'F':
			FullScreen();
			break;
		}		
		return 0;
	case WM_SYSKEYDOWN:
		switch(wParam){
		case VK_MENU:
		case VK_F10:
			SetMenu(hWnd,hMenu);
			if(BoolFullScreen){				
				SetTimer(hWnd,4,5000,NULL);
			}
			while(ShowCursor(TRUE)<0);
			if(!paused)
			goto PAUSE;
			break;
		case VK_RETURN:
			FullScreen();
			break;
		}
		break;
		
	case WM_NCHITTEST:
		nHit=DefWindowProc(hWnd,iMessage,wParam,lParam);
		if(Clicked==true)
		if(nHit==HTCLIENT) {
			nHit|=HTCAPTION;
		}
		
		return nHit;
		
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		Clicked=true;
		goto rgn;
	//	Sound(IDR_DEAD);
	case WM_MOUSEMOVE:
		if(mx!=LOWORD(lParam) || my!=HIWORD(lParam)){
rgn:
		while(ShowCursor(TRUE)<0);	//0보다 작은 동안 아무것도 안 함.
		if(!FullScreen){
			GetWindowRect(hWnd,&window);
			hWndRgn=CreateRectRgn(0,0,window.right-window.left,window.bottom-window.top);
			SetWindowRgn(hWnd,hWndRgn,TRUE);
			SetMenu(hWnd,hMenu);
		}		
		SetTimer(hWnd,3,3000,HideTitle);
		}
		mx=LOWORD(lParam);
		my=HIWORD(lParam);
		
		break;
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		Clicked=false;
		break;
	case WM_KEYUP:
		switch(wParam){
		case VK_SHIFT:
		case VK_CONTROL:
			PaddleSpeed=INIT_PADDLE_SPEED;
			break;
		case VK_SPACE:
			bSpacePressed=FALSE;
		}
		return 0;
	case WM_ACTIVATEAPP:
		if(wParam==FALSE && paused==false)
			goto PAUSE;
			break;
	case WM_DESTROY:
		DestroyCS();
		CloseHandle(hMoveThread);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}