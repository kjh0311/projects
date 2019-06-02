void ExpandPAD(){
	SoundNoStop(IDR_Expand);
	if(LengthOfBar>=MAX_LENGTH) return;
	pos-=20;
	LengthOfBar+=40;
	if(20+blockX*18 < pos + LengthOfBar)
		pos= 20+blockX*18 - LengthOfBar;
	else if(pos<20)	pos = 20;
	SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
	//InvalidateRect(hWndMain,&Paddle,FALSE);
}
void ShrinkPAD(){
	SoundNoStop(IDR_SHRINK);
	if(LengthOfBar<=MIN_LENGTH) return;
	SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
	pos+=20;
	LengthOfBar-=40;
	//InvalidateRect(hWndMain,&Paddle,FALSE);
}
void ExpandBall(){
	SoundNoStop(IDR_Expand);
	if(BallSize >= MAX_BALL_SIZE) return;
	
	// 아래의 것이 반영 안 됨.//
		for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
		{
				Ball->x-=(MAX_BALL_SIZE-BallSize)/2;	
				Ball->y-=(MAX_BALL_SIZE-BallSize)/2;
				if(Ball->x<20) Ball->x=20;
				else if(Ball->x+BallSize> 20+blockX*18)
					Ball->x = 20+blockX*18 -BallSize;
				if(Ball->y<20) Ball->y=20;
	
				if(Ball->Grabbed==TRUE)
				{
					(Ball->y) -= (MAX_BALL_SIZE-BallSize)/2;
				}
		}
		BallSize=MAX_BALL_SIZE;
}

	//SetRect(&BallRect,(x)*(width/WIDTH)-5,(y)*fh-5,(x+BallSize)*(width/WIDTH)+5,(y+BallSize)*fh+5);
	////InvalidateRect(hWndMain,&BallRect,FALSE);


void ShrinkBall(){
	SoundNoStop(IDR_Warn);
	if(BallSize <= MIN_BALL_SIZE) return;
	for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
	{
		Ball->x+=(BallSize-MIN_BALL_SIZE)/2;
		Ball->y+=(BallSize-MIN_BALL_SIZE)/2;
	}
	BallSize=MIN_BALL_SIZE;
	SetRect(&BallRect,(x)-5,(y)-5,(x+BallSize)+5,(y+BallSize)+5);
	//InvalidateRect(hWndMain,&BallRect,FALSE);
}

void EnableGrab(){
	SoundNoStop(IDR_ItemSound);
	if(BoolGrab==FALSE){
		BoolGrab=TRUE;
		SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
		//InvalidateRect(hWndMain,&Paddle,FALSE);
	}
	else
		GrabCount-=MAX_GRAB;
}

void LifeUp(){
	if(life<MAX_LIFE){
		SoundNoStop(IDR_LifeUp);
		SetRect(&RClife, (559-33*life),3, (589-33*life), 18);
		//InvalidateRect(hWndMain,&RClife,FALSE);
		life++;
		////InvalidateRect(hWndMain,NULL,FALSE);
	}
	else
		SoundNoStop(IDR_ItemSound);
}

void SpeedUp(){
	SoundNoStop(IDR_Danger);
	speed+=0.5;	// speed 0.5 증가
	if(speed>MAX_SPEED)	speed=MAX_SPEED;
}
void SpeedDown(){
	SoundNoStop(IDR_SHRINK);
	speed-=1.0;	// speed 1.0 감소
	if(speed<MIN_SPEED)	speed=MIN_SPEED;
}
void EnergyUp(){
	if(energy<MAX_ENERGY){
		UpdateWindow(hWndMain);
		SoundNoStop(IDR_Expand);
		//UpdateWindow(hWndMain);
		SetRect(&RCenergy,(545-11*energy),20,(555-11*energy),25);
		//InvalidateRect(hWndMain,&RCenergy,FALSE);
		energy++;
	}
	else
		Sound(IDR_ItemSound);
}
void PiercingBall(){
	SoundNoStop(IDR_ItemSound);
	if(Pierce==FALSE)
		Pierce=TRUE;
}
void Fire_Ball(){
	SoundNoStop(IDR_ItemSound);
	if(bFireBall==FALSE)
		bFireBall=TRUE;
}
void Falling_Brick(){	
	if(bFallingBrick==FALSE){
		if(bUppingBrick==TRUE){
			Sound(IDR_ItemSound);
			bUppingBrick=FALSE;
		}
		else{
			SoundNoStopShort(IDR_Danger);
			bFallingBrick=TRUE;
		}
	}
	else
		SoundNoStop(IDR_Danger);
}
void Upping_Brick(){	
	if(bUppingBrick==FALSE){
		SoundNoStop(IDR_Expand);
		if(bFallingBrick==TRUE)
			bFallingBrick=FALSE;
		else
			bUppingBrick=TRUE;
	}
	else Sound(IDR_ItemSound);
}

void EmptyItem(){
	SoundNoStop(IDR_SHRINK);
	BoolGrab=FALSE;
	BoolShootingPaddle=FALSE;
	Pierce=FALSE;
	bFireBall=FALSE;
	bFallingBrick=FALSE;
	bUppingBrick=FALSE;
//	Draw(NULL);
	////InvalidateRect(NULL);
}

void EnableShoot(){
	SoundNoStop(IDR_ItemSound);
	if(BoolShootingPaddle==FALSE){
		BoolShootingPaddle=TRUE;
		SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
		//InvalidateRect(hWndMain,&Paddle,FALSE);
	}
	else
		ShootCount-=MAX_SHOOT;
}
#define PI 3.141593
void SplitBall(){	
	SoundNoStop(IDR_ItemSound);
	//for(BallStruct *Ball = FirstBall; Ball!=NULL; Ball=Ball->next)
	int number=BallCount;
	double dx,dy; // 선언
	double T, t;
	// 아래 쓰면 지연이 너무 큼
	//EnterCriticalSection(&Ball_CRT);
	BallStruct *Ball = FirstBall;
	for(int i=0;i<number;i++){	
		dx=Frame*Ball->dx;
		dy=Frame*Ball->dy;
		T=atan(dy/dx);
		if( T > -PI/4 && T < PI/4 )
			dy*=-1;
		else dx*=-1;
		//pow는 int만 받음
		//float t=(8.2/sqrt(pow(Ball->dx,2)+pow(Ball->dy,2))/INIT_FRAME);	
		//float dx=Ball->dx*INIT_FRAME+6;
		//float dy=Ball->dy*INIT_FRAME-8;		
		//dx=10*Ball->dx*cos(PI/3.0);	//+8로 해도됨.
		//dy=10*Ball->dy*sin(PI/3.0);	//PI/8은 공의 방향이 수평으로 고정되는 것을 방지
		t=(8.2/sqrt(pow(dx,2)+pow(dy,2))/INIT_FRAME);
		BallStruct *NewBall = CreateBall(Ball->x,Ball->y,dx*t, dy*t);
		NewBall->Grabbed=Ball->Grabbed;	// 상속받음
		Ball=Ball->next;
	} // 두 칸 뒤를 내다봄.
	//LeaveCriticalSection(&Ball_CRT);
}
void EightBall(){
	SoundNoStop(IDR_ItemSound);
	float dx,dy; // 선언
	float T, t;
	//EnterCriticalSection(&Ball_CRT);	// 포인터를 잡기 전에는 임계구역을 지정(쓰레드의 기본)
	BallStruct *HighBall = FirstBall;
	BallStruct *CheckBall;	
	for(CheckBall = FirstBall; CheckBall->next !=NULL ; CheckBall = CheckBall->next)
	{	// 공이 2/3 지점 위에 있는 경우 그 공을 채택
		if(HighBall->dy < HEIGHT*(2.0/3.0) )
			break;
		if(HighBall->dy > CheckBall->dy)	// HighBall이 CheckBall보다 아래에 있으면 교체
			HighBall = CheckBall;		
	}	// 제일 위에 있는 공을 이용하면 어떨까?
	dx = Frame * HighBall->dx;
	dy = Frame * HighBall->dy;
	//LeaveCriticalSection(&Ball_CRT);
	T = atan(dy/dx);
	if(dx<0)	T += PI;
	float entry;
	//for문 중간은 for문이 마치는 조건임.
	for(entry = PI/4 ; entry < T ; entry += PI/4);
	// 여기까지 현재 공의 각도를 구함.
	// 7개 만들라는 뜻.
	for(float a = entry; a<entry + 7 * (PI/4) ; a+=PI/4){		
		dx=Frame*cos(a+PI/6);	
		dy=Frame*sin(a+PI/6);
		t=(8.2/sqrt(pow(dx,2)+pow(dy,2))/INIT_FRAME);
		//EnterCriticalSection(&Ball_CRT);	// 포인터를 잡기 전에는 임계구역을 지정(쓰레드의 기본)
		CreateBall(HighBall->x,HighBall->y,dx*t, dy*t);
		//LeaveCriticalSection(&Ball_CRT);
	}
	speed+=0.5;
	if(speed>MAX_SPEED)
		speed=MAX_SPEED;
}

void ItemAction(DropingItem* Item){
	// 그림으로 아이템 식별
	if(Item->rand == &Item_ExpandPaddle)
		ExpandPAD();
	else if(Item->rand == &Item_ShrinkPaddle)
		ShrinkPAD();
	else if(Item->rand == &Item_BigBall)
		ExpandBall();
	else if(Item->rand == &Item_MiniBall)
	 	ShrinkBall();
	else if(Item->rand == &Item_GrabPaddle)
		EnableGrab();
	else if(Item->rand == &Item_ExtraLife)
		LifeUp();
	else if(Item->rand == &Item_ExtraEnergy)
		EnergyUp();
	else if(Item->rand == &Item_FasterBall)
		SpeedUp();
	else if(Item->rand == &Item_SlowerBall)
		SpeedDown();
	else if(Item->rand == &Item_ThruBrick)
		PiercingBall();
	else if(Item->rand == &Item_FireBall)
		Fire_Ball();
	else if(Item->rand == &Item_FallingBrick)
		Falling_Brick();
	else if(Item->rand == &Item_UppingBrick)
		Upping_Brick();
	else if(Item->rand == &Item_Empty)
		EmptyItem();
	else if(Item->rand == &Item_Shooting)
		EnableShoot();
	else if(Item->rand == &Item_SplitBall)
		SplitBall();
	else if(Item->rand == &Item_EightBall)
		EightBall();
}