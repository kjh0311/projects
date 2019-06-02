#define WINVER 0x500
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mmsystem.h"
#include "resource.h"

#define INIT_FRAME 16.0
//#define FULL_FRAME 2.6
#define MAX_ENERGY 3
#define INIT_LIFE 3
#define MAX_LIFE 4
#define MIN_SPEED 1.0
#define INIT_SPEED 1.5
#define MAX_SPEED 2.0
#define INIT_X 292
#define INIT_Y 320
#define INIT_DX 2/INIT_FRAME
#define INIT_DY -8/INIT_FRAME
#define INIT_POS 255
#define WIDTH 590.0
#define HEIGHT 370.0


int Frame=INIT_FRAME;
double Top;
BOOL BoolFullScreen=FALSE;
BOOL Started=FALSE;
COLORREF Color=RGB(0,0,0);
COLORREF crTemp[16];
int Option=1;
int fCount=0;
int i;
void Threading();
DWORD WINAPI ChangeSpeed(LPVOID temp);
DWORD WINAPI MoveThread(LPVOID temp);
void CALLBACK HideTitle(HWND hWnd,UINT uMsg, UINT idEvent, DWORD dwTime);
//void CALLBACK ChangeSpeed(HWND hWnd,UINT uMsg, UINT idEvent, DWORD dwTime);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK BackDlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK HelpDlgProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hHelpDlg;
HWND hWndMain;
HWND hEnergy[MAX_ENERGY];
HWND hLife[MAX_LIFE];
HWND hPaddle;
HMENU hMenu;
MSG Message;
HBITMAP MemBit;
RECT window;
RECT BrickRect;
RECT Paddle;
RECT BallRect;
RECT Target;
RECT RClife;
RECT RCenergy;
RECT RcItem;
RECT RcMissile;
RECT RcMissile1;
BOOL bSound=TRUE;
BOOL bSpacePressed=FALSE;
bool Clicked=false;
bool bGrabbed=true;
bool paused=false;
bool gameOvered=false;
bool xStriked=false;
bool yStriked=false;
bool Striked1=false;
bool Striked2=false;
bool killed=false;
#define BH 14
#define BW 18
char board[BH][BW];
int blockX=30;
int blockY=15;
double width=WIDTH;
double height=HEIGHT;
int mostBrick=30;
unsigned int number=0;
double speed=INIT_SPEED;
int energy=MAX_ENERGY;
int life=INIT_LIFE;
double x=INIT_X, y=INIT_Y;
int pos=INIT_POS;
#define INIT_LENGTH 73
#define MIN_LENGTH 33
#define MAX_LENGTH 193
int LengthOfBar=INIT_LENGTH;
int HeightOfGrab=33;
int HeightOfGrabPaddle=26;
int HeightOfShooting=29;
#define INIT_BALL_SIZE 9
#define MIN_BALL_SIZE 5
#define MAX_BALL_SIZE 13
int BallSize=INIT_BALL_SIZE;
BOOL Pierce=FALSE;
BOOL bFireBall=FALSE;
BOOL bFallingBrick=FALSE;
BOOL bUppingBrick=FALSE;
BOOL BoolGrab=FALSE;
BOOL BoolShootingPaddle=FALSE;
BOOL bDrawing=FALSE;
int GrabCount=0;
#define MAX_GRAB 5
int ShootCount=0;
#define MAX_SHOOT 15
#define INIT_PADDLE_SPEED 20
int PaddleSpeed=INIT_PADDLE_SPEED;
double dx=INIT_DX, dy=INIT_DY;
struct ItemInfo{
	int x,y;
	double dx,dy;
	HBITMAP *randBit;
}tempCoord;	// 임계 구역 안에서만 사용가능
void MoveBar(unsigned int wParam, int speed);
TCHAR String[20]="             ";
HANDLE hMoveThread;
HANDLE hDrawThread;

#include "LinkedList.h"
#include "ShootingStruct.h"
#include "BallStruct.h"
#include "InitCS.h"
#include "TransBlt.h"
#include "Sound.h"
#include "InitializeGame.h"
#include "LoadGraphic.h"
#include "LoadItem.h"
#include "ItemAction.h"
#include "DrawBitmap.h"
#include "DrawBitmapRC.h"
#include "Draw.h"
#include "Dlg.h"
#include "InnerAction.h"
#include "WindowSize.h"
#include "WndProc.h"


//HANDLE moveThread;
//HANDLE ItemThread;