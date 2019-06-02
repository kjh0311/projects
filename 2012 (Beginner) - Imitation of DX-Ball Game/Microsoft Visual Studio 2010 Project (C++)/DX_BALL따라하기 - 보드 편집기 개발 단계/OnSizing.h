void OnSizing()
{
	GetWindowRect(hWnd,&window);
		nw=window.right-window.left;
		nh=window.bottom-window.top;
		GetClientRect(hWnd,&ClientRect);
		width=ClientRect.right;
		height=ClientRect.bottom;

		hWndRgn=CreateRectRgn(0,0,nw,nh);
		
		SetWindowRgn(hWnd,hWndRgn,TRUE);	
}