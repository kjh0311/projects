//extern double width,height;
#define fh ( (height/HEIGHT)*(1+Top*(height-HEIGHT)/(HEIGHT*height)) )
#define fh2 ( (height/HEIGHT) )
#define fw (width/WIDTH)

//int cw,ch;
void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit){
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;
	RECT window;

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);	
	TransparentBlt(hdc,x,y,bx,by,MemDC,0,0,bx,by,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawCenterBitmap(HDC hdc,int cx,int cy,HBITMAP hBit){
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;
	
	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	TransparentBlt(hdc,cx-bx/2,cy-by/2,bx,by,MemDC,0,0,bx,by,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawTileBitmap(HDC hdc,int x,int y,int ex, int ey,HBITMAP hBit){
	HDC MemDC;
	HBITMAP OldBitmap;
	int i,j;
	int bx,by;
	BITMAP bit;
	
	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;
	
	for(i=0;bx*(i+1)<ex;i++){ for(j=0;by*(j+1)<ey;j++)
	TransparentBlt(hdc,x+bx*i,y+by*j,bx,by,MemDC,0,0,bx,by,RGB(0,0,0));
	//세로줄 마지막
	TransparentBlt(hdc,x+bx*i,y+by*j,bx,(ey-by*j),MemDC,0,0,bx,(ey-by*j),RGB(0,0,0));
	}
	//가로줄 마지막
	for(j=0;by*(j+1)<ey;j++)
	TransparentBlt(hdc,x+bx*i,y+by*j,(ex-bx*i),by,MemDC,0,0,(ex-bx*i),by,RGB(0,0,0));
	//마지막 타일
	TransparentBlt(hdc,x+bx*i,y+by*j,(ex-bx*i),(ey-by*j),MemDC,0,0,(ex-bx*i),(ey-by*j),RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawStretchBitmap(HDC hdc,int x,int y,int sx,int sy, HBITMAP hBit){
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;
	
	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	TransparentBlt(hdc,x,y,sx,sy,MemDC,0,0,bx,by,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawFixBitmap(HDC hdc,int x,int y,int sx,int sy, HBITMAP hBit){
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
	TransparentBlt(hdc,x,y,sx,sy,MemDC,0,0,bx,by,RGB(0,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawStretchBitmapNoTransperent(HDC hdc,int x,int y,int sx,int sy, HBITMAP hBit){
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