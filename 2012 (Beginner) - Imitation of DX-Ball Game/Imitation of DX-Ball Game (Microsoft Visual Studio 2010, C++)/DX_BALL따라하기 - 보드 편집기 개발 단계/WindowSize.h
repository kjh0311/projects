//extern int width, height;
void DefaultScreen(){
	width=WIDTH;
	height=HEIGHT;
	int WindowWidth=width+2*GetSystemMetrics(SM_CXFRAME);
	int WindowHeight=height+2*GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYMENU);
	SetWindowPos(hWndMain,NULL,0,0,WindowWidth,WindowHeight,SWP_NOMOVE|SWP_NOZORDER);
}
void FullScreen(){
	static double tempWidth,tempHeight;
	static int tempXpos,tempYpos;
	LONG Style;
	if(BoolFullScreen){
				BoolFullScreen=FALSE;
				SetMenu(hWndMain,hMenu);
				Style=GetWindowLongPtr(hWndMain,GWL_STYLE);
				//Style |= WS_CAPTION;
				Style &= ~WS_POPUPWINDOW;
				Style |=WS_OVERLAPPEDWINDOW;
				SetWindowLongPtr(hWndMain,GWL_STYLE,Style);
				width=tempWidth;
				height=tempHeight;
				int WindowWidth = width+GetSystemMetrics(SM_CXFRAME)*2;
				int WindowHeight = height + GetSystemMetrics(SM_CYFRAME)*2+GetSystemMetrics(SM_CYCAPTION)
					+ GetSystemMetrics(SM_CYMENU);
				SetWindowPos(hWndMain,NULL,tempXpos,tempYpos,WindowWidth,WindowHeight,SWP_NOZORDER);
				SetTimer(hWndMain,3,3000,HideTitle);
			}
			else{
				BoolFullScreen=TRUE;
				GetWindowRect(hWndMain,&window);
				tempXpos=window.left;
				tempYpos=window.top;
				//SetMenu(hWnd,NULL);
				Style=GetWindowLongPtr(hWndMain,GWL_STYLE);
				Style &= ~WS_OVERLAPPEDWINDOW;
				Style |=WS_POPUPWINDOW;
				//Style &= ~WS_CAPTION;
				SetWindowLongPtr(hWndMain,GWL_STYLE,Style);
				i= GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENU);
				tempWidth=width;
				tempHeight=height;				
				width=GetSystemMetrics(SM_CXSCREEN);
				height=GetSystemMetrics(SM_CYSCREEN);
				SetWindowPos(hWndMain,NULL,0,0,width,height,SWP_NOZORDER);
				//SetWindowPos(hWndMain,NULL,0,0,width,height,SWP_NOZORDER);
				//InvalidateRect(hWnd,NULL,FALSE);
				while(ShowCursor(FALSE)>=0);
				//SetTimer(hWnd,3,3000,HideTitle);
			}
}