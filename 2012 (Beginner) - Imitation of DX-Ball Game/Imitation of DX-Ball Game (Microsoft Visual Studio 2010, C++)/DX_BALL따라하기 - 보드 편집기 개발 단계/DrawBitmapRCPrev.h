//int cw,ch;
void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit, LPRECT rc){
	
	int bx,by;
	BITMAP bit;
	
	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	int left =rc->left;
	int top = rc->top;
	int right = rc->right;
	int bottom = rc->bottom;

	// 영역을 벗어나면 리턴
	if(left > x + bx ) return;
	if(top > y + by ) return;
	if(right < x ) return;
	if(bottom < y ) return;
	// 시작과 끝 지점 설정
	if(left < x ) left = x;
	if(top < y ) top =y;
	if(right > x + bx ) right = x + bx;
	if(bottom > y + by) bottom = y + by;

	HDC MemDC;
	HBITMAP OldBitmap;
	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	TransparentBlt(hdc,left - rc->left,top - rc->top,right-left,bottom-top,MemDC,left-x,top-y,right-left,bottom-top,RGB(0,0,0));
		
	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawCenterBitmap(HDC hdc,int cx,int cy,HBITMAP hBit, LPRECT rc){
	
	int bx,by;
	BITMAP bit;	

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	int left =rc->left;
	int top = rc->top;
	int right = rc->right;
	int bottom = rc->bottom;

	// 영역을 벗어나면 리턴
	if(left > cx-bx/2 + bx ) return;
	if(top > cy-by/2 + by ) return;
	if(right < cx-bx/2 ) return;
	if(bottom < cy-by/2 ) return;
	// 시작과 끝 지점 설정
	if(left < cx-bx/2 ) left = cx-bx/2;
	if(top < cy-by/2 ) top =cy-by/2;
	if(right > cx-bx/2 + bx ) right = cx-bx/2 + bx;
	if(bottom > cy-by/2 + by) bottom = cy-by/2 + by;

	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	TransparentBlt(hdc,cx-bx/2,cy-by/2,bx,by,MemDC,0,0,bx,by,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawTileBitmap(HDC hdc,int x,int y,int ex, int ey,HBITMAP hBit, LPRECT rc){
	
	HDC MemDC;
	HBITMAP OldBitmap;
	
	MemDC=CreateCompatibleDC(hdc);
	HDC MemDC2=CreateCompatibleDC(MemDC);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);
	HBITMAP MemBit = CreateCompatibleBitmap(hdc,ex-x,dy-y);
	HBITMAP OldBitmap2 = (HBITMAP)SelectObject(MemDC,MemBit);

	int bx,by;
	BITMAP bit;
	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;
	
	int i,j;

	for(i=0;bx*(i+1)<ex;i++){ for(j=0;by*(j+1)<ey;j++)
	BitBlt(MemDC2,0+bx*i,0+by*j,bx,by,MemDC,0,0,SRCCOPY);
	//세로줄 마지막
	BitBlt(MemDC2,0+bx*i,0+by*j,bx,(ey-by*j),MemDC,0,0,SRCCOPY);
	}
	//가로줄 마지막
	for(j=0;by*(j+1)<ey;j++)
	BitBlt(MemDC2,0+bx*i,0+by*j,(ex-bx*i),by,MemDC,0,0,SRCCOPY);
	//마지막 타일
	BitBlt(MemDC2,0+bx*i,0+by*j,(ex-bx*i),(ey-by*j),MemDC,0,0,SRCCOPY);
	

	GetObject(MemBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	int left =rc->left;
	int top = rc->top;
	int right = rc->right;
	int bottom = rc->bottom;

	// 영역을 벗어나면 리턴
	if(left > x + bx ) return;
	if(top > y + by ) return;
	if(right < x ) return;
	if(bottom < y ) return;
	// 시작과 끝 지점 설정
	if(left < x ) left = x;
	if(top < y ) top =y;
	if(right > x + bx ) right = x + bx;
	if(bottom > y + by) bottom = y + by;

	TransparentBlt(hdc,left - rc->left,top - rc->top,right-left,bottom-top,MemDC2,left-x,top-y,right-left,bottom-top,RGB(0,0,0));
	

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawStretchBitmap(HDC hdc,int x,int y,int sx,int sy, HBITMAP hBit, LPRECT rc){
	HDC MemDC;
	HDC MemDC2;
	HBITMAP OldBitmap;
	HBITMAP OldBitmap2;
	int bx,by;
	BITMAP bit;
	RECT window;
	
	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	int left =rc->left;
	int top = rc->top;
	int right = rc->right;
	int bottom = rc->bottom;
	//return;
	// 영역을 벗어나면 리턴
	if(left > x + sx ) return;
	if(top > y + sy ) return;
	if(right < x ) return;
	if(bottom < y ) return;
	// 시작과 끝 지점 설정
	if(left < x ) left = x;
	if(top < y ) top =y;
	if(right > x + sx ) right = x + sx;
	if(bottom > y + sy) bottom = y + sy;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	TransparentBlt(hdc,left - rc->left,top - rc->top,right-left,bottom-top,MemDC,left-x,top-y,(right-left)*bx/sx,(bottom-top)*by/sy,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawFixBitmap(HDC hdc,int x,int y,int sx,int sy, HBITMAP hBit, LPRECT rc){
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;
	
	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;
	if(sx/bx<=sy/by)
		sy=by*sx/bx;
	else
		sx=bx*sy/by;

	int left =rc->left;
	int top = rc->top;
	int right = rc->right;
	int bottom = rc->bottom;
	//return;
	// 영역을 벗어나면 리턴
	if(left > x + sx ) return;
	if(top > y + sy ) return;
	if(right < x ) return;
	if(bottom < y ) return;
	// 시작과 끝 지점 설정
	if(left < x ) left = x;
	if(top < y ) top =y;
	if(right > x + sx ) right = x + sx;
	if(bottom > y + sy) bottom = y + sy;

	TransparentBlt(hdc,left - rc->left,top - rc->top,right-left,bottom-top,MemDC,left-x,top-y,(right-left)*bx/sx,(bottom-top)*by/sy,RGB(0,0,0));

//	TransparentBlt(hdc,x,y,sx,sy,MemDC,0,0,bx,by,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}
// 새로 추가한 인자는 항상 맨뒤에
// 그런데 이 경우엔 그래도 안 됨.
void DrawStretchBitmapNoTransperent(HDC hdc,int x,int y,int sx,int sy, HBITMAP hBit, LPRECT rc){
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;	
	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	StretchBlt(hdc,x,y,sx,sy,MemDC,0,0,bx,by,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}