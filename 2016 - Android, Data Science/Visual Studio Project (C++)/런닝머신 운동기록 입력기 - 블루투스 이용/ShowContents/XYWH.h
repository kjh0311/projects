#pragma once


typedef struct XYWH
{
	const int
		X, Y, W, H;
} XYWH;


static const XYWH window_xywh = { 720, 700, 420, 320 };


inline XYWH right_top(int w, int h)
{
	XYWH xywh = { 310,40,w,h };
	return xywh;
}


inline XYWH left_top(int w, int h)
{
	XYWH xywh = { 40,40,w,h };
	return xywh;
}


inline XYWH right_from(XYWH left, int offset,  int w, int h)
{
	XYWH xywh = { left.X + left.W + offset, left.Y ,w,h };
	return xywh;
}


inline XYWH down_from(XYWH up, int w, int h)
{
	XYWH xywh = { up.X, up.Y + up.H + 10 ,w,h };
	return xywh;
}



